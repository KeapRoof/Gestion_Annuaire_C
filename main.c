#include <stdio.h>
#include <assert.h>

#include "functions.h"

//commentaire doxygen (sur 0.375/20) sur l'API
//assert obligatoire
//fichier .h & .c séparés

int main(void) {
    ajouter_client("annuaire.csv","b","c","d","e","f","g","h");
    supprimer_client("annuaire.csv","g");
}
