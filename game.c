#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Fonction principale
int main(void) {

    Plateau plateau = {.ligne1 = NULL, .ligne2 = NULL, .ligne3 = NULL, .ligne4 = NULL, .ligne5 = NULL, .ligne6 = NULL, .ligne7 = NULL};
    Defense defense = {.ligne1 = NULL, .ligne2 = NULL, .ligne3 = NULL, .ligne4 = NULL, .ligne5 = NULL, .ligne6 = NULL, .ligne7 = NULL};
    Jeu jeu = { .tourelles = NULL, .etudiants = NULL, .cagnotte = 0, .tour = 0 , .score = 0, .niveau = 0, .mode = 0};




    int choix = afficher_menu();
    jeu.mode = choix;
    if (jeu.mode == -1) {
        printf("Mauvais mode de jeu\n");
        return 1;
    }
    else if (jeu.mode == 1) {
        lire_fichier("niveau.txt", &jeu, &plateau);
    }


    printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>VISUALISER<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
    int enCours = visualiser_vague(&jeu, &plateau);
    jeu.tour = 1;
    int toucher = 0;
    while (enCours) {
        printf("\n------------------------------------ TOUR %d ------------------------------------\n", jeu.tour);
        printf("%ld 🪙", jeu.cagnotte);
        printf("\t\t\t\t\t\t\t\t\t Score : %ld\n\n", jeu.score);
        placer_tourelles(&jeu, &defense, &plateau);
        apparition(&jeu, &plateau, &defense, jeu.tour);
        tir_tourelles(&jeu, &plateau, &defense);
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
    
    libere_jeu(&jeu);
    return EXIT_SUCCESS;
}
