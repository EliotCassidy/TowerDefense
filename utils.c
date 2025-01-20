#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "utils.h"

// Fonction pour vérifier si une chaîne correspond à une liste d'arguments
int is_valid_input(const char *input, const char *args[], int arg_count) {
    for (int i = 0; i < arg_count; ++i) {
        if (strcmp(input, args[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Fonction scan_propre
void scan_propre(char *output, char* message, int arg_count, ...) {
     if (arg_count == 0) {
        printf("%s\n", message);
        scanf("%s", output);
        return;
    }
    va_list args;
    const char *valid_args[arg_count];
    
    // Initialisation de la liste des arguments
    va_start(args, arg_count);
    for (int i = 0; i < arg_count; ++i) {
        valid_args[i] = va_arg(args, const char *);
    }
    va_end(args);

    // Lecture et validation de l'entrée utilisateur
    char input[256];
    while (1) {
        printf("%s\n", message);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            // Retirer le caractère '\n' en fin de chaîne
            input[strcspn(input, "\n")] = '\0';

            if (is_valid_input(input, valid_args, arg_count)) {
                strcpy(output, input);
                return;
            } else {
                printf("Entrée invalide. Veuillez réessayer.\n");
            }
        }
    }
}

int degat(char type) {
    switch (type) {
        case 'T': //gentil
            return 1;
        case 'P': //gentil
            return 3;
        case 'Z': //mechant
            return 1;
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
        default:
            printf(">>>> Mauvais Type\n");
            exit(1);
    }
}

int pdv(char type) {
    switch (type) {
        case 'T':
            return 1;
        case 'P':
            return 2;
        case 'Z':
            return 3;
        default:
            printf(">>>> Mauvais Type\n");
            exit(1);
    }
}

int gain(char type) {
    switch (type) {
        case 'Z':
            return 150;
        default:
            printf(">>>> Mauvais Type\n");
            exit(1);
    }
}

int vitesse(char type) {
    switch (type) {
        case 'Z':
            return 1;
        default:
            printf(">>>> Mauvais Type\n");
            exit(1);
    }
}

int creer_tourelle(Jeu *jeu, Tourelle *t, char* infos) {

    t->type = infos[0];
    t->prix = prix(infos[0]);
    t->pointsDeVie = pdv(infos[0]);
    t->ligne = infos[1] - '0';
    if (strlen(infos) == 3) {
        t->position = infos[2] - '0';
    }
    else {
        t->position = (infos[2] - '0')*10 + (infos[3] - '0');
    }
    t->next = NULL;

    Tourelle *tmp = jeu->tourelles;

    while (tmp != NULL) {
        if (tmp->ligne == t->ligne && tmp->position == t->position) {
            free(t);
            return 1;
        }
        tmp = tmp->next;
    }
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