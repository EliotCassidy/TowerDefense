#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "utils.h" 


void save(const char* nomfichier, Jeu* jeu, char *actions[]) {
    // Sauvegarde des actions du joueur:
    // - Ajoute un marqueur ##### pour séparer la configuration du niveau
    // - Enregistre chaque action dans l'ordre d'exécution
    
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
    // Nettoyage du fichier de sauvegarde:
    // - Conserve uniquement la configuration du niveau
    // - Supprime toutes les actions précédentes (après le marqueur #####)
    // - Utilise un fichier temporaire
    
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
    // Lecture du fichier de sauvegarde:
    // - Ignore tout ce qui précède le marqueur #####
    // - Charge les instructions jusqu'à la fin du fichier
    // - Termine la liste avec "END"
    
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
    fclose(f);
}

void ajouter_classement(char *classement, int score, char *nom, int i) {
    // Mise à jour du tableau des scores:
    // - Insère le nouveau score à la position i
    // - Décale les scores inférieurs et préserve les 10 meilleurs scores uniquement
    // - Utilise un fichier temporaire
    
    FILE *tmp = fopen("tmp.txt", "w");
    FILE *f = fopen(classement, "r");
    char ligne[50];
    for (int j = 0; j < i; j++) {
        fgets(ligne, sizeof(ligne), f);
        fputs(ligne, tmp);
    }
    fprintf(tmp, "%d %s\n", score, nom);
    for (int j = i; j < 9; j++) {
        if (!fgets(ligne, sizeof(ligne), f)) {
            break;
        }
        fputs(ligne, tmp);
    }


    fclose(f);
    fclose(tmp);

    remove(classement);
    rename("tmp.txt", classement);

}

void verifier_score(Jeu *jeu, int *scores, char *classement) {
    // Gestion du système de high scores:
    // - Vérifie si le score actuel mérite d'être dans le top 10
    // - Détermine la position exacte du nouveau score
    // - Demande le nom de l'utilisateur pour l'enregistrement
    
    if (jeu->score <= scores[9]) {
        return;
    }
    int i;
    for (i = 0; i < 10; i++) {
        if (jeu->score > scores[i]) {
            break;
        }
    }
    printf("BRAVO ! Vous êtes le numéro %d dans le classement !\nComment vous appelez vous ?\n", i+1);
    char nom[20];
    scanf("%19s", nom);
    ajouter_classement(classement, jeu->score, nom, i);
    printf("Votre score a bien été enregistré\n");
}
