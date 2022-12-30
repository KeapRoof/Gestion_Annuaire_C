#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"

void ajouter_client(const char* nom_annuaire, const char* nom_p, const char* prenom_p, const char* code_postal_p, const char* ville_p, const char* telephone_p, const char* mel_p, const char* profession_p) 
{
  // Auteur : Haithem HADJ AZZEM
  // Ouvre le fichier en mode "a" (ajout)
  FILE* file = fopen(nom_annuaire, "a");
  if (file == NULL) {
    printf("Impossible d'ouvrir le fichier\n");
    return;
  }
  // ecrit les informations du client dans le fichier
  fprintf(file, "\n%s,%s,%s,%s,%s,%s,%s,", nom_p, prenom_p, code_postal_p, ville_p, telephone_p, mel_p, profession_p);
  printf("Le client a bien été ajouté à l'annuaire");
  // Ferme le fichier
  fclose(file);
}

void supprimer_client(const char* nom_annuaire, const char* mel_p) 
{
  // Auteur : Haithem HADJ AZZEM
  // Ouvre le fichier en mode "r" (lecture)
  FILE* file = fopen(nom_annuaire, "r");
  if (file == NULL) {
      printf("Impossible d'ouvrir le fichier\n");
      return;
  }
  // Ouvre un fichier temporaire en mode "w" (écriture)
  FILE* temp = fopen("temp.csv", "w");
  if (temp == NULL) {
      printf("Impossible d'ouvrir le fichier temporaire\n");
      return;
  }
  // Lit le fichier ligne par ligne
  char line[1024];
  while (fgets(line, 1024, file)) {
      // Si la ligne ne contient pas l'adresse mail, on l'écrit dans le fichier temporaire
      if (!strstr(line, mel_p)) {
      fputs(line, temp);
      }
  }
  // Ferme les fichiers
  fclose(file);
  fclose(temp);
  // Supprime l'ancien fichier
  remove(nom_annuaire);
  // Renomme le fichier temporaire
  rename("temp.csv", nom_annuaire);
  printf("Client supprimé\n");
}

void modifier_mel_client(const char* nom_annuaire, char* mel_p, const char* nv_mel_p)
{
  // Auteur : Clement LE GOASTER
  // Ouvre le fichier en mode "a" (ajout)
  int find_mel = 0;
  FILE* file = fopen(nom_annuaire, "r+");
  if (file == NULL) {
    printf("Impossible d'ouvrir le fichier\n");
    return;
  }
  // Lit le fichier ligne par ligne
  char line[1024];
  while (fgets(line, 1024, file)) {
    // Remplace l'ancien par le nouveau mail si il est trouvé dans le fichier
    if(strstr(line, mel_p)) {
      fprintf(file, "%s", nv_mel_p);
      int nb_mel_rp = 1;
      printf("%d Mail remplacé\n", nb_mel_rp);
      nb_mel_rp++;
    }
  }
  fclose(file);
}