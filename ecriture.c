#include <stdio.h>
#include <stdlib.h>
#include "utils.h"


// Afficher le titre en ASCII art
void afficherTitre() {

printf("                                         .----------------.  .----------------.  .----------------.                                         \n");
printf("                                        | .--------------. || .--------------. || .--------------. |                                        \n");
printf("                                        | |  ________    | || |      __      | || | _____  _____ | |                                        \n");
printf("                                        | | |_   ___ `.  | || |     /  \\     | || ||_   _||_   _|| |                                        \n");
printf("                                        | |   | |   `. \\ | || |    / /\\ \\    | || |  | |    | |  | |                                        \n");
printf("                                        | |   | |    | | | || |   / ____ \\   | || |  | '    ' |  | |                                        \n");
printf("                                        | |  _| |___.' / | || | _/ /    \\ \\_ | || |   \\ `--' /   | |                                        \n");
printf("                                        | | |________.'  | || ||____|  |____|| || |    `.__.'    | |                                        \n");
printf("                                        | |              | || |              | || |              | |                                        \n");
printf("                                        | '--------------' || '--------------' || '--------------' |                                        \n");
printf("                                         '----------------'  '----------------'  '----------------'                                         \n");
printf(" .----------------.  .-----------------. .----------------.  .----------------.  .----------------.  .----------------.  .----------------. \n");
printf("| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
printf("| |     _____    | || | ____  _____  | || | ____   ____  | || |      __      | || |  ________    | || |  _________   | || |  _______     | |\n");
printf("| |    |_   _|   | || ||_   \\|_   _| | || ||_  _| |_  _| | || |     /  \\     | || | |_   ___ `.  | || | |_   ___  |  | || | |_   __ \\    | |\n");
printf("| |      | |     | || |  |   \\ | |   | || |  \\ \\   / /   | || |    / /\\ \\    | || |   | |   `. \\ | || |   | |_  \\_|  | || |   | |__) |   | |\n");
printf("| |      | |     | || |  | |\\ \\| |   | || |   \\ \\ / /    | || |   / ____ \\   | || |   | |    | | | || |   |  _|  _   | || |   |  __ /    | |\n");
printf("| |     _| |_    | || | _| |_\\   |_  | || |    \\ ' /     | || | _/ /    \\ \\_ | || |  _| |___.' / | || |  _| |___/ |  | || |  _| |  \\ \\_  | |\n");
printf("| |    |_____|   | || ||_____|\\____| | || |     \\_/      | || ||____|  |____|| || | |________.'  | || | |_________|  | || | |____| |___| | |\n");
printf("| |              | || |              | || |              | || |              | || |              | || |              | || |              | |\n");
printf("| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
printf(" '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n");

}

// Afficher les instructions interactives
void afficherInstructions() {
    printf("1 : Partie dans niveau.txt\n"); // En bas à gauche
    printf("2 : Partie infinie\n");
    printf("3 : Charger un fichier de sauvegarde\n"); // En bas à droite
}

void effacerEcran() {
    printf("\n\n\n\n\n\n\n\n\n\n");
}

int afficher_menu() {
    effacerEcran();
    afficherTitre();
    afficherInstructions();

    char c[3];
    fgets(c, sizeof(c), stdin);
    if (c[0] == '1') {
        printf("\nDémarrage du jeu...\n");
        effacerEcran();
        return 1;
    }
    else if (c[0] == '2') {
        printf("\nDémarrage du jeu...\n");
        effacerEcran();
        return 2;
    } 
    else if (c[0] == '3') {
        printf("\nChargement du fichier...\n");
        effacerEcran();
        return 3;
    }
    else {
        return -1;
    }

}




int visualiser_vague(Jeu *jeu, Plateau *plateau) {
    printf("Vagues :\n");
    Etudiant *maxi = jeu->etudiants;
    if (maxi == NULL) {
        printf("Pas de vague\n");
        return 0;
    }
    while (maxi->next) {
        maxi = maxi->next;
    }
    int pos = maxi->tour;
    for (int ligne = 1; ligne <= 7; ligne++) {
        printf("%d|   ", ligne);
        Etudiant *e_ligne = jeu->etudiants;
        while (e_ligne != NULL && e_ligne->ligne != ligne) {
            e_ligne = e_ligne->next;
        }
        modifier_ligne_i_etudiant(ligne, e_ligne, plateau);

        for (int el = 1; el <= pos; el++) {
            if (e_ligne != NULL && e_ligne->tour == el && e_ligne->ligne == ligne) {
                printf(" %2d%c ", e_ligne->pointsDeVie, e_ligne->type);
                e_ligne = e_ligne->next_line;
            }
            else {
                printf("  .  ");
            }
            if (el == pos) {
                printf("\n");
            }
        }
    }
    return 1;
}

void afficher_jeu(Jeu *jeu, Plateau *plateau, Defense *defense) {
    effacerEcran();
    for (int ligne = 1; ligne <= 7; ligne++) {
        printf("%d|   ", ligne);
        Etudiant *e = malloc(sizeof(Etudiant));
        Tourelle *d = malloc(sizeof(Tourelle));
        switch (ligne) {
            case 1:
                e = plateau->ligne1;
                d = defense->ligne1;
                break;
            case 2:
                e = plateau->ligne2;
                d = defense->ligne2;
                break;
            case 3:
                e = plateau->ligne3;
                d = defense->ligne3;
                break;
            case 4:
                e = plateau->ligne4;
                d = defense->ligne4;
                break;
            case 5:
                e = plateau->ligne5;
                d = defense->ligne5;
                break;
            case 6:
                e = plateau->ligne6;
                d = defense->ligne6;
                break;
            case 7:
                e = plateau->ligne7;
                d = defense->ligne7;
                break;
        }

        for (int pos = 1; pos <= 15; pos++) {
            if (d && e && d->position == pos && e->position == pos) {
                printf("%c%1d#%1d%c", d->type, d->pointsDeVie, e->pointsDeVie, e->type);
                d = d->next_line;
                e = e->next_line;
            }
            else if (d && d->position == pos) {
                printf(" %c%2d#", d->type, d->pointsDeVie);
                d = d->next_line;
            }
            else if (e && e->position == pos) {
                printf(" %2d%c ", e->pointsDeVie, e->type);
                e = e->next_line;
            }
            else {
                printf("  .  ");
            }
            if (pos == 15) {
                printf("\n");
            }
        }
    }
        printf(" |\n");
    printf(" |     1    2    3    4    5    6    7    8    9    10   11   12   13   14   15");
}