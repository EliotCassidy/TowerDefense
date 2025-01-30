#ifndef UTILS_H
    #define UTILS_H

    // Couleurs de base
    #define GREEN   "\x1b[32m"
    #define RESET   "\x1b[0m"
    
    // Couleurs rétro pour les ennemis
    #define CYAN    "\x1b[36m"    // Pour les Etudiants (E)
    #define MAGENTA "\x1b[35m"    // Pour les Redoublants (R)
    #define YELLOW  "\x1b[33m"    // Pour les Conditionnels (C)
    #define BLUE    "\x1b[34m"    // Pour les Zzzz (Z)
    #define RED     "\x1b[31m"    // Pour les Majorants (M)

    typedef struct tourelle {
        int type;
        int pointsDeVie;
        int ligne;
        int position;
        int prix;
        int niveau;
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
        long cagnotte;
        int tour;
        long score;
        int niveau;
        int mode;
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


    extern int nb_tourelles;
    extern int nb_actions;
    extern int max_actions;
    extern int placement;
    extern int pt_ligne;



    void lire_fichier(const char* nom_fichier, Jeu* jeu, Plateau *plateau);
    void supr_sauvegarde(const char* nom_fichier);
    void libere_jeu(Jeu *jeu, char *actions[], char ** instructions);
    int afficher_menu();
    int visualiser_vague(Jeu *jeu, Plateau *plateau);

    int prix(char);
    int scan_propre(char *output);

    int creer_tourelle(Jeu *jeu, Tourelle *t, char* infos);
    void ajout(Jeu *jeu, Tourelle *t, Defense *d);

    void placer_tourelles(Jeu *jeu, Defense* defense, Plateau* plateau, char *actions[], char* nom_fichier, char **instruction, int *n);
    void afficher_jeu(Jeu *jeu, Plateau *plateau, Defense *defense);
    void apparition(Jeu *jeu, Plateau *plateau, Defense* defense, int tour);
    void tir_tourelles(Jeu *jeu, Plateau *plateau, Defense* defense, char *actions[], char **instruction, int *score, char* classement);
    Etudiant* ligne_i_etudiant(int l, Plateau *plateau);
    void modifier_ligne_i_etudiant(int l, Etudiant *e, Plateau *p);
    void tir_ennemies(Jeu *jeu, Plateau *plateau, Defense *defense);
    int avancer_ennemies(Jeu *jeu, Plateau *plateau, Defense *defense);

    int degat(char type);
    int pdv(char type);
    int prix(char type);
    int vitesse(char type);
    int gain(char type);

    Tourelle* ligne_i_tourelle(int l, Defense *defense);
    void save(const char* nomfichier, Jeu* jeu, char * actions[]);
    void lire_instruction(char * nom_fichier, char ** instructions);
    void lire_score(char *classement, int *score);
    void verifier_score(Jeu *jeu, int *scores, char* classement);

    int get_terminal_width(void);
    void print_centered(const char* str);

#endif