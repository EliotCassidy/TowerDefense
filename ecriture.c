#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "utils.h"

// // Fonction pour désactiver l'entrée bufferisée
// void desactiverEntreeBufferisee() {
//     struct termios t;
//     tcgetattr(STDIN_FILENO, &t);
//     t.c_lflag &= ~ICANON; // Désactiver le mode canonique
//     t.c_lflag &= ~ECHO;   // Désactiver l'écho
//     tcsetattr(STDIN_FILENO, TCSANOW, &t);

//     // Rendre stdin non-bloquant
//     fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
// }

// // Fonction pour réactiver l'entrée bufferisée
// void activerEntreeBufferisee() {
//     struct termios t;
//     tcgetattr(STDIN_FILENO, &t);
//     t.c_lflag |= ICANON; // Activer le mode canonique
//     t.c_lflag |= ECHO;   // Activer l'écho
//     tcsetattr(STDIN_FILENO, TCSANOW, &t);

//     // Restaurer stdin en mode bloquant
//     fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) & ~O_NONBLOCK);
// }

// // Effacer l'écran
// void effacerEcran() {
//     printf("\033[H\033[J");
// }

// // Afficher le titre en ASCII art
// void afficherTitre() {

// printf("                                         .----------------.  .----------------.  .----------------.                                         \n");
// printf("                                        | .--------------. || .--------------. || .--------------. |                                        \n");
// printf("                                        | |  ________    | || |      __      | || | _____  _____ | |                                        \n");
// printf("                                        | | |_   ___ `.  | || |     /  \\     | || ||_   _||_   _|| |                                        \n");
// printf("                                        | |   | |   `. \\ | || |    / /\\ \\    | || |  | |    | |  | |                                        \n");
// printf("                                        | |   | |    | | | || |   / ____ \\   | || |  | '    ' |  | |                                        \n");
// printf("                                        | |  _| |___.' / | || | _/ /    \\ \\_ | || |   \\ `--' /   | |                                        \n");
// printf("                                        | | |________.'  | || ||____|  |____|| || |    `.__.'    | |                                        \n");
// printf("                                        | |              | || |              | || |              | |                                        \n");
// printf("                                        | '--------------' || '--------------' || '--------------' |                                        \n");
// printf("                                         '----------------'  '----------------'  '----------------'                                         \n");
// printf(" .----------------.  .-----------------. .----------------.  .----------------.  .----------------.  .----------------.  .----------------. \n");
// printf("| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n");
// printf("| |     _____    | || | ____  _____  | || | ____   ____  | || |      __      | || |  ________    | || |  _________   | || |  _______     | |\n");
// printf("| |    |_   _|   | || ||_   \\|_   _| | || ||_  _| |_  _| | || |     /  \\     | || | |_   ___ `.  | || | |_   ___  |  | || | |_   __ \\    | |\n");
// printf("| |      | |     | || |  |   \\ | |   | || |  \\ \\   / /   | || |    / /\\ \\    | || |   | |   `. \\ | || |   | |_  \\_|  | || |   | |__) |   | |\n");
// printf("| |      | |     | || |  | |\\ \\| |   | || |   \\ \\ / /    | || |   / ____ \\   | || |   | |    | | | || |   |  _|  _   | || |   |  __ /    | |\n");
// printf("| |     _| |_    | || | _| |_\\   |_  | || |    \\ ' /     | || | _/ /    \\ \\_ | || |  _| |___.' / | || |  _| |___/ |  | || |  _| |  \\ \\_  | |\n");
// printf("| |    |_____|   | || ||_____|\\____| | || |     \\_/      | || ||____|  |____|| || | |________.'  | || | |_________|  | || | |____| |___| | |\n");
// printf("| |              | || |              | || |              | || |              | || |              | || |              | || |              | |\n");
// printf("| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n");
// printf(" '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n");

// }

// // Afficher les instructions interactives
// void afficherInstructions() {
//     printf("\033[30;2HAppuie sur Entrée pour jouer"); // En bas à gauche
//     printf("\033[30;100HAppuie sur 's' pour charger un fichier"); // En bas à droite
// }

// // Afficher le dauphin à une position donnée
// void afficherDauphin(int x) {
//     for (int i = 0; i < x; i++) {
//         printf(" ");
//     }
//     printf("     / \\    \n");
//     for (int i = 0; i < x; i++) {
//         printf(" ");
//     }
//     printf("     \\ /    \n");
//     for (int i = 0; i < x; i++) {
//         printf(" ");
//     }
//     printf("   \\  |  / \n");
//     for (int i = 0; i < x; i++) {
//         printf(" ");
//     }
//     printf("    \\_|_/  \n");
//     for (int i = 0; i < x; i++) {
//         printf(" ");
//     }
//     printf("     / \\   \n");
//     for (int i = 0; i < x; i++) {
//         printf(" ");
//     }
//     printf("    /   \\  \n");
// }

// int afficher_menu() {
//     desactiverEntreeBufferisee();
//     int position = 0;
//     int direction = 1; // 1 pour droite, -1 pour gauche

//     while (1) {
//         effacerEcran();
//         afficherTitre(); // Appel à la fonction générique pour afficher le titre
//         afficherDauphin(position);
//         afficherInstructions();

//         // Mettre à jour la position
//         if (direction == 1 && position < 130) {
//             position++;
//         } else if (direction == -1 && position > 0) {
//             position--;
//         } else {
//             direction *= -1; // Inverser la direction
//         }

//         // Vérifier les touches pressées
//         char c = getchar();
//         if (c == '\n') {
//             printf("\nDémarrage du jeu...\n");
//             effacerEcran();
//             return 1;
//         } else if (c == 's') {
//             printf("\nChargement du fichier...\n");
//             effacerEcran();
//             return 2;
//         }

//         usleep(20000); // Attendre 0.2 secondes
//     }

//     activerEntreeBufferisee();
// }


void clear() {
    for (int i = 0; i < 1; i++) {
        printf("\n");
    }
}


int visualiser_vague(Jeu *jeu, Plateau *plateau) {
    printf("Vagues :\n");
    Etudiant *maxi = jeu->etudiants;
    if (maxi == NULL) {
        printf("Pas de vague\n");
        return 1;
    }
    while (maxi->next) {
        maxi = maxi->next;
    }
    int pos = maxi->tour;
    for (int ligne = 1; ligne <= 7; ligne++) {
        printf("%d|   ", ligne);
        Etudiant *e_ligne = jeu->etudiants;
        while (e_ligne->ligne != ligne && e_ligne->next != NULL) {
            e_ligne = e_ligne->next;
        }
        switch (ligne) {
            case 1:
                plateau->ligne1 = e_ligne;
                break;
            case 2:
                plateau->ligne2 = e_ligne;
                break;
            case 3:
                plateau->ligne3 = e_ligne;
                break;
            case 4:
                plateau->ligne4 = e_ligne;
                break;
            case 5:
                plateau->ligne5 = e_ligne;
                break;
            case 6:
                plateau->ligne6 = e_ligne;
                break;
            case 7:
                plateau->ligne7 = e_ligne;
                break;
        }
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
    return 0;
}

void afficher_jeu(Jeu *jeu, Plateau *plateau, Defense *defense) {
    clear();
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
            }
            else {
                printf("  .  ");
            }
            if (pos == 15) {
                printf("\n");
            }
        }
    }
}