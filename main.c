#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//commentaire doxygen (sur 0.375/20) sur l'API
//assert obligatoire
//fichier .h & .c séparés

int affichage_console(void);
int ajouter_client();
void modifier_mail_client();

int main(void)
{    
    int res = affichage_console();
    if (res == 1)
    {
        ajouter_client();
    }
    if (res == 2)
    {
        modifier_mail_client();
    } else {
        printf("Erreur !");
    }
}

int ajouter_client()
{
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
            printf("Ce contact existe deja !\n");
            break;
        }
    }

    // Ajout du contact dans le fichier

    if(doublon == 0)
        fprintf(fichier, "\n%s;%s;%s;%s;%s;%s;%s", nom, prenom, numero, cp, ville, email, job);   
    return 0;
}

int affichage_console(void)
{
    //afficher une console pour faire des choix de l'API
    int n = 0;
    printf("---------------Bonjour !---------------");
    printf("\n");
    printf("1. Ajouter un client\n");
    printf("2. Modifier le mail d'un client\n");
    scanf("%d", &n);
    printf("---------------------------------------\n");
    if (0 < n < 3);
    {
        return n;
    }
}

void modifier_mail_client()
{
    char mel_p[20], nv_mel_p[20];

    // modification de l'adresse mail d'un contact
    FILE *fichier = fopen("annuaire.csv", "r+");

    if(fichier == NULL){
        perror("Erreur :");
        exit(EXIT_FAILURE);
    }

    printf("Email : ");
    scanf("%s", mel_p);

    // Vérification de l'existence du mail

    char ligne[100];
    int doublon = 0;

    while(fgets(ligne, 100, fichier) != NULL)
    {
        if(strstr(ligne, mel_p) != NULL)
        {
            doublon = 1;
            break;
        }
        else {
            printf("Le mail n'existe pas !\n");
            break;
        }
    }

    // Modification du mail dans le fichier

    if(doublon == 1)
        printf("Nouvel email : ");
        scanf("%s", nv_mel_p);
        fprintf(fichier,"%s",nv_mel_p);
    
    // Fermeture du fichier

    fclose(fichier);
}