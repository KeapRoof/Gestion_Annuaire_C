/**
 * @file main.c
 * @author Clément, Haithem, Aziz
 * @brief Fichier main, qui contient l'interface de l'API
 */

#include "functions.h"

// Assert obligatoire

/**
 * @brief Interface de l'API
 * 
 * @return int 
 */
int main(void) {
    // Auteur : Clement LE GOASTER
    char* nom_annuaire = malloc(100 * sizeof(char));
    char* nom_p = malloc(100 * sizeof(char));
    char* prenom_p = malloc(100 * sizeof(char));
    char* code_postal_p = malloc(100 * sizeof(char));
    char* ville_p = malloc(100 * sizeof(char));    
    char* telephone_p = malloc(100 * sizeof(char));    
    char* mel_p = malloc(100 * sizeof(char));
    char* nv_mel_p = malloc(100 * sizeof(char));
    char* profession_p = malloc(100 * sizeof(char));
    char* nom_champ = malloc(100 * sizeof(char));
    char* val_chaine = malloc(100 * sizeof(char));
    if (nom_annuaire == NULL || nom_p ==  NULL || prenom_p == NULL || code_postal_p == NULL || ville_p == NULL || telephone_p == NULL || mel_p == NULL || nv_mel_p == NULL || profession_p == NULL || nom_champ == NULL || val_chaine == NULL) {
        printf("Erreur lors de l'allocation de la mémoire\n");
        return -1; // Erreur car la mémoire n'a pas pu être allouée
    }
    int choix;
    int quit = 0;
    while (quit == 0) {
        printf("\n");
        printf("-------------Que voulez-vous faire ?--------------\n");
        printf("0. Afficher l'annuaire\n");
        printf("1. Ajouter un nouveau client\n");
        printf("2. Modifier le mel d'un client\n");
        printf("3. Modifier autres elements que le mel d'un client\n");
        printf("4. Supprimer un client\n");
        printf("5. Trier les clients par leur nom\n");
        printf("6. Filtrer les clients avec des données manquantes\n");
        printf("7. Filtrer un champ\n");
        printf("8. Filtrer en combinant deux champs\n");
        printf("9. Quitter le programme\n");
        printf("--------------------------------------------------\n");
        printf("-> ");
        scanf("%d", &choix);
        switch (choix)
        {
        case 0:
            printf("Entrez le nom de l'annuaire à afficher (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            afficher_annuaire_clients(nom_annuaire);
            break;
        case 1:
            printf("Entrez le nom de l'annuaire où ajouter le client (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            printf("Entrez le nom du client : \n");
            scanf("%s", nom_p);
            printf("Entrez le prenom du client : \n");
            scanf("%s", prenom_p);
            printf("Entrez le code postal du client : \n");
            scanf("%s", code_postal_p);
            printf("Entrez la ville où réside le client : \n");
            scanf("%s", ville_p);
            printf("Entrez le numéro de téléphone du client : \n");
            scanf("%s", telephone_p);
            printf("Entrez le mail du client : \n");
            scanf("%s", mel_p);
            printf("Entrez la profession du client : \n");
            scanf("%s", profession_p);
            ajouter_client(nom_annuaire, nom_p, prenom_p, code_postal_p, ville_p, telephone_p, mel_p, profession_p);
            break;
        case 2:
            printf("Entrez le nom de l'annuaire à lire (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            printf("Entrez le mail à remplacer : \n");
            scanf("%s", mel_p);
            printf("Entrez le nouvel email : \n");
            scanf("%s", nv_mel_p);
            modifier_mel_client(nom_annuaire, mel_p, nv_mel_p);
            break;
        case 4:
            printf("Entrez le nom de l'annuaire à lire (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            printf("Entrez le mail du client à supprimer : \n");
            scanf("%s", mel_p);
            supprimer_client(nom_annuaire, mel_p);
            break;
        case 5:
            printf("Entrez le nom de l'annuaire à trier (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            trier_clients_par_nom(nom_annuaire);
            break;
        case 7:
            printf("Entrez le nom de l'annuaire à trier (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            printf("Entrez le nom du champs à trier : \n");
            scanf("%s", nom_champ);
            printf("Entrez la valeur à rechercher : \n");
            scanf("%s", val_chaine);
            filtrer_un_champ(nom_annuaire, nom_champ, val_chaine);
        case 9:
            printf("Vous quittez le programme...\n");
            printf("\n");
            quit = 1;
            break;
        default :
            printf("Erreur lors de la saisie OU fonctionnalité non disponible pour le moment\n");
            return -1; // Erreur lors de la saisie 
        }
    }
    free(nom_annuaire);
    free(nom_p);
    free(prenom_p);
    free(code_postal_p);
    free(ville_p);
    free(telephone_p);
    free(mel_p);
    free(nv_mel_p);
    free(profession_p);
    free(nom_champ);
    free(val_chaine);
    return 0; // Retour normal
}