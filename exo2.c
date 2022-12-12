#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "tp_note.h"




POrdonnanceur O=NULL, queue=NULL;
Processus p;
int fini =2, type =0, type2=0, nb=0, i=0;

//Fonction permettant de créer un noeud avec le processus à ajouter à l'ordonnanceur
POrdonnanceur creer_noeud(Processus p, POrdonnanceur suiv){
    POrdonnanceur pointeur;
    if ((pointeur = MALLOC(Ordonnanceur)) == NULL){
        fprintf(stderr, "ERREUR ALLOCATION MEMOIRE");
        exit(1);
    }
    pointeur->P = p;
    pointeur->suiv = suiv;
    return pointeur;
}

//Affiche la liste des processus dans l'ordonnanceur
void aff_liste_proc(POrdonnanceur O){
    int i=1;
    if (!O) puts("Aucun processus");            //Signale que l'ordonnanceur est vide
    else{
        while (O)
        {
            printf("%d / PROCESSUS %s - DUREE : %ds - PRIORITE : %d\n",i, O->P.nom, O->P.duree, O->P.priorite);
            O = O->suiv;
            i++;
        }
        puts("");
    }
}

//Ajoute un processus à l'odonnanceur de type FIFO
void ajout_activite(Processus p, POrdonnanceur *tete, POrdonnanceur *queue){
    POrdonnanceur ptr = creer_noeud(p, NULL);
    if (*queue) (*queue)->suiv = ptr;
    else *tete = ptr;
    *queue = ptr;
}

//Ajoute un processus à l'odonnanceur par priorité
void ajout_activite2(Processus p, POrdonnanceur *tete){
    POrdonnanceur ptr = *tete;
    POrdonnanceur noeud = creer_noeud(p, NULL);
        if (!*tete){                            //Si l'ordonnanceur est vide, 
        *tete = noeud;                          //alors le processus ajouté est placé à la tête de l'ordonnanceur
    }else if (ptr->P.priorite > p.priorite || (ptr->P.priorite == p.priorite && ptr->P.duree > p.duree)){
        noeud->suiv = ptr;                      //Si le processus ajouté à une priorité plus forte ou si il à une priorité égale mais
        *tete = noeud;                          //une durée plus petite, alors il est ajouté à la tête
    }else{
        while (ptr->suiv != NULL && ptr->suiv->P.priorite < p.priorite ){
            ptr=ptr->suiv;                      //Tant que la priorité est plus forte que celle du processus suivant, 
        }                                       //on avance dans l'odonnanceur
        while (ptr->suiv != NULL && (ptr->suiv->P.priorite == p.priorite && ptr->suiv->P.duree <= p.duree))
        {                                       //Si la priorité du nouveau processus est égale mais la durée est supérieure
            ptr=ptr->suiv;                      //on avance dans l'ordonnanceur
        }
        noeud->suiv = ptr->suiv;                //Une fois la place du nouveau processus trouvé, on l'insère dans l'odonnanceur
        ptr->suiv = noeud;
    }
}

//Effectue un tour d'ordonnancemment
void step(POrdonnanceur *tete, int temps){
    POrdonnanceur ptr= *tete;
    ptr->P.duree--;                             //On réduit la durée du processus en cours
    if (ptr->P.duree == 0)                      //Si la durée du processus en cours passe à zéro
    {                                           //on passe au processus suivant
        *tete = ptr->suiv;
        free(ptr);
        printf("\n\n\n\nt = %ds : \n",temps);   //Puis ffiche le temps écoulé
        if (O)                                  //Si l'ordonnanceur n'est pas vide, on affiche son contenu
        {                                       //puis du nouveau processus à être executé
            printf("Voici les processus dans votre Ordonnanceur :\n");
            aff_liste_proc(*tete);
            printf("EXECUTION : %s - DUREE : %ds - PRIORITE : %d\n", O->P.nom, O->P.duree, O->P.priorite);
        }else{
            aff_liste_proc(O);                  //Si l'ordonnanceur est vide, on l'affiche
        }
    }
}

//Effectue la procédure step jusqu'à ce que l'ordonnanceur soit vide
void run(POrdonnanceur *tete){
    printf("\n\n\n\n\n--------------------------------------------------\nVoici les processus dans votre Ordonnanceur :\n");
    aff_liste_proc(*tete);
    printf("Demarrage de l execution.\n");
    int temps=1;
    printf("\nt = %ds : \n",temps-1);           //Affichage du temps=0 puis du premier processus à être exécuté
    printf("EXECUTION : %s - DUREE : %ds - PRIORITE : %d\n", O->P.nom, O->P.duree, O->P.priorite);
    while (*tete != NULL)                       //tourne jusqu'à ce que l'ordonnanceur soit vite
    {
        step(tete, temps);
        temps++;
        sleep(1);
    }
    printf("\nFin de l execution.\n");
}

int exo2(){
    srand(time(NULL));
                                                //choix du type d'ordonnanceur
    printf("\n\nQuel type d'ordonnanceur voulez vous executer ?\n1 - Ordonnanceur par ordre d'arrivee\n2 - Ordonnanceur par priorite\n");
    scanf("%d", &type);
    while (type != 1 && type != 2)
    {
        printf("\nErreur, quel ordonnanceur avez-vous choisi ?");
        scanf("%d", &type);
    }
                                                //choix du type de création des processus
    printf("\nComment voulez-vous choisir les processus ?\n1 - Je veux creer mes propres processus\n2 - Je veux qu'ils soient crees aleatoirement\n");
    scanf("%d", &type2);
    while (type2 != 1 && type2 != 2)
    {
        printf("\nErreur, choisissez un combre entre 1 et 2 ?");
        scanf("%d", &type2);
    }

    switch (type)
    {
    case 1 :                                //ORDONNANCEUR FIFO
        switch (type2)
        {
        case 1 :
/*----------------------------------PROCESSUS CHOISIS PAR L'UTILISATEUR-----------------------------------*/
            while (fini==2)
            {
                printf("\nQuel est le nom du nouveau processus ?\n");         //On demande à l'utilisateur les informations
                scanf("%s", p.nom);                                         //du nouveau procéssus
                printf("Quel est la duree du nouveau processus ?\n");
                scanf("%d", &p.duree);
                printf("Quel est la priorite du nouveau processus ?\n");
                scanf("%d", &p.priorite);
                ajout_activite(p,&O,&queue);                                //On ajoute le processus créé à l'ordonnanceur
                printf("\nVoici les processus dans votre Ordonnanceur :\n");  //Puis on affiche la liste des processus dans
                aff_liste_proc(O);                                          //l'ordonnanceur 

                printf("\nAvez-vous termine ?\n1 - OUI\n2 - NON\n");
                scanf("%d", &fini);
                while (fini != 1 && fini != 2)
                {
                    printf("\nErreur, avez-vous termine ?");
                    scanf("%d", &fini);
                }
                
            }
            run(&O);                                                        //On execute les processus
            break;
        case 2 :
/*---------------------------------------PROCESSUS ALEATOIRES--------------------------------------------*/
            printf("\nCombien de processus voulez-vous ajouter ?\n");
            scanf("%d", &nb);
            for ( i = 0; i < nb; i++)                                       //On génère le nombre de processus
            {                                                               //demandé avec des valeurs aléatoires
                sprintf(p.nom,"p%d",i+1);
                p.duree=1+rand() % (5);                                     //durée allant de 1 à 5 inclus
                p.priorite=rand() % (5+1);                                  //priorité allant de 0 à 5 inclus
                ajout_activite(p,&O,&queue);                                //Ajout du processus à l'ordonnanceur
            }
            printf("\nVoici les processus dans votre Ordonnanceur :\n");
            aff_liste_proc(O);
            run(&O);                                                        //On execute les processus
            break;
        default:
            break;
        }
        break;

    case 2 :                            //ORDONNANCEUR PAR PRIORITE
        switch (type2)
        {
        case 1 :
/*----------------------------------PROCESSUS CHOISIS PAR L'UTILISATEUR-----------------------------------*/
            while (fini==2)
            {
                printf("\nQuel est le nom du nouveau processus ?\n");         //On demande à l'utilisateur les informations
                scanf("%s", p.nom);                                         //du nouveau procéssus
                printf("Quel est la duree du nouveau processus ?\n");
                scanf("%d", &p.duree);
                printf("Quel est la priorite du nouveau processus ?\n");
                scanf("%d", &p.priorite);
                ajout_activite2(p,&O);                                      //On ajoute le processus créé à l'ordonnanceur
                printf("\nVoici les processus dans votre Ordonnanceur :\n");  //Puis on affiche la liste des processus dans
                aff_liste_proc(O);                                          //l'ordonnanceur triés par priorité

                printf("\nAvez-vous termine ?\n1 - OUI\n2 - NON\n");
                scanf("%d", &fini);
                while (fini != 1 && fini != 2)
                {
                    printf("\nErreur, avez-vous termine ?");
                    scanf("%d", &fini);
                }
                
            }
            run(&O);                                                        //On execute les processus
            break;
        case 2 :

/*---------------------------------------PROCESSUS ALEATOIRES--------------------------------------------*/
            printf("\nCombien de processus voulez-vous ajouter ?\n");
            scanf("%d", &nb);
            for ( i = 0; i < nb; i++)                                       //On génère le nombre de processus
            {                                                               //demandé avec des valeurs aléatoires
                sprintf(p.nom,"p%d",i+1);
                p.duree=1+rand() % (5);                                     //durée allant de 1 à 5 inclus
                p.priorite=rand() % (5+1);                                  //priorité allant de 0 à 5 inclus
                ajout_activite2(p,&O);                                      //Ajout du processus à l'ordonnanceur par priorité
            }
            printf("\nVoici les processus dans votre Ordonnanceur :\n");
            aff_liste_proc(O);
            run(&O);                                                        //On execute les processus
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }

    return 0;
}
