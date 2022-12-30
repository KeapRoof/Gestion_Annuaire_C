#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//commentaire doxygen (sur 0.375/20) sur l'API
//assert obligatoire
//fichier .h & .c séparés

int affichage_console();
int ajouter_client();
// void modifier_mail_client(char nom_annuaire, char mel_p, char nv_mel_p);

int main(void)
{    
    int res = affichage_console();
    if (res == 1)
    {
        ajouter_client();
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
    int n = 0;
    printf("---------------Bonjour !---------------");
    printf("\n");
    printf("1. ajouter un client\n");
    printf("2. modifier le mail d'un client\n");
    printf("---------------------------------------\n");
    scanf("%d", &n);
    if (0 < n < 3);
    {
        return n;        
    }
}


// void modifier_mail_client(nom_annuaire, mel_p, nv_mel_p)
// {
//     // modification de l'adresse mail d'un contact

//     FILE *fichier = fopen("annuaire.csv", "r+");

//     if(fichier == NULL){
//         perror(fichier);
//         exit(EXIT_FAILURE);
//     }

//     // Vérification de l'existence du mail

//     char ligne[100];
//     int doublon = 0;

//     while(fgets(ligne, 100, fichier) != NULL)
//     {
//         if(strstr(ligne, mel_p) != NULL)
//         {
//             doublon = 1;
//             break;
//         }
//         else
//             printf("le mail n'existe pas !\n");
//     }

//     // Modification du mail dans le fichier

//     if(doublon == 1)
//         fprintf(fichier, "%s",nv_mel_p);
    
//     // Fermeture du fichier

//     fclose(fichier);
// }

void ajout_de_cli(const char* nom_annuaire, const char* nom_p, const char* prenom_p, const char* code_postal_p, const char* ville_p, const char* telephone_p, const char* mel_p, const char* profession_p) {
  // Auteur : Haithem HADJ AZZEM
  // Ouvre le fichier en mode "a" (ajout)
  FILE* file = fopen(nom_annuaire, "a");
  if (file == NULL) {
    printf("Impossible d'ouvrir le fichier\n");
    return;
  }
  // ecrit les informations du client dans le fichier
  fprintf(file, "\n%s,%s,%s,%s,%s,%s,%s,", nom_p, prenom_p, code_postal_p, ville_p, telephone_p, mel_p, profession_p);
  printf("Le client a bien été ajouté à l'annuaire");
  // Ferme le fichier
  fclose(file);
}

void supprimer_client(const char* nom_annuaire, const char* mel_p) {
    // Auteur : Haithem HADJ AZZEM

    // Ouvre le fichier en mode "r" (lecture)
    FILE* file = fopen(nom_annuaire, "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }
    // Ouvre un fichier temporaire en mode "w" (écriture)
    FILE* temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf("Impossible d'ouvrir le fichier temporaire\n");
        return;
    }
    // Lit le fichier ligne par ligne
    char line[1024];
    while (fgets(line, 1024, file)) {
        // Si la ligne ne contient pas l'adresse mail, on l'écrit dans le fichier temporaire
        if (!strstr(line, mel_p)) {
        fputs(line, temp);
        }
    }
    // Ferme les fichiers
    fclose(file);
    fclose(temp);
    // Supprime l'ancien fichier
    remove(nom_annuaire);
    // Renomme le fichier temporaire
    rename("temp.csv", nom_annuaire);
    printf("Client supprimé\n");
    }