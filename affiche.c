#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // On ouvre le fichier csv en lecture
    FILE* fp = fopen("annuaire.csv", "r");
    if (fp == NULL) {
        // On affiche un message au cas où le fichier ne s'ouvre pas
        printf("Fichier inexistant");
    }

    // Nous allons afficher le contenu du fichier
    char line[1024]; //la variable "line" peut prendre jusqu'à 1024 données, ce qui est suffisant
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Tokenize the line
        char* token = strtok(line, ",");
        while (token != NULL) {
            // Print the token
            printf("%s ", token);
            // Get the next token
            token = strtok(NULL, ",");
        }
        // Print a newline after each line
        printf("\n");
    }

    // Close the file
    fclose(fp);

    return 0;
}
