#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture.h"

int nb_etudiants = 0;

Etudiant* creer_etudiant(int type, int pointsDeVie, int ligne, int position, int vitesse, int tour) {
    Etudiant* e = malloc(sizeof(Etudiant));
    if (!e) {
        perror("Erreur d'allocation mémoire pour un étudiant");
        exit(EXIT_FAILURE);
    }
    e->type = type;
    e->pointsDeVie = pointsDeVie;
    e->ligne = ligne;
    e->position = position;
    e->vitesse = vitesse;
    e->tour = tour;
    e->next = NULL;
    e->next_line = NULL;
    e->prev_line = NULL;
    return e;
}

void ajouter_etudiant(Jeu* jeu, Etudiant* etudiant) {
    if (!jeu->etudiants) {
        jeu->etudiants = etudiant;
    }
    else {
        Etudiant* temp = jeu->etudiants;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = etudiant;
    
    nb_etudiants += 1;
    }
}

void lire_fichier(const char* nom_fichier, Jeu* jeu) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Lecture de la cagnotte
    if (fscanf(fichier, "%d", &jeu->cagnotte) != 1) {
        fprintf(stderr, "Erreur de lecture de la cagnotte\n");
        fclose(fichier);
        exit(EXIT_FAILURE);
    }

    int tour, ligne;
    char type[2];

    // Lecture des vilains ennemis
    while (fscanf(fichier, "%d %d %s", &tour, &ligne, type) == 3) {
        Etudiant* e = creer_etudiant(type[0], 5, ligne, 0, 1, tour);
        ajouter_etudiant(jeu, e);
    }
    fclose(fichier);
}


// Fonction principale
int lecture(char *fichier) {
    Jeu jeu = { .tourelles = NULL, .etudiants = NULL, .cagnotte = 0, .tour = 0 };

    lire_fichier(fichier, &jeu);

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
