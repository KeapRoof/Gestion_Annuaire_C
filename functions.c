/**
 * @file functions.c
 * @author Clément, Haithem, Aziz
 * @brief Fichier contenant le code des fonctions de l'API
 */

#include "functions.h"

int ajouter_client(const char* nom_annuaire, const char* nom_p, const char* prenom_p, const char* code_postal_p, const char* ville_p, const char* telephone_p, const char* mel_p, const char* profession_p) 
{
  // Auteur : Haithem HADJ AZZEM
  FILE* file = chargement_annuaire_clients(nom_annuaire);
  // Ouvre le fichier en mode "a" (ajout)
  FILE* sortie = ecriture_annuaire_clients("resultat_ajouter.txt", "a");
  if ((file == NULL || sortie == NULL) || (file == NULL && sortie == NULL)) {
    return -1; // Erreur lors de la lecture / ecriture de l'annuaire
  }
  // ecrit les informations du client dans le fichier
  afficher_annuaire_clients(file, sortie);
  fprintf(sortie, "\n%s,%s,%s,%s,%s,%s,%s,", nom_p, prenom_p, code_postal_p, ville_p, telephone_p, mel_p, profession_p);
  printf("Le client a bien été ajouté à l'annuaire\n");
  // Ferme le fichier
  fclose(file);
  fclose(sortie);
}

int supprimer_client(const char* nom_annuaire, const char* mel_p) 
{
  // Auteur : Haithem HADJ AZZEM
  // Ouvre le fichier en mode "r" (lecture)
  FILE* file = chargement_annuaire_clients(nom_annuaire);
  // Ouvre le fichier en mode "w" (ecriture)
  FILE* temp = ecriture_annuaire_clients("temp.csv", "w");
  if ((file == NULL || temp == NULL) || (file == NULL && temp == NULL)) {
    return -1; // Erreur lors de la lecture / ecriture de l'annuaire
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
  FILE* file = chargement_annuaire_clients(nom_annuaire);
  // Ouvre le fichier en mode "w" (ecriture)
  FILE* sortie = ecriture_annuaire_clients("resultat_trier_par_nom.txt", "w");
  if ((file == NULL || sortie == NULL) || (file == NULL && sortie == NULL)) {
    return -1; // Erreur lors de la lecture / ecriture de l'annuaire
  }
  // Verifie si les chaines ne sont pas des chaines vides
  if ((strlen(mel_p) == 0 && strlen(nv_mel_p) == 0) || (strlen(mel_p) == 0 || strlen(nv_mel_p) == 0))
  {
    printf("Le ou les chaines sont vides\n");
    remove("resultat_modifier_mel.txt");
    fclose(file);
    return -3; // Erreur car les chaines sont vides
  }
  // Verifie si l'adresse mail est valide (@ & . présents)
  if (strchr(mel_p, '@') == NULL) {
    printf("L'adresse mel à remplacer est invalide : pas de (@)\n");
    remove("resultat_modifier_mel.txt");
    fclose(file);
    return -4; // Erreur car l'adresse mail est invalide
  }
  if (strchr(mel_p, '.') == NULL) { // Ne fonctionne pas si il y a un point dans la première partie de l'adresse
    printf("L'adresse mel à remplacer est invalide : pas de (.)\n");
    remove("resultat_modifier_mel.txt");
    fclose(file);
    return -5; // Erreur car l'adresse mail est invalide
  }
  // Verifie si l'adresse mail est valide (@ & . présents)
  if (strchr(nv_mel_p, '@') == NULL) {
    printf("La nouvelle adresse mel est invalide : pas de (@)\n");
    remove("resultat_modifier_mel.txt");
    fclose(file);
    return -6; // Erreur car la nouvelle adresse mail est invalide
  }
  if (strchr(nv_mel_p, '.') == NULL) { // Ne fonctionne pas si il y a un point dans la première partie de l'adresse
    printf("La nouvelle adresse mel est invalide : pas de (.)\n");
    remove("resultat_modifier_mel.txt");
    fclose(file);
    return -7; // Erreur car la nouvelle adresse mail est invalide
  }
  // Lit le fichier ligne par ligne
  char line[1024];
  while (fgets(line, 1024, file)) {
    // Remplace l'ancien par le nouveau mail si il est trouvé dans le fichier
    if (strstr(line, nv_mel_p)) {
    printf("La nouvelle adresse est déjà dans l'annuaire\n");
    remove("resultat_modifier_mel.txt");
    fclose(file);
    return -8; // Erreur car la nouvelle adresse est déja présente dans le fichier
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
  return -9; // Erreur car l'adresse à remplacer n'est pas dans l'annuaire
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
  FILE* file = chargement_annuaire_clients(nom_annuaire);
  // Ouvre le fichier en mode "w" (ecriture)
  FILE* sortie = ecriture_annuaire_clients("resultat_trier_par_nom.txt", "w");
  if ((file == NULL || sortie == NULL) || (file == NULL && sortie == NULL)) {
    return -1; // Erreur lors de la lecture / ecriture de l'annuaire
  }
  // Lit le fichier ligne par ligne
  char* lines[1000];
  char line[1024];
  char *temp;  // Chaîne de caractères temporaire pour échanger les lignes
  int i = 0;
  while (fgets(line, 1024, file)) {
    lines[i] = malloc(strlen(line) + 1);  // allouez de l'espace mémoire pour la ligne
    if (lines == NULL) {
      printf("Erreur lors de l'allocation de la mémoire\n");
      remove("resultat_modifier_mel.txt");
      fclose(file);
      return -3; // Erreur car la mémoire n'a pas pu être allouée
    }
    strcpy(lines[i], line);  // copiez la ligne dans le tableau
    i++;
  }
  // Tri à bulles du tableau de lignes
  for (int j = 0; j < i - 1; j++) {
    for (int k = 0; k < i - 1; k++) {
      if (strcmp(lines[k], lines[k + 1]) > 0) {  // Si la ligne actuelle est "supérieure" à la ligne suivante
        temp = lines[k];  // Echangez les lignes
        lines[k] = lines[k + 1];
        lines[k + 1] = temp;
      }
    }
  }
  for (int j = 0; j < i; j++) {
    fputs(lines[j], sortie);
  }
  for (int j = 0; j < i; j++) {
    free(lines[j]);
  }
  printf("Le fichier est trié\n");
  fclose(sortie);
  fclose(file);
  return 0; // Fonctionnement normal
}

FILE* chargement_annuaire_clients(const char* nom_annuaire)
{
  // Auteur : Clement LE GOASTER
  FILE* file = fopen(nom_annuaire, "r");
  if (file == NULL) {
    printf("Impossible d'ouvrir l'annuaire\n");
    return NULL; // Erreur car il est impossible d'ouvrir l'annuaire
  }
  return file;
}

FILE* ecriture_annuaire_clients(const char* nom_fichier, const char* mode_ecriture)
{
  // Auteur : Clement LE GOASTER
  FILE* sortie = fopen(nom_fichier, mode_ecriture);
  if (sortie == NULL) {
    printf("Impossible de créer/ouvrir le fichier de sortie (.txt)\n");
    return NULL; // Erreur car il est impossible de créer/ouvrir le fichier de sortie
  }
  return sortie;
}

void afficher_annuaire_clients(FILE* nom_pt, FILE* nom_pt_sortie)
{
  // Auteur : Clement LE GOASTER
  char line[1024];
  while (fgets(line, 1024, nom_pt)) {
    fputs(line, nom_pt_sortie);
  }
}

int verifier_validite_annuaire_client(const char* nom_annuaire)
{
  // Auteur : Clement LE GOASTER
}