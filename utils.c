#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include "utils.h"


int scan_propre(char *entree) {
    if (strcmp(entree, "q") == 0 || strcmp(entree, "quit") == 0) {
        return 1;
    }

    if (strcmp(entree, "h") == 0 || strcmp(entree, "help") == 0) {
        printf("HELP A FAIRE\n");
        return 0;
    }

    if (strlen(entree) < 3 || strlen(entree) > 4) {
        return 0;
    }


    if (entree[0] != 'P' && entree[0] != 'T' && entree[0] != 'B' && entree[0] != 'G' && entree[0] != 'S') {
        return 0;
    }


    if (!isdigit(entree[1])) {
        return 0;
    }
    int ligne = entree[1] - '0';
    if (ligne < 1 || ligne > 7) {
        return 0;
    }


    int position = 0;
    if (isdigit(entree[2])) {
        position = entree[2] - '0';
        if (strlen(entree) == 4 && isdigit(entree[3])) {
            position = position * 10 + (entree[3] - '0');
        }
    } else {
        return 0;
    }
    if (position < 1 || position > 15) {
        return 0;
    }

    return 1;
}

int degat(char type) {
    switch (type) {
        //gentil
        case 'T': // Tourelle
            return 1;
        case 'P': // Professeur
            return 2;
        case 'B': // Bouclier
            return 0;
        case 'G': // Greve
            return -2;
        case 'S': // Stage
            return -1;


        //mechant
        case 'Z': // Zzzzz
            return 1;
        case 'M': // Majorant
            return 3;
        case 'R': // Redoublant
            return 1;
        case 'C': // Conditionel
            return 4;
        default:
            return -1;
    }
}

int prix(char type) {
    switch (type) {
        case 'T':
            return 200;
        case 'P':
            return 500;
        case 'B':
            return 1000;
        case 'G':
            return 1000;
        case 'S':
            return 1000;
        default:
            printf(">>>> Mauvais Type\n");
            exit(1);
    }
}

int pdv(char type) {
    switch (type) {
        case 'T':
            return 3;
        case 'P':
            return 3;
        case 'B':
            return 9;
        case 'G':
            return 1;
        case 'S':
            return 1;
        

        case 'Z':
            return 5;
        case 'M':
            return 5;
        case 'R':
            return 7;
        case 'C':
            return 2;
        default:
            printf(">>>> Mauvais Type\n");
            exit(1);
    }
}

int gain(char type) {
    switch (type) {
        case 'R':
            return 300;
        case 'M':
            return 350;
        case 'Z':
            return 100;
        case 'C':
            return 300;
        default:
            printf(">>>> Mauvais Type\n");
            exit(1);
    }
}

int vitesse(char type) {
    switch (type) {
        case 'M':
            return 3;
        case 'R':
            return 1;
        case 'Z':
            return 1;
        case 'C':
            return 2;
        default:
            printf(">>>> Mauvais Type\n");
            exit(1);
    }
}

int creer_tourelle(Jeu *jeu, Tourelle *t, char* infos) {
    t->type = infos[0];
    t->ligne = infos[1] - '0';
    if (strlen(infos) == 3) {
        t->position = infos[2] - '0';
    }
    else {
        t->position = (infos[2] - '0')*10 + (infos[3] - '0');
    }

    Tourelle *tmp = jeu->tourelles;

    while (tmp != NULL) {
        if (tmp->ligne == t->ligne && tmp->position == t->position) {
            if (t->type != tmp->type) {
                free(t);
                printf("Il y a déjà une tourelle d'un autre type\n");
                return 1;  
            }
            else {
                if (tmp->niveau == 3) {
                    free(t);
                    printf("La tourelle est déjà au niveau maximum\n");
                    return 1;
                }
                else {
                    if (pow(prix(infos[0]) * (tmp->niveau + 1), 1.5) > jeu->cagnotte) {
                        printf("Erreur : Vous avez %ld 🪙, l'amélioration coûte %ld 🪙\n", jeu->cagnotte, (long) pow(prix(infos[0]) * (tmp->niveau + 1), 1.5));
                        free(t);
                        return 1;
                    }
                    else {
                        jeu->cagnotte -= (long) pow(prix(infos[0]) * (tmp->niveau + 1), 1.5);
                        tmp->niveau += 1;
                        tmp->pointsDeVie = (int) (tmp->pointsDeVie + 2*pow(tmp->niveau, 1.2));
                        free(t);
                        return 1;
                    }
                }
            }
        }
        tmp = tmp->next;
    }
    if (prix(infos[0]) > jeu->cagnotte) {
        printf("Erreur : Vous avez %ld 🪙, la tourelle coûte %d 🪙\n", jeu->cagnotte, prix(infos[0]));
        free(t);
        return 1;
    }
    t->prix = prix(infos[0]);
    t->pointsDeVie = pdv(infos[0]);
    
    t->next = NULL;
    t->niveau = 1;
    return 0;

}

void ajout_liste_chainer(Tourelle *ligne, Tourelle *t) {
    Tourelle *tmp = ligne->next_line;
    while (tmp != NULL && tmp->position <= t->position) {
        tmp = tmp->next_line;
        ligne = ligne->next_line;
    }
    ligne->next_line = t;
    ligne->next_line->next_line = tmp;

}

void ajout(Jeu *jeu, Tourelle *t, Defense *d) {
    Tourelle *tmp = jeu->tourelles;
    Tourelle *last = jeu->tourelles;
    switch (t->ligne) {
        case 1:
            if (d->ligne1 == NULL) {
                d->ligne1 = t;
            }
            else if (d->ligne1->position > t->position) {
                Tourelle *tmp = d->ligne1;
                d->ligne1 = t;
                d->ligne1->next_line = tmp;

            }
            else {
                ajout_liste_chainer(d->ligne1, t);
            }
            break;
        case 2:
            if (d->ligne2 == NULL) {
                d->ligne2 = t;
            }
            else if (d->ligne2->position > t->position) {
                Tourelle *tmp = d->ligne2;
                d->ligne2 = t;
                d->ligne2->next_line = tmp;

            }
            else {
                ajout_liste_chainer(d->ligne2, t);
            }
            break;
        case 3:
            if (d->ligne3 == NULL) {
                d->ligne3 = t;
            }
            else if (d->ligne3->position > t->position) {
                Tourelle *tmp = d->ligne3;
                d->ligne3 = t;
                d->ligne3->next_line = tmp;

            }
            else {
                ajout_liste_chainer(d->ligne3, t);
            }
            break;
        case 4:
            if (d->ligne4 == NULL) {
                d->ligne4 = t;
            }
            else if (d->ligne4->position > t->position) {
                Tourelle *tmp = d->ligne4;
                d->ligne4 = t;
                d->ligne4->next_line = tmp;

            }
            else {
                ajout_liste_chainer(d->ligne4, t);
            }
            break;
        case 5:
            if (d->ligne5 == NULL) {
                d->ligne5 = t;
            }
            else if (d->ligne5->position > t->position) {
                Tourelle *tmp = d->ligne5;
                d->ligne5 = t;
                d->ligne5->next_line = tmp;

            }
            else {
                ajout_liste_chainer(d->ligne5, t);
            }
            break;
        case 6:
            if (d->ligne6 == NULL) {
                d->ligne6 = t;
            }
            else if (d->ligne6->position > t->position) {
                Tourelle *tmp = d->ligne6;
                d->ligne6 = t;
                d->ligne6->next_line = tmp;

            }
            else {
                ajout_liste_chainer(d->ligne6, t);
            }
            break;
        case 7:
            if (d->ligne7 == NULL) {
                d->ligne7 = t;
            }
            else if (d->ligne7->position > t->position) {
                Tourelle *tmp = d->ligne7;
                d->ligne7 = t;
                d->ligne7->next_line = tmp;

            }
            else {
                ajout_liste_chainer(d->ligne7, t);
            }
            break;
    }

    if (last == NULL) {
        jeu->tourelles = t;
        return;
    }
    tmp = tmp->next;
    while (tmp != NULL) {
        tmp = tmp->next;
        last = last->next;
    }
    last->next = t;
}