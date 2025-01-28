#include <stdio.h>
#include <stdlib.h>
#include "utils.h" 


void save_tourelle(const char* nomfichier, Tourelle* head)  {
    //int nb_tourelle = 0;
    FILE * sauvegarde = fopen("nomfichier", "w");
    if (sauvegarde == NULL) {
        perror("Erreur lors de la création du fichier");
        exit(EXIT_FAILURE);
    }

    Tourelle* tmp = head;
    while (tmp != NULL) {
        fprintf(sauvegarde, "%d %d %d %d %d\n", tmp->type, tmp->pointsDeVie, tmp->ligne, tmp->position, tmp->prix );
        tmp = tmp->next;
        //nb_tourelle ++;
    } 

    fprintf(sauvegarde, "\n");

    fclose(sauvegarde);
    //return nb_tourelle;
}

void save_etudiant(const char* nomfichier, Etudiant* head) {
    FILE * sauvegarde = fopen("nomfichier", "a");
    if (sauvegarde == NULL) {
        perror("Erreur lors de la création du fichier");
        exit(EXIT_FAILURE);
    }

    Etudiant* tmp = head;
    while (tmp != NULL) {
        fprintf(sauvegarde, "%d %d %d %d %d %d\n", tmp->type, tmp->pointsDeVie, tmp->position, tmp->vitesse, tmp->tour);
    }
    fprintf(sauvegarde, "\n");

    fclose(sauvegarde);
}  


void save(const char* nomfichier, Jeu* jeu) {

    save_tourelle(nomfichier, jeu->tourelles);
    save_etudiant(nomfichier, jeu->etudiants);
    printf("Etudiant et tourelles save avec succès");
    FILE* sauvegarde = fopen(nomfichier, "a");
    fprintf(sauvegarde, "%d, %d\n", jeu->cagnotte, jeu->tour);
    fclose(sauvegarde);

    printf("Tout est sauvgardé grace à dieu");

}

