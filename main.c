/**
 * @file main.c
 * @author Clément, Haithem, Aziz
 * @brief Fichier main, qui contient l'interface de l'API
 */
/*! \mainpage Page d'accueil
 *
 * Membres du groupe : Clement, Haithem, Aziz
 * 
 * Ce programme en C est une API pour intéragir avec un annuaire.
 * 
 * Pour plus d'informations sur l'installation du programme, rendez-vous sur le README.md (fans Related Pages)
 */

#include "functions.h"

/**
 * @brief Interface de l'API
 * 
 * @return int 
 */
int main(void) {
    // Auteur : Clement LE GOASTER
    char* nom_annuaire = malloc(100 * sizeof(char)); // Allocation de mémoire pour les variables d'entrées des fonctions
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
    char* nv_valeur = malloc(100 * sizeof(char));

    if (nom_annuaire == NULL || nom_p ==  NULL || prenom_p == NULL || code_postal_p == NULL || ville_p == NULL || telephone_p == NULL || mel_p == NULL || nv_mel_p == NULL || profession_p == NULL || nom_champ == NULL || val_chaine == NULL) {
        printf("Erreur lors de l'allocation de la mémoire\n");
        return -1; // Erreur car la mémoire n'a pas pu être allouée
    }

    int choix;
    int quit = 0;
    system("COLOR 0A");

    while (quit == 0) {
        printf("\n");
        printf("---------------Que voulez-vous faire ?--------------\n");
        printf("0. Afficher l'annuaire\n");
        printf("1. Ajouter un nouveau client\n");
        printf("2. Modifier le mel d'un client\n");
        printf("3. Modifier d'autres elements que le mel d'un client\n");
        printf("4. Supprimer un client\n");
        printf("5. Trier les clients par leur nom\n");
        printf("6. Filtrer les clients avec des données manquantes\n");
        printf("7. Filtrer un champ\n");
        printf("8. Filtrer en combinant deux champs\n");
        printf("9. Quitter le programme\n");
        printf("----------------------------------------------------\n");
        printf("-> ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 0:
            printf("Entrez le chemin vers l'annuaire a afficher (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            afficher_annuaire_clients(nom_annuaire);
            break;
        case 1:
            printf("Entrez le chemin vers l'annuaire ou ajouter le client (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            printf("Entrez le nom du client : \n");
            scanf("%s", nom_p);
            printf("Entrez le prenom du client : \n");
            scanf("%s", prenom_p);
            printf("Entrez le code postal du client : \n");
            scanf("%s", code_postal_p);
            printf("Entrez la ville ou reside le client : \n");
            scanf("%s", ville_p);
            printf("Entrez le numéro de telephone du client : \n");
            scanf("%s", telephone_p);
            printf("Entrez le mail du client : \n");
            scanf("%s", mel_p);
            printf("Entrez la profession du client : \n");
            scanf("%s", profession_p);
            ajouter_client(nom_annuaire, nom_p, prenom_p, code_postal_p, ville_p, telephone_p, mel_p, profession_p);
            break;
        case 2:
            printf("Entrez le chemin vers l'annuaire a lire (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            printf("Entrez le mail a remplacer : \n");
            scanf("%s", mel_p);
            printf("Entrez le nouvel email : \n");
            scanf("%s", nv_mel_p);
            modifier_mel_client(nom_annuaire, mel_p, nv_mel_p);
            break;
        case 3:
            int val_champ;
            printf("Entrez le chemin vers l'annuaire a lire (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            printf("Entrez le mel du client dont vous souhaitez modifier la valeur d'un champ : \n");
            scanf("%s", mel_p);
            printf("Voici les différents champs que vous pouvez modifier : \n");
            printf("\n");
            printf("1. Modifier le nom du client\n");
            printf("2. Modifier le prenom du client\n");
            printf("3. Modifier le code postal du client\n");
            printf("4. Modifier la ville ou réside le client\n");
            printf("5. Modifier le numero du telephone du client\n");
            printf("6. Modifier la profession du client\n");
            printf("\n");
            printf("Entrez le numero du champ a modifier : \n");
            scanf("%d", &val_champ);
            switch (val_champ)
            {
            case 1:
                nom_champ = "nom";
                break;
            case 2:
                nom_champ = "prenom";
                break;
            case 3:
                nom_champ = "code_postal";
                break;
            case 4:
                nom_champ = "ville";
                break;
            case 5:
                nom_champ = "telephone";
                break;
            case 6:
                nom_champ = "profession";
                break;
            default:
                printf("Erreur lors de la saisie\n");
                return -1; // Erreur lors de la saisie
                break;
            }
            printf("Entrez la nouvelle valeur de ce champ : \n");
            scanf("%s", nv_valeur);
            modifier_autres_que_mel_client(nom_annuaire, mel_p, nom_champ, nv_valeur);
            break;
        case 4:
            printf("Entrez le chemin vers l'annuaire a lire (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            printf("Entrez le mail du client a supprimer : \n");
            scanf("%s", mel_p);
            supprimer_client(nom_annuaire, mel_p);
            break;
        case 5:
            printf("Entrez le chemin vers l'annuaire a trier (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            trier_clients_par_nom(nom_annuaire);
            break;
        case 6:
            printf("Entrez le chemin vers l'annuaire a filtrer (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            filtrer_clients_donnees_manquantes(nom_annuaire);
            break;
        case 7:
            printf("Entrez le chemin vers l'annuaire a trier (avec l'extension) : \n");
            scanf("%s", nom_annuaire);
            printf("Entrez le nom du champs a trier : \n");
            scanf("%s", nom_champ);
            printf("Entrez la valeur a rechercher : \n");
            scanf("%s", val_chaine);
            filtrer_un_champ(nom_annuaire, nom_champ, val_chaine);
        case 8:
            printf("Fonctionnalité non disponible\n");
            break;
        case 9:
            printf("Vous quittez le programme...\n");
            printf("\n");
            quit = 1;
            break;
        default :
            printf("Erreur lors de la saisie\n");
            return -1; // Erreur lors de la saisie 
        }
    }

    // Libère l'espace mémoire alloué pour les chaines de charactères
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
    free(nv_valeur);
    return 0; // Retour normal
}
