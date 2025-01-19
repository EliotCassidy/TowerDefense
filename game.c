#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Fonction principale
int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier_d_entree>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Plateau plateau = {.ligne1 = NULL, .ligne2 = NULL, .ligne3 = NULL, .ligne4 = NULL, .ligne5 = NULL, .ligne6 = NULL, .ligne7 = NULL};
    Defense defense = {.ligne1 = NULL, .ligne2 = NULL, .ligne3 = NULL, .ligne4 = NULL, .ligne5 = NULL, .ligne6 = NULL, .ligne7 = NULL};
    Jeu jeu = { .tourelles = NULL, .etudiants = NULL, .cagnotte = 0, .tour = 0 };
    lire_fichier(argv[1], &jeu, &plateau);



    // int choix = afficher_menu();
    // Gérer cas = 2
    // switch (choix) {
    //     case 1:

    //     case 2:

    //     default:
    //         exit(EXIT_FAILURE);
    //         break;
    // }

    visualiser_vague(&jeu, &plateau);
    printf("Vous avez %d 🪙\n", jeu.cagnotte);
    placer_tourelles(&jeu, &defense, &plateau);
    afficher_jeu(&jeu, &plateau, &defense);
    jeu.tour = 1;
    while (jeu.tour < 10) {
        printf("----------------- TOUR %d -----------------\n", jeu.tour);
        apparition(&jeu, &plateau, &defense, jeu.tour);
        tir_tourelles(&jeu, &plateau, &defense);
        afficher_jeu(&jeu, &plateau, &defense);

        // tir_ennemies(&jeu);
        // avancer_ennemies(&jeu);
        // if (partie_perdu(&jeu)) {
        //     procedure_perte(&jeu);
        //     break;
        // }
        // placer_tourelles(&jeu);
        // afficher_jeu(&jeu, &plateau);

        // if (jeu.etudiants == NULL) {
            
        // }
        jeu.tour++;
    }
    
    libere_jeu(&jeu);
}
