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



int prix(char Type) {
    switch (Type) {
        case 'T':
            return 200;
            break;
        case 'P':
            return 500;
            break;
        default:
            printf(">>>> Mauvais Type\n");
            exit(1);
    }
}

int pdv(char Type) {
    switch (Type) {
        case 'T':
            return 1;
            break;
        case 'P':
            return 2;
            break;
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

void ajout(Jeu *jeu, Tourelle *t) {
    Tourelle *tmp = jeu->tourelles;
    Tourelle *last = jeu->tourelles;
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