#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int nb_etudiants = 0;

Etudiant* creer_etudiant(int type, int ligne, int tour) {
    Etudiant* e = malloc(sizeof(Etudiant));
    if (!e) {
        perror("Erreur d'allocation mémoire pour un étudiant");
        exit(EXIT_FAILURE);
    }
    e->type = type;
    e->ligne = ligne;
    e->position = -1;
    e->tour = tour;
    e->enCombat = 0;
    e->enDeplacement = 1;
    e->pointsDeVie = pdv(e->type);
    e->vitesse = vitesse(e->type);
    e->next = NULL;
    e->next_line = NULL;
    e->prev_line = NULL;
    return e;
}

void ajouter_etudiant(Jeu* jeu, Etudiant* etudiant, Plateau *p) {
    Etudiant* temp = jeu->etudiants;
    Etudiant* prev = NULL;
    nb_etudiants += 1;
    while (temp && temp->tour <= etudiant->tour) {
        // Gérer les conflits de position sur la même ligne
        if (temp->ligne == etudiant->ligne && temp->tour == etudiant->tour) {
            etudiant->tour += 1;
        }
        prev = temp;
        temp = temp->next;
    }

    // Insérer l'étudiant dans la liste globale
    if (prev) {
        prev->next = etudiant;
    } else {
        jeu->etudiants = etudiant; // L'étudiant devient la tête de liste
    }
    etudiant->next = temp;
    etudiant->position = 15 + etudiant->tour;

    // Maintenir les relations `next_line` et `prev_line` pour les étudiants de la même ligne
    Etudiant* ligne_temp = jeu->etudiants;
    Etudiant* ligne_prev = NULL;

    while (ligne_temp) {
        if (ligne_temp->ligne == etudiant->ligne) {
            if (ligne_temp->position < etudiant->position) {
                ligne_prev = ligne_temp;
            } else if (ligne_temp->position > etudiant->position) {
                etudiant->next_line = ligne_temp;
                ligne_temp->prev_line = etudiant;
                break;
            }
        }
        ligne_temp = ligne_temp->next;
    }

    if (ligne_prev) {
        ligne_prev->next_line = etudiant;
        etudiant->prev_line = ligne_prev;
    }
    if (etudiant->prev_line == NULL) {
        modifier_ligne_i_etudiant(etudiant->ligne, etudiant, p);
    }
}



void lire_fichier(const char* nom_fichier, Jeu* jeu, Plateau *plateau) {
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

        Etudiant* e = creer_etudiant(type[0], ligne, tour);
        ajouter_etudiant(jeu, e, plateau);
    }
    fclose(fichier);
}

void libere_jeu(Jeu *jeu) {
    Etudiant *temp = jeu->etudiants;
    while (temp) {
        Etudiant* suivant = temp->next;
        free(temp);
        temp = suivant;
    }
    Tourelle *tmp = jeu->tourelles;
    while (tmp) {
        Tourelle* suivant = tmp->next;
        free(tmp);
        tmp = suivant;
    }
}