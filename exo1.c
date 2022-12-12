
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "tp_note.h"


// Fonction qui défini le logement x. 
logement creerlogement(logement logement_x){
    printf("Premièrement, veuillez renseigner les caractéristques de votre logement :\n");
    printf("Quel est la capacite de votre logement ? \n");
    scanf("%d", &logement_x.capacite);
    printf("Quel est le nombre de chambres de votre logement ? \n");
    scanf("%d", &logement_x.chambres);
    printf("Quel est le nombre de salles de bain de votre logement ? \n");
    scanf("%d", &logement_x.salle_bain);
    printf("Quel est le nombre de lits de votre logement ?\n");
    scanf("%d", &logement_x.lit);
    printf("Quel est le nombre de nuis minimales de votre logement ?\n");
    scanf("%d", &logement_x.min_nuit);
    printf("Quel est le nombre de nuits maximales de votre logement ?\n");
    scanf("%d", &logement_x.max_nuit);
    printf("Quel est le nombre de reviews de votre logement ?\n");
    scanf("%d", &logement_x.nb_review);
    logement_x.nb_logement = 7920;
    logement_x.capacite = 5;
    logement_x.chambres =  8;
    logement_x.salle_bain = 5;
    logement_x.lit = 12;
    logement_x.prix = 450;
    logement_x.min_nuit = 7;
    logement_x.max_nuit = 7;
    logement_x.nb_review = 100;   
    return logement_x;
}

//Fonction qui trouve le nombre de logements du fichier de donnees airbnb_donnees_propres
int trouver_nb_ligne(){
    int nb_ligne = 0;
    FILE* donnees = fopen("airbnb_donnees_propre.csv", "r");
    char ligne[100];
    while(fgets(ligne, 100, donnees) != NULL){
        nb_ligne++;
    }
    fclose(donnees);
    return nb_ligne-1;    // On retourne le nombre de ligne-1, car la première ligne du fichier n'est pas un logement. 

}


//Fonction qui remplit notre tableau de distance en fonction de la caractéristique voulu, et le prix des logements concernés.  
void remplir_tab_distance(logement tab[], int nb_lignes, logement logement_x, int choix){
    FILE* donnees = fopen("airbnb_donnees_propre.csv", "rt");   //rt pour ouvrir en lecture, en mode texte. 
    int position_tableau = 0; 
    int position_tableau_prix = 0;
    const char* separateur = ",";                             //Séparateur de chaque donnees dans une ligne du fichier
    int position=1;                                     
    if(choix == 5 || choix == 6 || choix == 7){             //Si la caracéristique choisie se trouve après le prix dans le fichier de données, on augmente 
        choix+=2;                                           //de 1 pour obtenir les donnees correspondantes. 
    }
    else{
        choix++;
    }
    if(donnees == NULL){
        printf("erreur");
        exit(3);
    }
    char ligne[100];
    while(fgets(ligne, 100, donnees) != NULL){                      //On sépare la récuperation des donnees ligne par ligne         
        char *unite = strtok(ligne, separateur);                    //On découpe la ligne en plusieurs parties, selon notre séparateur ",". 
        position=1;
        while(unite != NULL){
            if(position == choix){                                 //Si on se trouve à la position de la donnée recherchée
                int unite_nb = atoi(unite);                        //On transforme le char* unite en int.
                switch(choix){                                     //Selon la caractéristique choisie, on récupère la donnée. 
                    case 2:
                        tab[position_tableau].capacite = abs(logement_x.capacite - unite_nb);
                        break;
                    case 3:
                        tab[position_tableau].chambres = abs(logement_x.chambres - unite_nb);
                        break;
                    case 4:
                        tab[position_tableau].salle_bain = abs(logement_x.salle_bain - unite_nb);
                        break;
                    case 5: 
                        tab[position_tableau].lit = abs(logement_x.lit - unite_nb);
                        break;
                    case 7:
                        tab[position_tableau].min_nuit = abs(logement_x.min_nuit - unite_nb);
                        break;
                    case 8:
                        tab[position_tableau].max_nuit = abs(logement_x.max_nuit - unite_nb);
                        break;
                    case 9: 
                        tab[position_tableau].nb_review = abs(logement_x.nb_review - unite_nb);
                        break;
                    default:
                        printf("erreur : problème lié au choix du comparateur. (fonction remplir tab)");
                }
                position_tableau++;
            }
            if(position == 6){                     //On rempli le tableau des prix, peu importe la caractéristique choisie. 
                int unite_nb = atoi(unite);
                tab[position_tableau_prix].prix = unite_nb;
                position_tableau_prix++;
            }
            unite = strtok (NULL, separateur);
            position++;
        
        }
    }
    fclose(donnees);
}


//Fonction qui lit le tableau, en fonction de la caractéristique choisie. 
void lire_tableau(logement tab[], int nb_lignes, int choix){
    switch(choix){
        case 1:
            for(int i=0;i<=nb_lignes-1;i++){
                printf("%d |", tab[i].capacite);
            }
            break;
        case 2:
            for(int i=0;i<=nb_lignes-1;i++){
                printf("%d |", tab[i].chambres);
            }
            break;
        case 3:
            for(int i=0;i<=nb_lignes-1;i++){
                printf("%d |", tab[i].salle_bain);
            }          
            break;
        case 4: 
            for(int i=0;i<=nb_lignes-1;i++){
                printf("%d |", tab[i].lit);
            }            
            break;
        case 5:
            for(int i=0;i<=nb_lignes-1;i++){
                printf("%d |", tab[i].min_nuit);
            }            
            break;
        case 6:
            for(int i=0;i<=nb_lignes-1;i++){
                printf("%d |", tab[i].max_nuit);
            }            
            break;
        case 7: 
            for(int i=0;i<=nb_lignes-1;i++){
                printf("%d |", tab[i].nb_review);
            }            
            break;
        default:
            printf("erreur : problème lié au choix du comparateur. (fonction lire tableau)");
    }
    for(int i=0;i<=nb_lignes-1;i++){
        printf("%d |", tab[i].prix);
    }   
}


//Fonction qui randomise le tableau de la caractéristique choisie. 
void randomiser_tableau(logement tab[], int nb_lignes, int choix){
    int temp;
    int nb;
    for(int i=0;i<=nb_lignes;i++){
        nb = rand() % nb_lignes;       //Chiffre aléatoire entre 0 et le nombre de logements existant. 
        switch(choix){
            case 1:
                temp = tab[i].capacite;
                tab[i].capacite = tab[nb].capacite;
                tab[nb].capacite = temp;
                break;
            case 2:
                temp = tab[i].chambres;
                tab[i].chambres = tab[nb].chambres;
                tab[nb].chambres = temp;
                break;
            case 3:
                temp = tab[i].salle_bain;
                tab[i].salle_bain = tab[nb].salle_bain;
                tab[nb].salle_bain = temp;                
                break;
            case 4: 
                temp = tab[i].lit;
                tab[i].lit = tab[nb].lit;
                tab[nb].lit = temp;
                break;
            case 5:
                temp = tab[i].min_nuit;
                tab[i].min_nuit = tab[nb].min_nuit;
                tab[nb].min_nuit = temp;
                break;
            case 6:
                temp = tab[i].max_nuit;
                tab[i].max_nuit = tab[nb].max_nuit;
                tab[nb].max_nuit = temp;
                break;
            case 7: 
                temp = tab[i].nb_review;
                tab[i].nb_review = tab[nb].nb_review;
                tab[nb].nb_review = temp;
                break;
            default:
                printf("erreur : problème lié au choix du comparateur (fct random).");
        }
        temp = tab[i].prix;
        tab[i].prix = tab[nb].prix;
        tab[nb].prix = temp;
    }
}

//Fonction qui trie le tableau de la caractéristique choisie. 
void triBulle(int nb_lignes, logement tab[], int choix){
    int i,j,temp;
    switch(choix){
        case 1: 
            for(j=1;j<=nb_lignes;j++){ 
                for(i=0;i<nb_lignes-1;i++){
                    if ( tab[i].capacite > tab[i+1].capacite ) {
                            temp = tab[i].capacite;
                            tab[i].capacite = tab[i+1].capacite;
                            tab[i+1].capacite = temp;
                            temp = tab[i].prix;
                            tab[i].prix = tab[i+1].prix;
                            tab[i+1].prix = temp;
                            
                        }
                    }
                }
            break;
        case 2: 
            for(j=1;j<=nb_lignes;j++){ 
                for(i=0;i<nb_lignes-1;i++){
                    if ( tab[i].chambres > tab[i+1].chambres ) {
                            temp = tab[i].chambres;
                            tab[i].chambres = tab[i+1].chambres;
                            tab[i+1].chambres = temp;
                            temp = tab[i].prix;
                            tab[i].prix = tab[i+1].prix;
                            tab[i+1].prix = temp;
                        }
                    }
                }
            break;
        case 3: 
            for(j=1;j<=nb_lignes;j++){ 
                for(i=0;i<nb_lignes-1;i++){
                    if ( tab[i].salle_bain > tab[i+1].salle_bain ) {
                            temp = tab[i].salle_bain;
                            tab[i].salle_bain = tab[i+1].salle_bain;
                            tab[i+1].salle_bain = temp;
                            temp = tab[i].prix;
                            tab[i].prix = tab[i+1].prix;
                            tab[i+1].prix = temp;
                        }
                    }
                }               
            break;
        case 4: 
            for(j=1;j<=nb_lignes;j++){ 
                for(i=0;i<nb_lignes-1;i++){
                    if ( tab[i].lit > tab[i+1].lit ) {
                            temp = tab[i].lit;
                            tab[i].lit = tab[i+1].lit;
                            tab[i+1].lit = temp;
                            temp = tab[i].prix;
                            tab[i].prix = tab[i+1].prix;
                            tab[i+1].prix = temp;
                        }
                    }
                }
            break;
        case 5: 
            for(j=1;j<=nb_lignes;j++){ 
                for(i=0;i<nb_lignes-1;i++){
                    if ( tab[i].min_nuit > tab[i+1].min_nuit ) {
                            temp = tab[i].min_nuit;
                            tab[i].min_nuit = tab[i+1].min_nuit;
                            tab[i+1].min_nuit = temp;
                            temp = tab[i].prix;
                            tab[i].prix = tab[i+1].prix;
                            tab[i+1].prix = temp;
                        }
                    }
                }
            break;
        case 6:
            for(j=1;j<=nb_lignes;j++){ 
                for(i=0;i<nb_lignes-1;i++){
                    if ( tab[i].max_nuit > tab[i+1].max_nuit ) {
                            temp = tab[i].max_nuit;
                            tab[i].max_nuit = tab[i+1].max_nuit;
                            tab[i+1].max_nuit = temp;
                            temp = tab[i].prix;
                            tab[i].prix = tab[i+1].prix;
                            tab[i+1].prix = temp;
                        }
                    }
                }
            break;
        case 7: 
            for(j=1;j<=nb_lignes;j++){ 
                for(i=0;i<nb_lignes-1;i++){
                    if ( tab[i].nb_review > tab[i+1].nb_review ) {
                            temp = tab[i].nb_review;
                            tab[i].nb_review = tab[i+1].nb_review;
                            tab[i+1].nb_review = temp;
                            temp = tab[i].prix;
                            tab[i].prix = tab[i+1].prix;
                            tab[i+1].prix = temp;
                        }
                    }
                }
            break;
        default:
            printf("Erreur : problème lié au choix du compatateur (fonction tri bulle)");
    }

}

//Fonction qui trouve le prix idéal de notre logement, en fonction de la caractéristique choisie et du nombre de logements à comparer. 
float trouver_prix_moyen(logement tab[], int choix_comparation, int choix_comparateur){
    int somme = 0;
    for(int i=0;i<=choix_comparateur-1;i++){
        somme += tab[i].prix;
    }
    float prix_moyen = (float) somme/choix_comparateur;                 //Moyenne des X logements à comparer. 
    return prix_moyen;
}



void exo1(){
    printf("\n\nBienvenue ! Cet algorithme calcule le prix moyen de votre logement en fonction des caracteristiques qui le compose. \n\n");
    int choix_comparateur;
    int choix_comparation = 0;
    srand( time( NULL ) );
    logement logement_x;
    logement_x = creerlogement(logement_x);
    printf("\n\nPour choisir avec quelle caractéristique vous voulez comparer votre logement,");
    printf("choisissez : \n - 1 pour comparer votre logement par rapport a la capacite de ce dernier \n - 2 pour comparer votre logement par rapport au nombre de chambres \n - 3 pour comparer votre logement par rapport au nombre de salles de bain \n - 4 pour comparer votre logement par rapport au nombre lits \n - 5 pour comparer votre logement par rapport au nombre de nuits minimales \n - 6 pour comparer votre logement par rapport au nombre de nuits maximales \n - 7 pour comparer votre logement au nombre de reviews\n");
    scanf("%d", &choix_comparation);
    while(choix_comparation < 1 || choix_comparation > 7){
        printf("Erreur : veuillez choisir un nombre entre 1 et 7.");
        scanf("%d", &choix_comparation);
    }
    printf("Avec combien de logement voulez-vous comparer votre logement ?");
    scanf("%d", &choix_comparateur);
    while(choix_comparation < 1 || choix_comparation > 7500){
        printf("Erreur : veuillez choisir un nombre entre 1 et 7500.");
        scanf("%d", &choix_comparation);
    }
    int nb_lignes = trouver_nb_ligne();
    logement distance_similarite_x[nb_lignes];
    int tmp[nb_lignes];
    remplir_tab_distance(distance_similarite_x, nb_lignes, logement_x, choix_comparation);
    randomiser_tableau(distance_similarite_x, nb_lignes, choix_comparation);
    triBulle(nb_lignes, distance_similarite_x, choix_comparation);
    float prix = trouver_prix_moyen(distance_similarite_x, choix_comparation, choix_comparateur);
    printf("\n\nAprès avoir comparé votre logement avec %d autres sur notre base de données, nous estimons que le prix de votre logement devrait être : %.2f €\n", choix_comparateur, prix);
}


