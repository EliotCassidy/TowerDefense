#ifndef LECTURE_H
    #define LECTURE_H

    typedef struct tourelle {
        int type;
        int pointsDeVie;
        int ligne;
        int position;
        int prix;
        struct tourelle* next;
    } Tourelle;

    typedef struct etudiant {
        int type;
        int pointsDeVie;
        int ligne;
        int position;
        int vitesse;
        int tour;
        struct etudiant* next;
        struct etudiant* next_line;
        struct etudiant* prev_line;
    } Etudiant;

    typedef struct {
        Tourelle* tourelles;
        Etudiant* etudiants;
        int cagnotte;
        int tour;
    } Jeu;

    extern int nb_etudiants;


    void ajouter_etudiant(Jeu* jeu, Etudiant* etudiant);
    void lire_fichier(const char* nom_fichier, Jeu* jeu);

#endif