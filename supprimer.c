#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void supprimer_client(const char* nom_annuaire, const char* mel_p) {
    // Ouvre le fichier en mode "r" (lecture)
    FILE* file = fopen(nom_annuaire, "r");
    if (file == NULL) {
        perror("Impossible d'ouvrir le fichier\n");
        return;
    }
    // Ouvre un fichier resultat en mode "w" (écriture)
    FILE* res = fopen("resultat_supprimer.txt", "w");
    if (res == NULL) {
        perror("Impossible d'ouvrir le fichier resultat\n");
        return;
    }
    // Lit le fichier ligne par ligne
    char line[1024];
    while (fgets(line, 1024, file)) {
        // Si la ligne ne contient pas l'adresse mail, on l'écrit dans le fichier resultat
        if (!strstr(line, mel_p)) {
        fputs(line, res);
        }
    }
    // Ferme les fichiers
    fclose(file);
    fclose(res);
    printf("Client supprimé\n");
    }

int main() {
    supprimer_client("annuaire.csv", "david.perrin@server.fr");
    return 0;
}