#include "functions.h"

// Assert obligatoire

int main(void) {
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
    int choix;
    fflush(stdin);
    scanf("%d", &choix);
    char* nom_annuaire = malloc(100 * sizeof(char));
    char* nom_p = malloc(100 * sizeof(char));
    char* prenom_p = malloc(100 * sizeof(char));
    char* code_postal_p = malloc(100 * sizeof(char));
    char* ville_p = malloc(100 * sizeof(char));    
    char* telephone_p = malloc(100 * sizeof(char));    
    char* mel_p = malloc(100 * sizeof(char));
    char* nv_mel_p = malloc(100 * sizeof(char));
    char* profession_p = malloc(100 * sizeof(char));
    if (nom_annuaire == NULL || nom_p ==  NULL || prenom_p == NULL || code_postal_p == NULL || ville_p == NULL || telephone_p == NULL || mel_p == NULL || nv_mel_p == NULL || profession_p == NULL) {
        printf("Erreur lors de l'allocation de la mémoire\n");
        return -1; // Erreur car la mémoire n'a pas pu être allouée
    }
    switch (choix)
    {
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
        printf("Entrez numéro de téléphone du client : \n");
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
    default:
        printf("Erreur lors de la saisie OU fonctionnalité non disponible pour le moment\n");
        return -1; // Erreur lors de la saisie 
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
    return 0; // Retour normal
}
