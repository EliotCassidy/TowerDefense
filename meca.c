#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
        do {
            printf("Voulez-vous arrêter (o) ? \nSi non, où voulez vous la placer [Type tourelle (T/P/...)][Ligne tourelle (1/.../7)][Position tourelle (1/.../15)] ?\n");
            fgets(placement_tourelle, sizeof(placement_tourelle), stdin);
            placement_tourelle[strcspn(placement_tourelle, "\n")] = '\0';
        }
        while (scan_propre(placement_tourelle) == 0);


        if (placement_tourelle[0] == 'o') {
            break;
        }
        else {
            Tourelle *t = malloc(sizeof(Tourelle));
            if (creer_tourelle(jeu, t, placement_tourelle) == 0) {
                nb_tourelles += 1;
                ajout(jeu, t, defense);
                Etudiant *ligne = ligne_i_etudiant(t->ligne, plateau);
                while (ligne != NULL && ligne->position < t->position) {
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
        afficher_jeu(jeu, plateau, defense);
        printf("\n");
        printf("Il vous reste %ld 🪙\n", jeu->cagnotte);
    }
    while (placement_tourelle[0] != 'o');
}


int vide_devant(Etudiant *e, Etudiant *ligne) {
    int cpt = 0;
    while (ligne != NULL && ligne->position <= 14 && cpt < 10) {
        ligne = ligne->next_line;
        cpt++;
    }
    if (ligne != NULL && ( ligne->position != 15 || ( (ligne->position == 15) && (ligne->enDeplacement == 1) ) ) ) {
        return 1;
    }
    else {
        return 0;
    }
}

void apparition(Jeu *jeu, Plateau *plateau, Defense* defense, int tour) {
    Etudiant *e = jeu->etudiants;
    while (e && e->tour <= jeu->tour) {
        if (e->position > 15) {
            Etudiant *l = ligne_i_etudiant(e->ligne, plateau);
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
                    jeu->score += (gain(e->type)*exp(-0.05*jeu->tour)*1/(log(1+nb_tourelles)));
                    jeu->cagnotte += gain(e->type);
                    if (e->next == NULL) {
                        printf("\n >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>VICTOIRE<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                        libere_jeu(jeu);
                        exit(0);
                    }
                    jeu->etudiants = e->next;
                    if (e->next_line != NULL) {
                        e->next_line->prev_line = e->prev_line;
                        if (e->prev_line == NULL) {
                            modifier_ligne_i_etudiant(e->ligne, e->next_line, plateau);
                        }
                        else {
                            e->prev_line->next_line = e->next_line;
                        }
                    }
                    else {
                        if (e->prev_line == NULL) {
                            modifier_ligne_i_etudiant(e->ligne, NULL, plateau);
                        }
                        else {
                            e->prev_line->next_line = NULL;
                        }
                    }
                    // free(e);
                }
            }
            else {
                e = e->next;
                while (e != NULL) {
                    if (e->ligne == t->ligne && t->position <= e->position && (e->position <= 15 || (e->position == 16 && e->enDeplacement == 1) ) ) {
                        e->pointsDeVie -= degat(t->type);
                        if (e->pointsDeVie <= 0) {
                            jeu->score += (gain(e->type)*exp(-0.05*jeu->tour)*1/(log(1+nb_tourelles)));
                            jeu->cagnotte += gain(e->type);
                            prev->next = e->next;
                            if (e->prev_line == NULL) {
                                modifier_ligne_i_etudiant(e->ligne, e->next_line, plateau);
                            }
                            else {
                                e->prev_line->next_line = e->next_line;
                            }
                            if (e->next_line != NULL) {
                                e->next_line->prev_line = e->prev_line;
                            }
                        }
                        // free(e);
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
                nb_tourelles -= 1;
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
                // free(t);
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
                Tourelle *t = ligne_i_tourelle(e->ligne, defense);
                if (t != NULL) {
                    while (t->next_line != NULL && t->next_line->position <= e->position) {
                        t = t->next_line;
                    }
                    if (t->position == 15) {
                        e->enCombat = 1;
                    }
                }
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