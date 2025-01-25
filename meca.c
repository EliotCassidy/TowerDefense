#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

Etudiant* ligne_i_etudiant(int l, Plateau *plateau) {
    switch (l) {
        case 1:
            return plateau->ligne1;
        case 2:
            return plateau->ligne2;
        case 3:
            return plateau->ligne3;
        case 4:
            return plateau->ligne4;
        case 5:
            return plateau->ligne5;
        case 6:
            return plateau->ligne6;
        case 7:
            return plateau->ligne7;
        default:
            return NULL;
        
    }
}

Tourelle* ligne_i_tourelle(int l, Defense *defense) {
    switch (l) {
        case 1:
            return defense->ligne1;
        case 2:
            return defense->ligne2;
        case 3:
            return defense->ligne3;
        case 4:
            return defense->ligne4;
        case 5:
            return defense->ligne5;
        case 6:
            return defense->ligne6;
        case 7:
            return defense->ligne7;
        default:
            return NULL;
        
    }
}

void modifier_ligne_i_tourelle(int l, Tourelle *e, Defense *d) {
    switch (l) {
        case 1:
            d->ligne1 = e;
            break;
        case 2:
            d->ligne2 = e;
            break;
        case 3:
            d->ligne3 = e;
            break;
        case 4:
            d->ligne4 = e;
            break;
        case 5:
            d->ligne5 = e;
            break;
        case 6:
            d->ligne6 = e;
            break;
        case 7:
            d->ligne7 = e;
            break;
    }
}

void modifier_ligne_i_etudiant(int l, Etudiant *e, Plateau *p) {
    switch (l) {
        case 1:
            p->ligne1 = e;
            break;
        case 2:
            p->ligne2 = e;
            break;
        case 3:
            p->ligne3 = e;
            break;
        case 4:
            p->ligne4 = e;
            break;
        case 5:
            p->ligne5 = e;
            break;
        case 6:
            p->ligne6 = e;
            break;
        case 7:
            p->ligne7 = e;
            break;
    }
}


void placer_tourelles(Jeu *jeu, Defense* defense, Plateau* plateau) {
    char placement_tourelle[6];
    do {
        scan_propre(placement_tourelle, "Voulez-vous arrêter (o) ? \nSi non, où voulez vous la placer [Type tourelle (T/P/...)][Ligne tourelle (1/.../7)][Position tourelle (1/.../15)] ?", 211, "o","T11", "T12", "T13", "T14", "T15", "T16", "T17", "T18", "T19", "T110", "T111", "T112", "T113", "T114", "T115", "T21", "T22", "T23", "T24", "T25", "T26", "T27", "T28", "T29", "T210", "T211", "T212", "T213", "T214", "T215", "T31", "T32", "T33", "T34", "T35", "T36", "T37", "T38", "T39", "T310", "T311", "T312", "T313", "T314", "T315", "T41", "T42", "T43", "T44", "T45", "T46", "T47", "T48", "T49", "T410", "T411", "T412", "T413", "T414", "T415", "T51", "T52", "T53", "T54", "T55", "T56", "T57", "T58", "T59", "T510", "T511", "T512", "T513", "T514", "T515", "T61", "T62", "T63", "T64", "T65", "T66", "T67", "T68", "T69", "T610", "T611", "T612", "T613", "T614", "T615", "T71", "T72", "T73", "T74", "T75", "T76", "T77", "T78", "T79", "T710", "T711", "T712", "T713", "T714", "T715", "P11", "P12", "P13", "P14", "P15", "P16", "P17", "P18", "P19", "P110", "P111", "P112", "P113", "P114", "P115", "P21", "P22", "P23", "P24", "P25", "P26", "P27", "P28", "P29", "P210", "P211", "P212", "P213", "P214", "P215", "P31", "P32", "P33", "P34", "P35", "P36", "P37", "P38", "P39", "P310", "P311", "P312", "P313", "P314", "P315", "P41", "P42", "P43", "P44", "P45", "P46", "P47", "P48", "P49", "P410", "P411", "P412", "P413", "P414", "P415", "P51", "P52", "P53", "P54", "P55", "P56", "P57", "P58", "P59", "P510", "P511", "P512", "P513", "P514", "P515", "P61", "P62", "P63", "P64", "P65", "P66", "P67", "P68", "P69", "P610", "P611", "P612", "P613", "P614", "P615", "P71", "P72", "P73", "P74", "P75", "P76", "P77", "P78", "P79", "P710", "P711", "P712", "P713", "P714", "P715");
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
                Etudiant *ligne = ligne_i_etudiant(t->ligne, plateau);
                while (ligne && ligne->position < t->position) {
                    ligne = ligne->next_line;
                }
                if (ligne != NULL && ligne->position == t->position) {
                    ligne->enCombat = 1;
                    ligne->enDeplacement = 0;
                    while (ligne->next_line != NULL && ligne->next_line->position <= 15 && ligne->next_line->position - ligne->position == 1) {
                        ligne = ligne->next_line;
                        ligne->enDeplacement = 0;
                    }

                }
                jeu->cagnotte -= t->prix;
            }
        }
        printf("Il vous reste %d 🪙\n", jeu->cagnotte);
    }
    while (placement_tourelle[0] != 'o');
}


int vide_devant(Etudiant *e, Etudiant *ligne) {
    while (ligne && ligne->position <= 14) {
        ligne = ligne->next_line;
    }
    if ( (ligne->position != 15) || ( (ligne->position == 15) && (ligne->enDeplacement == 1) ) ) {
        return 1;
    }
    else {
        return 0;
    }
}

void apparition(Jeu *jeu, Plateau *plateau, Defense* defense, int tour) {
    Etudiant *e = jeu->etudiants;
    Etudiant *l = malloc(sizeof(Etudiant));
    while (e && e->tour <= jeu->tour) {
        if (e->position > 15) {
            l = ligne_i_etudiant(e->ligne, plateau);
            if (vide_devant(e, l) && e->enDeplacement == 0) {
                e->position = 16;
                e->enDeplacement = 1;
            }
            else {
                e->position = 16;

            }
        }
        e = e->next;

    }
    // free(l);
}



void tir_tourelles(Jeu *jeu, Plateau *plateau, Defense* defense) {
    Tourelle *t = jeu->tourelles;
    while (t != NULL) {
        if (degat(t->type) != -1) {
            Etudiant *e = jeu->etudiants;
            Etudiant *prev = jeu->etudiants;
            if (e->ligne == t->ligne && t->position <= e->position && (e->position <= 15 || (e->position == 16 && e->enDeplacement == 1) )) {
                e->pointsDeVie -= degat(t->type);
                if (e->pointsDeVie <= 0) {
                    jeu->cagnotte += gain(e->type);
                    if (e->next == NULL) {
                        printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>VICTOIRE<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                        exit(0);
                    }
                    jeu->etudiants = e->next;
                    if (e->next_line != NULL) {
                        e->next_line->prev_line = e->prev_line;
                        if (e->prev_line == NULL) {
                            modifier_ligne_i_etudiant(e->ligne, e->next_line, plateau);
                        }
                    }
                    else {
                        modifier_ligne_i_etudiant(e->ligne, NULL, plateau);
                    }
                }
            }
            else {
                e = e->next;
                while (e != NULL) {
                    if (e->ligne == t->ligne && t->position <= e->position && (e->position <= 15 || (e->position == 16 && e->enDeplacement == 1) ) ) {
                        e->pointsDeVie -= degat(t->type);
                        if (e->pointsDeVie <= 0) {
                            jeu->cagnotte += gain(e->type);
                            prev->next = e->next;
                            if (e->prev_line == NULL) {
                                modifier_ligne_i_etudiant(e->ligne, e->next_line, plateau);
                            }
                            else {
                                e->prev_line->next_line = e->prev_line;
                            }
                            if (e->next_line != NULL) {
                                e->next_line->prev_line = e->prev_line;
                            }
                        }
                        break;
                    }
                    e = e->next;
                    prev = prev->next;
                }
            }
        }
        t = t->next;
    }
}


void tir_ennemies(Jeu *jeu, Plateau *plateau, Defense *defense) {
    Etudiant *e = jeu->etudiants;
    while (e) {
        if (e->enCombat == 1) {
            Tourelle *t = jeu->tourelles;
            while (t->ligne != e->ligne && t->position != e->position) {
                t = t->next;
            }
            t->pointsDeVie -= degat(e->type);

            if (t->pointsDeVie <= 0) {
                e->enCombat = 0;
                e->enDeplacement = 1;
                while (e->next_line != NULL && e->next_line->enDeplacement == 0 && e->next_line->position <= 15 && e->next_line->enCombat == 0) {
                    e->next_line->enDeplacement = 1;
                    e = e->next_line;
                }
                Tourelle *tmp_ligne = ligne_i_tourelle(t->ligne, defense);
                if (tmp_ligne->position == t->position) {
                    modifier_ligne_i_tourelle(t->ligne, t->next_line, defense);
                }
                else {
                    while (tmp_ligne->next_line->position != t->position) {
                        tmp_ligne = tmp_ligne->next_line;
                    }
                    tmp_ligne->next_line = t->next_line;
                }

                Tourelle *tmp = jeu->tourelles;
                if (tmp->position == t->position && tmp->ligne == t->ligne) {
                    jeu->tourelles = t->next;
                }
                else {
                    while (tmp->next->position != t->position && tmp->next->ligne != t->ligne) {
                        tmp = tmp->next;
                    }
                    tmp->next = t->next;
                }
            }
        }
        e = e->next;
    }
}

int max(int x, int y) {
    if (x<y)
        return y;
    else
        return x;
}

// Selon le chainage next et pas par ligne :(
int avancer_ennemies(Jeu *jeu, Plateau *plateau, Defense *defense) {
    Etudiant *e = jeu->etudiants;
    while (e != NULL) {
        if (e->enDeplacement == 1) {
            if (e->position == 16) {
                e->position = 15;
            }
            else {
                Tourelle *t = ligne_i_tourelle(e->ligne, defense);
                // . . . Z ou // . Z .... Z
                if (t == NULL) {
                    if (e->prev_line == NULL) {
                        e->position -= vitesse(e->type);
                    }
                    else {
                        e->position = max(e->position - vitesse(e->type), e->prev_line->position + 1);
                    }
                }
                else {
                    while (t->next_line != NULL && t->next_line->position <= e->position) {
                        t = t->next_line;
                    }
                    // T . . . Z ou T . Z . Z ou Z . T . Z
                    if (t->position <= e->position) {
                        // T ... Z
                        if (e->prev_line == NULL) {
                            if (t->position >= e->position - vitesse(e->type)) {
                                e->position = t->position;
                                e->enCombat = 1;
                                e->enDeplacement = 0;
                            }
                            else {
                                e->position -= vitesse(e->type);
                            }
                        }
                        else {
                            // Z ... T ... Z
                            if (e->prev_line->position < t->position) {
                                if (t->position >= e->position - vitesse(e->type)) {
                                    e->position = t->position;
                                    e->enCombat = 1;
                                }
                                else {
                                    e->position -= vitesse(e->type);
                                }
                            }
                            // T ... Z ... Z ou ... TZ ... Z ou qui vient de finir le combat
                            else {
                                e->position = max(e->prev_line->position + 1, e->position - vitesse(e->type));
                            }
                        }
                        }
                    else {
                        if (e->prev_line == NULL) {
                            e->position -= vitesse(e->type);
                        }
                        else {
                            e->position = max(e->position - vitesse(e->type), e->prev_line->position + 1);
                        }                            
                    }
                }

            }
            if (e->position <= 0) {
                return 1;
            }
        }
        e = e->next;
    }
    return 0;
}