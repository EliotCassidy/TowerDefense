#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture.h"

// Fonction principale
int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fichier_d_entree>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Jeu jeu = { .tourelles = NULL, .etudiants = NULL, .cagnotte = 0, .tour = 0 };

    lire_fichier(argv[1], &jeu);

    // Exemple d'affichage de la liste des étudiants lus
    printf("Cagnotte: %d\n", jeu.cagnotte);
    Etudiant* temp = jeu.etudiants;
    while (temp) {
        printf("Tour: %d, Ligne: %d, Type: %d, PV: %d\n",
               temp->tour, temp->ligne, temp->type, temp->pointsDeVie);
        temp = temp->next;
    }

    // Libération de la mémoire
    temp = jeu.etudiants;
    while (temp) {
        Etudiant* suivant = temp->next;
        free(temp);
        temp = suivant;
    }

    return EXIT_SUCCESS;
}
