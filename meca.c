#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void placer_tourelles(Jeu *jeu, Defense* defense) {
    char placement_tourelle[6];
    do {
        scan_propre(placement_tourelle, "Voulez-vous arrêter (o) ? \nSi oui, où voulez vous la placer [Type tourelle (T/P/...)][Ligne tourelle (1/.../7)][Position tourelle (1/.../15)] ?", 211, "o","T11", "T12", "T13", "T14", "T15", "T16", "T17", "T18", "T19", "T110", "T111", "T112", "T113", "T114", "T115", "T21", "T22", "T23", "T24", "T25", "T26", "T27", "T28", "T29", "T210", "T211", "T212", "T213", "T214", "T215", "T31", "T32", "T33", "T34", "T35", "T36", "T37", "T38", "T39", "T310", "T311", "T312", "T313", "T314", "T315", "T41", "T42", "T43", "T44", "T45", "T46", "T47", "T48", "T49", "T410", "T411", "T412", "T413", "T414", "T415", "T51", "T52", "T53", "T54", "T55", "T56", "T57", "T58", "T59", "T510", "T511", "T512", "T513", "T514", "T515", "T61", "T62", "T63", "T64", "T65", "T66", "T67", "T68", "T69", "T610", "T611", "T612", "T613", "T614", "T615", "T71", "T72", "T73", "T74", "T75", "T76", "T77", "T78", "T79", "T710", "T711", "T712", "T713", "T714", "T715", "P11", "P12", "P13", "P14", "P15", "P16", "P17", "P18", "P19", "P110", "P111", "P112", "P113", "P114", "P115", "P21", "P22", "P23", "P24", "P25", "P26", "P27", "P28", "P29", "P210", "P211", "P212", "P213", "P214", "P215", "P31", "P32", "P33", "P34", "P35", "P36", "P37", "P38", "P39", "P310", "P311", "P312", "P313", "P314", "P315", "P41", "P42", "P43", "P44", "P45", "P46", "P47", "P48", "P49", "P410", "P411", "P412", "P413", "P414", "P415", "P51", "P52", "P53", "P54", "P55", "P56", "P57", "P58", "P59", "P510", "P511", "P512", "P513", "P514", "P515", "P61", "P62", "P63", "P64", "P65", "P66", "P67", "P68", "P69", "P610", "P611", "P612", "P613", "P614", "P615", "P71", "P72", "P73", "P74", "P75", "P76", "P77", "P78", "P79", "P710", "P711", "P712", "P713", "P714", "P715");
        if (placement_tourelle[0] == 'o') {
            break;
        }
        if (prix(placement_tourelle[0]) > jeu->cagnotte) {
            printf("Erreur : Vous avez %d 🪙, la tourelle coûte %d 🪙\n", jeu->cagnotte, prix(placement_tourelle[0]));
        }
        else {
            Tourelle *t = malloc(sizeof(Tourelle));
            if (creer_tourelle(jeu, t, placement_tourelle)) {
                printf("Erreur, il y a déjà une tourelle ici\n");
            }
            else {
                ajout(jeu, t, defense);
                jeu->cagnotte -= t->prix;
            }
        }
        printf("Il vous reste %d 🪙\n", jeu->cagnotte);
    }
    while (placement_tourelle[0] != 'o');
}


void avancer_ennemies(Jeu *jeu, Plateau *plateau, Defense* defense, int tour) {
    Etudiant *e = jeu->etudiants;
}