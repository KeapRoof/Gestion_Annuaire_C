#include <stdio.h>
#include <stdlib.h>

void ajout_de_cli(const char* nom_annuaire, const char* nom_p, const char* prenom_p, const char* code_postal_p, const char* ville_p, const char* telephone_p, const char* mel_p, const char* profession_p) {
  // Ouvre le fichier en mode "r" (lecture)
  FILE* file = fopen(nom_annuaire, "r");
  if (file == NULL) {
    perror("Impossible d'ouvrir le fichier");
    return;
  }

  // Ouvre le fichier en mode "w" (ecriture)
  FILE* file2 = fopen("Resultat.txt", "w");
  if (file2 == NULL) {
    perror("Impossible d'ouvrir le fichier");
    return;
  }

  // Copie le contenu du fichier annuaire dans le fichier resultat
  char c;
  while ((c = fgetc(file)) != EOF) {
    fputc(c, file2);
  }

  // ecrit les informations du client dans le fichier
  fprintf(file2, "\n%s,%s,%s,%s,%s,%s,%s,", nom_p, prenom_p, code_postal_p, ville_p, telephone_p, mel_p, profession_p);
  printf("Le client a bien été ajouté à l'annuaire");
  // Ferme le fichier
  fclose(file);
  fclose(file2);
}

int main(){
    ajout_de_cli("annuaire.csv", "Dupont", "Jean", "75000", "Paris", "0123456789","jean.dupont@gmail.com", "Ingenieur");
    return 0;
}