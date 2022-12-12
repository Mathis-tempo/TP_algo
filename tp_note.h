

//________________________________________ Exercice 1 ______________________________________________________________

//Structure d'un logement
typedef struct{          
    int nb_logement;
    int capacite;
    int chambres; 
    int salle_bain;
    int lit;
    int prix; 
    int min_nuit;
    int max_nuit;
    int nb_review;
}logement;

logement creerlogement(logement);
int trouver_nb_ligne();
void remplir_tab_distance(logement*, int, logement, int);
void lire_tableau(logement*, int, int);
void randomiser_tableau(logement*, int, int);
void triBulle(int, logement*, int);
float trouver_prix_moyen(logement*, int, int);
void exo1();


//________________________________________ Exercice 2 ______________________________________________________________



//Structure du processus
typedef struct Processus Processus;
struct Processus{
    char nom[11];
    int duree;
    int priorite;
};

//Structure de l'ordonnanceur
typedef struct Ordonnanceur{
    Processus P;
    struct Ordonnanceur *suiv;
} Ordonnanceur;
typedef Ordonnanceur * POrdonnanceur;


POrdonnanceur creer_noeud(Processus, POrdonnanceur);
void aff_liste_proc(POrdonnanceur);
void ajout_activite(Processus, POrdonnanceur *, POrdonnanceur *);
void ajout_activite2(Processus, POrdonnanceur *);
void step(POrdonnanceur *, int);
void run(POrdonnanceur *);
int exo2();

#define MALLOC(x)((x * ) malloc(sizeof(x)))
