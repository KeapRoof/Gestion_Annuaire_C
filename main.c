#include <stdio.h>
#include <assert.h>

#include "functions.h"

//commentaire doxygen (sur 0.375/20) sur l'API
//assert obligatoire
//fichier .h & .c séparés

int main(void) {
    ajouter_client("annuaire.csv", "Dupont", "Jean", "75000", "Paris", "0123456789","jean.dupont@gmail.com", "Ingenieur");
    modifier_mel_client("annuaire.csv", "antoine.boucher@server.fr", "antoine.viviviivvivi@server.fr");
}
