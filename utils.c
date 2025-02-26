#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <math.h>
#include "utils.h"
#include <sys/ioctl.h>
#include <unistd.h>

int get_terminal_width(void) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

void print_centered(const char* str) {
    int width = get_terminal_width();
    int padding = (width - strlen(str)) / 2;
    if (padding > 0) {
        printf("%*s%s\n", padding, "", str);
    } else {
        printf("%s\n", str);
    }
}

int scan_propre(char *entree) {
    if (strcmp(entree, "q") == 0 || strcmp(entree, "quit") == 0) {
        return 1;
    }

    if (strcmp(entree, "h") == 0 || strcmp(entree, "help") == 0) {
        printf("\n=== TYPES DE TOURELLES DISPONIBLES ===\n\n"
        "T - Tourelle Basique (200 🪙)\n"
        "    • Dégâts: 1, PV: 3\n"
        "    • Tourelle économique et fiable\n\n"
        "P - Professeur (500 🪙)\n"
        "    • Dégâts: 4, PV: 3\n"
        "    • Dégâts élevés mais coût important\n\n"
        "B - Bouclier (1000 🪙)\n"
        "    • Dégâts: 0, PV: 9\n"
        "    • Bloque les ennemis sans les blesser\n"
        "    • Très résistant\n\n"
        "G - Grève (1000 🪙)\n"
        "    • Effet spécial: Ralentit les ennemis (vitesse = 1)\n"
        "    • PV: 1\n"
        "    • Stratégique pour contrôler le flux d'ennemis\n\n"
        "S - Stage (1000 🪙)\n"
        "    • Génère 500*(niveau²) 🪙 par tour\n"
        "    • PV: 1\n"
        "    • Investissement pour économie à long terme\n\n"
        "Note: Toutes les tourelles peuvent être améliorées jusqu'au niveau 3\n"
        "      Le coût d'amélioration augmente avec le niveau\n\n"
        "\n=== COMMENT PLACER UNE TOURELLE ===\n\n"
        "Format: [Type][Ligne][Colonne]\n"
        "Exemple: T25 place une Tourelle basique en ligne 2, colonne 5\n"
        "        P715 place un Professeur en ligne 7, colonne 15\n"
        "        B112 place un Bouclier en ligne 1, colonne 12\n\n"
        "• Type: T, P, B, G ou S\n"
        "• Ligne: 1 à 7\n"
        "• Colonne: 1 à 15\n\n"
        "Pour améliorer une tourelle, placez le même type au même endroit\n\n");
        return 0;
    }

    if (strcmp(entree, "s") == 0 || strcmp(entree, "save") == 0) {
        return 1;
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
            return 4;
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
        case 'E': // Etudiant
            return 2;
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
        case 'E':
            return 5;
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
        case 'E':
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
        case 'E':
            return 2;
        default:
            printf(">>>> Mauvais Type\n");
            exit(1);
    }
}

int creer_tourelle(Jeu *jeu, Tourelle *t, char* infos) {
    // Gestion de l'amélioration des tourelles:
    // - Vérifie si une tourelle existe déjà à cette position
    // - Gère les niveaux (max 3) et le coût croissant des améliorations
    // - Retourne 0 si la tourelle doit être placé, 1 sinon
    
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
                    if (pow(prix(infos[0]) * (tmp->niveau + 1), 1.2) > jeu->cagnotte) {
                        printf("Erreur : Vous avez %ld 🪙, l'amélioration coûte %ld 🪙\n", jeu->cagnotte, (long) pow(prix(infos[0]) * (tmp->niveau + 1), 1.2));
                        free(t);
                        return 1;
                    }
                    else {
                        jeu->cagnotte -= (long) pow(prix(infos[0]) * (tmp->niveau + 1), 1.2);
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
    t->next_line = NULL;
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
    // Fonction complexe gérant l'ajout d'une tourelle dans deux structures:
    // 1. La liste chainée globale des tourelles du jeu
    // 2. La liste chainée spécifique à la ligne de la tourelle
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