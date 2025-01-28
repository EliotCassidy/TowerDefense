#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


int max_actions = 5000;
int placement = 0;
int pt_ligne = 0;

// Fonction principale
int main(void) {

    Plateau plateau = {.ligne1 = NULL, .ligne2 = NULL, .ligne3 = NULL, .ligne4 = NULL, .ligne5 = NULL, .ligne6 = NULL, .ligne7 = NULL};
    Defense defense = {.ligne1 = NULL, .ligne2 = NULL, .ligne3 = NULL, .ligne4 = NULL, .ligne5 = NULL, .ligne6 = NULL, .ligne7 = NULL};
    Jeu jeu = { .tourelles = NULL, .etudiants = NULL, .cagnotte = 0, .tour = 0 , .score = 0, .niveau = 0, .mode = 0};
    char *actions[max_actions];


    char *nom_fichier = "niveau.txt";
    char **instructions = malloc(max_actions * sizeof(char *));
    instructions[0]= "END";
    int choix = afficher_menu();
    jeu.mode = choix;
    
    if (jeu.mode == -1) {
        printf("Mauvais mode de jeu\n");
        return 1;
    }
    else if (jeu.mode == 1) {
        lire_fichier(nom_fichier, &jeu, &plateau);
        supr_sauvegarde(nom_fichier);
    }
    else if (jeu.mode == 2) {
        printf("Ce mode de jeu n'est pas encore disponible :(\n");
        return 1;
    }
    else if (jeu.mode == 3) {
        lire_fichier(nom_fichier, &jeu, &plateau);
        lire_instruction(nom_fichier, instructions);
    }

    printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>VISUALISER<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    int enCours = visualiser_vague(&jeu, &plateau);
    jeu.tour = 1;
    int toucher = 0;
    int i = 0;

    while (enCours) {
        printf("\n------------------------------------ TOUR %d ------------------------------------\n", jeu.tour);
        printf("%ld 🪙", jeu.cagnotte);
        printf("\t\t\t\t\t\t\t\t\t Score : %ld\n\n", jeu.score);
        if (jeu.mode == 3 && strcmp(instructions[i], "END") != 0) {
            placer_tourelles(&jeu, &defense, &plateau, actions, nom_fichier, instructions, &i);
        }
        else {
            placer_tourelles(&jeu, &defense, &plateau, actions, nom_fichier, instructions, &i);
        }
        apparition(&jeu, &plateau, &defense, jeu.tour);
        tir_tourelles(&jeu, &plateau, &defense, actions, instructions);
        tir_ennemies(&jeu, &plateau, &defense);
        toucher = avancer_ennemies(&jeu, &plateau, &defense);
        if (toucher == 1) {
            printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>DEFAITE<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            break;
        }
        if (jeu.etudiants == NULL) {
            printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>VICTOIRE<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            break;
        }
        afficher_jeu(&jeu, &plateau, &defense);
        jeu.tour++;
    }
    
    libere_jeu(&jeu, actions, instructions);
    return EXIT_SUCCESS;
}
