#include "functions.h"

#include <stdio.h>
#include <assert.h>

//commentaire doxygen (sur 0.375/20) sur l'API
//assert obligatoire
//fichier .h & .c séparés

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
