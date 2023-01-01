/**
 * @file functions.c
 * @author Haithem, Aziz, Clement
 * @brief fichiers contenant les fonctions
 * @version 0.1
 */

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
  printf("Le client a bien été ajouté à l'annuaire\n");
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

int modifier_mel_client(const char* nom_annuaire, const char* mel_p, const char* nv_mel_p)
{
  // Auteur : Clement LE GOASTER
  int cpt = 0; // Compteur pour savoir si l'adresse à remplacer est dans l'annuaire
  // Ouvre le fichier en mode "r" (lecture)
  FILE* file = fopen(nom_annuaire, "r");
  if (file == NULL) {
    printf("Impossible d'ouvrir l'annuaire\n");
    return -1; // Erreur car il est impossible d'ouvrir l'annuaire
  }
  // Ouvre le fichier en mode "w" (ecriture)
  FILE* sortie = fopen("resultat_modifier_mel.txt", "w");
  if (sortie == NULL) {
    printf("Impossible de créer/ouvrir le fichier de sortie (.txt)\n");
    return -2; // Erreur car il est impossible de créer/ouvrir le fichier de sortie
  }
  // Verifie si les chaines ne sont pas des chaines vides
  if ((strlen(mel_p) == 0 && strlen(nv_mel_p) == 0) || (strlen(mel_p) == 0 || strlen(nv_mel_p) == 0))
  {
    printf("Le ou les chaines sont vides\n");
    remove("resultat_modifier_mel.txt");
    fclose(file);
    return -3; // Erreur car les chaines sont vides
  }
  // Lit le fichier ligne par ligne
  char line[1024];
  while (fgets(line, 1024, file)) {
    // Remplace l'ancien par le nouveau mail si il est trouvé dans le fichier
    if (strstr(line, nv_mel_p)) {
    printf("La nouvelle adresse est déjà dans l'annuaire\n");
    remove("resultat_modifier_mel.txt");
    fclose(file);
    return -4; // Erreur car la nouvelle adresse est déja présente dans le fichier
    }
    if (strstr(line, mel_p)) {
      remplacer_element(line, mel_p, nv_mel_p);
      fputs((remplacer_element(line, mel_p, nv_mel_p)), sortie);
      printf("Mail remplacé\n");
      cpt++;
    } else {
      fputs(line, sortie);
    }
  }
  if (cpt == 0) {
  printf("L'adresse à remplacer n'est pas dans l'annuaire\n");
  remove("resultat_modifier_mel.txt");
  fclose(file);
  return -5; // Erreur car l'adresse à remplacer n'est pas dans l'annuaire
  }
  fclose(sortie);
  fclose(file);
  return 0;
}

char* remplacer_element(const char* nom_chaine, const char* ancien_element, const char* nouvel_element)
{ 
  // Auteur : Clement LE GOASTER
  char* ligne_modifiee; 
  int i, j = 0; 
  // Definition des tailles de chaines de charatères pour ne pas déborder sur les autres charactères
  int longueur_ancien_element = strlen(ancien_element); 
  int longueur_nouvel_element = strlen(nouvel_element); 
  // Comptage du nombre d'occurence de l'ancien element
  for (i = 0; nom_chaine[i] != '\0'; i++) { 
    if (strstr(&nom_chaine[i], ancien_element) == &nom_chaine[i]) { 
      j++;  
      i += longueur_ancien_element - 1; 
    } 
  } 
  // Création d'une chaine de caractères de longueur suffisante 
  ligne_modifiee = (char*)malloc(i + j * (longueur_nouvel_element - longueur_ancien_element) + 1); 
  i = 0; 
  while (*nom_chaine) { 
  // Modifie les deux elements et renvoie une chaine avec les element echangés
    if (strstr(nom_chaine, ancien_element) == nom_chaine) { 
      strcpy(&ligne_modifiee[i], nouvel_element); 
        i += longueur_nouvel_element; 
        nom_chaine += longueur_ancien_element; 
      } else {
        ligne_modifiee[i++] = *nom_chaine++;
      } 
  } 
  ligne_modifiee[i] = '\0'; 
  // Retourne la ligne modifiée pour qu'elle puisse ensuite être écrite
  return ligne_modifiee;
  // Libère l'espace mémoire alloué précedemment avec malloc
  free(ligne_modifiee); 
} 

int trier_clients_par_nom(const char* nom_annuaire) 
{
  // Auteur : Clement LE GOASTER
  // Ouvre le fichier en mode "r" (lecture)
  FILE* file = fopen(nom_annuaire, "r");
  if (file == NULL) {
    printf("Impossible d'ouvrir l'annuaire\n");
    return -1; // Erreur car il est impossible d'ouvrir l'annuaire
  }
  // Ouvre le fichier en mode "w" (ecriture)
  FILE* sortie = fopen("resultat_trier_par_nom.txt", "w");
  if (sortie == NULL) {
    printf("Impossible de créer/ouvrir le fichier de sortie (.txt)\n");
    return -2; // Erreur car il est impossible de créer/ouvrir le fichier de sortie
  }
}