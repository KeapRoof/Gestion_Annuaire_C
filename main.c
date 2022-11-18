#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    // Ouverture du fichier csv
    FILE *fichier = fopen("annuaire.csv", "a+");
    if(fichier == NULL){
        printf("Le fichier n'existe pas");
        return 0;
    }
    // Ajout d'une ligne dans le fichier csv sans doublon

    // Déclaration des variables
    char nom[20],prenom[20],cp[20],ville[20],numero[20],email[20],job[20];
    // Saisie des informations
    printf("Nom : ");
    scanf("%s", nom);
    printf("Prenom : ");
    scanf("%s", prenom);
    printf("Code postal : ");
    scanf("%s", cp);
    printf("Ville : ");
    scanf("%s", ville);    
    printf("Numero : ");
    scanf("%s", numero);
    printf("Email : ");
    scanf("%s", email);
    printf("Job : ");
    scanf("%s", job);
    // Vérification de l'existence du contact
    char ligne[100];
    int doublon = 0;
    while(fgets(ligne, 100, fichier) != NULL){
        if(strstr(ligne, nom) != NULL && strstr(ligne, prenom) != NULL){
            doublon = 1;
            printf("Ce contact existe deja !");
            break;
        }
    }
    // Ajout du contact dans le fichier
    if(doublon == 0)
        fprintf(fichier, "\n%s;%s;%s;%s;%s;%s;%s", nom, prenom, numero, cp, ville, email, job);   
    return 0;
}