#ifndef UTILS_H
    #define UTILS_H

    typedef struct tourelle {
        int type;
        int pointsDeVie;
        int ligne;
        int position;
        int prix;
        struct tourelle* next;
        struct tourelle* next_line;
    } Tourelle;

    typedef struct etudiant {
        int type;
        int pointsDeVie;
        int ligne;
        int position;
        int vitesse;
        int tour;
        int enDeplacement;
        int enCombat;
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

    typedef struct {
        Etudiant* ligne1;
        Etudiant* ligne2;
        Etudiant* ligne3;
        Etudiant* ligne4;
        Etudiant* ligne5;
        Etudiant* ligne6;
        Etudiant* ligne7;
    } Plateau;

        typedef struct {
        Tourelle* ligne1;
        Tourelle* ligne2;
        Tourelle* ligne3;
        Tourelle* ligne4;
        Tourelle* ligne5;
        Tourelle* ligne6;
        Tourelle* ligne7;
    } Defense;

    extern int nb_etudiants;



    void lire_fichier(const char* nom_fichier, Jeu* jeu, Plateau *plateau);
    void libere_jeu(Jeu *jeu);
    int afficher_menu();
    int visualiser_vague(Jeu *jeu, Plateau *plateau);

    int prix(char);
    void scan_propre(char *output, char* message, int arg_count, ...);

    int creer_tourelle(Jeu *jeu, Tourelle *t, char* infos);
    void ajout(Jeu *jeu, Tourelle *t, Defense *d);

    void placer_tourelles(Jeu *jeu, Defense *defense, Plateau *plateau);
    void afficher_jeu(Jeu *jeu, Plateau *plateau, Defense *defense);
    void apparition(Jeu *jeu, Plateau *plateau, Defense* defense, int tour);
    void tir_tourelles(Jeu *jeu, Plateau *plateau, Defense* defense);
    Etudiant* ligne_i_etudiant(int l, Plateau *plateau);
    void modifier_ligne_i_etudiant(int l, Etudiant *e, Plateau *p);

#endif