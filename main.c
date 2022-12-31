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
    ajouter_client("annuaire.csv", "Dupont", "Jean", "75000", "Paris", "0123456789","jean.dupont@gmail.com", "Ingenieur");
    supprimer_client("annuaire.csv", "jean.dupont@gmail.com");
    modifier_mel_client("annuaire.csv", "richard.rey-du-letellier@server.fr", "richard.rey-du-letellier@server.fr");
}
