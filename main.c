/**
 * @file main.c
 * @author Haithem, Aziz, Clement
 * @brief main (executions des fonctions)
 * @version 0.1
 */

#include <stdio.h>
#include <assert.h>

#include "functions.h"

//commentaire doxygen (sur 0.375/20) sur l'API
//assert obligatoire
//fichier .h & .c séparés

int main(void) {
    int choix;
    printf("--------------------------------------------------\n");
    printf("1. Ajouter un nouveau client\n");
    printf("2. Modifier le mel d'un client\n");
    printf("3. Modifier autres elements que le mel d'un client\n");
    printf("4. Supprimer un client\n");
    printf("5. Trier les clients par leur nom\n");
    printf("6. Filtrer les clients avec des données manquantes\n");
    printf("7. Filtrer un champ\n");
    printf("8. Filtrer en combinant deux champs\n");
    printf("--------------------------------------------------\n");
    printf("-> ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        ajouter_client("annuaire.csv", "Dupont", "Jean", "75000", "Paris", "0123456789","jean.dupont@gmail.com", "Ingenieur");
        break;
    case 2:
        char* annuaire;
        char* mel_p;
        char* nv_mel_p;
        // rendre le tableau dinamique
        printf("Entrez le nom de l'annuaire à lire (avec l'extension) : \n");
        scanf("%s", annuaire);
        printf("Entrez le mail à remplacer : \n");
        scanf("%s", mel_p);
        printf("Entrez le nouvel email : \n");
        scanf("%s", nv_mel_p);
        printf("\n");
        modifier_mel_client(annuaire, mel_p, nv_mel_p);
        break;
    case 4:
        supprimer_client("annuaire.csv", "jean.dupont@gmail.com");
        break;
    case 5:
        trier_clients_par_nom("annuaire.csv");
        break;
    default:
        printf("Erreur lors de la saisie OU fonctionnalité non disponible pour le moment\n");
        return -1; // Erreur lors de la saisie 
    }
    return 0; // Retour normal
}
