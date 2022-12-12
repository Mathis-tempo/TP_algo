#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "tp_note.h"



int main(){
    int choix_exo;
    printf("Bonjour, Voici le projet d'algorithmie de Mahis TEMPO et Ella GADELLE. Veuillez entrez 1 ou 2 pour executer respectivement les exercices 1 et 2 du TP.");
    scanf("%d", &choix_exo);
    while(choix_exo != 1 && choix_exo != 2){
        printf("\n\nErreur : Veuillez choisir 1 ou 2.");
        scanf("%d", &choix_exo);
    }
    if(choix_exo == 1){
        exo1();
    }
    if(choix_exo == 2){
        exo2();
    }
}   



