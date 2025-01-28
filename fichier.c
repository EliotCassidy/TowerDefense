#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "utils.h" 


void save(const char* nomfichier, Jeu* jeu, char *actions[]) {

    FILE* fichier = fopen(nomfichier, "a");
        if (!fichier) {
            perror("Erreur lors de l'ouverture du fichier");
            exit(EXIT_FAILURE);
        }
        fprintf(fichier, "\n#####\n");
        for (int i = 0; i < nb_actions; i++) {
            fprintf(fichier, "%s\n", actions[i]);
        }

        fclose(fichier);
}

void supr_sauvegarde(const char* nom_fichier) {
    
    FILE *f = fopen(nom_fichier, "r+");
    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char line[256];
    FILE *tmpf = fopen("temp.txt", "w");
    if (tmpf == NULL) {
        perror("Erreur d'ouverture du fichier temporaire");
        fclose(f);
        exit(EXIT_FAILURE);
    }
    int deleteFlag = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strcmp(line, "#####\n") == 0) {
            deleteFlag = 1;
        }
        if (!deleteFlag) {
            fputs(line, tmpf);
        }
    }

    fclose(f);
    fclose(tmpf);

    // Remplace le fichier original par le fichier temporaire
    remove(nom_fichier);
    rename("temp.txt", nom_fichier);

}

void lire_instruction(char * nom_fichier, char ** instructions) {
    FILE *f = fopen(nom_fichier, "r");
    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int flag = 1;
    int i = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strcmp(line, "#####\n") == 0) {
            flag = 0;
        }
        if (!flag) {
            instructions[i] = strdup(line);
            i++;
        }
    }
    instructions[i] = "END";
}