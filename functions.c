/**
 * @file functions.c
 * @author Clément, Haithem, Aziz
 * @brief Fichier contenant le code des fonctions de l'API
 */

#include "functions.h"

void ajouter_client(const char* nom_annuaire, const char* nom_p, const char* prenom_p, const char* code_postal_p, const char* ville_p, const char* telephone_p, const char* mel_p, const char* profession_p) {
  // Auteur : Haithem HADJ AZZEM
  // Ouvre le fichier annaire
  FILE* file = fopen(nom_annuaire, "r");
  if (file == NULL) {
    perror("Impossible d'ouvrir le fichier");
    return;
  }

  // Ouvre le fichier résultat
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

  // Ecrit les informations du client dans le fichier
  fprintf(file2, "\n%s,%s,%s,%s,%s,%s,%s,", nom_p, prenom_p, code_postal_p, ville_p, telephone_p, mel_p, profession_p);
  printf("Le client a bien été ajouté à l'annuaire");

  // Fermeture des fichiers
  fclose(file);
  fclose(file2);
}

void supprimer_client(const char* nom_annuaire, const char* mel_p){
  // Auteur : Haithem HADJ AZZEM
  // Ouvre du fichier annuaire
  FILE* file = fopen(nom_annuaire, "r");
  if (file == NULL) {
      perror("Impossible d'ouvrir le fichier\n");
      return;
  }

  // Ouvre un fichier resultat
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

  // Fermeture des fichiers
  fclose(file);
  fclose(res);
  printf("Client supprimé\n");
  }

int modifier_mel_client(const char* nom_annuaire, const char* mel_p, const char* nv_mel_p)
{
  // Auteur : Clement LE GOASTER
  int cpt = 0; // Compteur pour savoir si l'adresse à remplacer est dans l'annuaire

  // Verifie la validité de l'annuaire
  int retour = verifier_validite_annuaire_client(nom_annuaire);
  if (retour == -1 || retour == -3 || retour == -4) {
    return -1; // L'annuaire n'est pas valide
  }

  // Ouvre le fichier en mode "r" (lecture)
  FILE* file = chargement_annuaire_clients(nom_annuaire);

  // Ouvre le fichier en mode "w" (ecriture)
  FILE* sortie = ecriture_annuaire_clients("resultat_modifier_mel.txt", "w");
  if ((file == NULL || sortie == NULL) || (file == NULL && sortie == NULL)) {
    return -2; // Erreur lors de la lecture / ecriture de l'annuaire
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

  // Fermeture des fichiers
  fclose(sortie);
  fclose(file);
  return 0;
}

int modifier_autres_que_mel_client(const char* nom_annuaire, const char* mel_p, const char* nom_champ, const char* nv_valeur)
{
  // Auteur : Clement LE GOASTER
  // Ouvre le fichier en mode "r" (lecture)
  FILE* file = chargement_annuaire_clients(nom_annuaire);

  // Ouvre le fichier en mode "w" (ecriture)
  FILE* sortie = ecriture_annuaire_clients("resultat_modifier_autres_que_mel.txt", "w");
  if ((file == NULL || sortie == NULL) || (file == NULL && sortie == NULL)) {
    return -1; // Erreur lors de la lecture / ecriture de l'annuaire
  }

  // Verification de la validité de l'adresse mail
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

  // Création de la structure client
  struct Client {
      char nom[50];
      char prenom[50];
      char adresse[50];
      char ville[50];
      char code_postal[50];
      char telephone[50];
      char email[50];
      char profession[50];
  };
  struct Client client;

  // Lit le fichier ligne par ligne
  char line[1024];
  while (fgets(line, 1024, file) != NULL) {
    if(strstr(line, mel_p)) { // Si le mel est trouvé sur la ligne
      char *token = strtok(line, ",");
      strcpy(client.nom, token); 
      token = strtok(NULL, ",");
      strcpy(client.prenom, token);
      token = strtok(NULL, ",");
      strcpy(client.code_postal, token);
      token = strtok(NULL, ",");
      strcpy(client.ville, token);
      token = strtok(NULL, ",");
      strcpy(client.telephone, token);
      token = strtok(NULL, ",");
      strcpy(client.email, token);
      token = strtok(NULL, ",");
      strcpy(client.profession, token);

      // Remplacement des valeurs dans le fichier
      if (strcmp(nom_champ, "nom") == 0) { // Si la valeur du champ est "nom"
        strcpy(client.nom, nv_valeur); // Remplacement de la valeur
        printf("La valeur est remplacée\n");
      }
      if (strcmp(nom_champ, "prenom") == 0) {
        strcpy(client.prenom, nv_valeur);
        printf("La valeur est remplacée\n");
      }
      if (strcmp(nom_champ, "code_postal") == 0) {
        strcpy(client.code_postal, nv_valeur);
        printf("La valeur est remplacée\n");
      }
      if (strcmp(nom_champ, "ville") == 0) {
        strcpy(client.ville, nv_valeur);
        printf("La valeur est remplacée\n");
      }
      if (strcmp(nom_champ, "telephone") == 0) {
        strcpy(client.telephone, nv_valeur);
        printf("La valeur est remplacée\n");
      }
      if (strcmp(nom_champ, "profession") == 0) {
        strcpy(client.profession, nv_valeur);
        printf("La valeur est remplacée\n");
      }

      fputs(line, sortie); // Ecriture dans le fichier de sortie
    } else {
      fputs(line, sortie);
    }
  }  

  // Fermeture des fichiers
  fclose(file);
  fclose(sortie);
  return 0;
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


int filtrer_clients_donnees_manquantes(const char *nom_annuaire) {
  // Auteur : Aziz MELLITI
  FILE* file = fopen(nom_annuaire, "r");
  if (file == NULL) {
    perror("Impossible d'ouvrir le fichier");
    return -1;
  }

  // Ouvre le fichier résultat
  FILE* file2 = fopen("resultat_afficher_donnees_manquantes.txt", "w");
  if (file2 == NULL) {
    perror("Impossible d'ouvrir le fichier");
  }

  int i = 1;
  char line[1024]; //la variable "line" peut prendre jusqu'a 1024 donnees, ce qui est suffisant
  while (fgets(line, sizeof(line), file) != NULL) {
    char *car = strstr(line, ",,");
    if (car != NULL || line[0] == ',' || line[strlen(line)-2] == ',')
      fprintf(file2, "client %d : %s", i, line);
      i++;
  }

  // Fermeture des fichiers
  printf("Le fichier est filtré\n");
  fclose(file);
  fclose(file2);
  return 0;
}

void filtrer_un_champ(char *nom_annuaire, char *nom_champ, char *val_chaine){
    // Auteur : Haithem
    // Création de la structure client
    struct Client {
        char nom[50];
        char prenom[50];
        char adresse[50];
        char ville[50];
        char code_postal[50];
        char telephone[50];
        char email[50];
    };

    //Ouverture de l'annuaire + Traitement des cas d'erreur
    FILE *fichier;
    fichier = fopen(nom_annuaire, "r");
    if (fichier == NULL){
        perror("Impossible d'ouvrir l'annuaire");
    }

    //Ouverture du ficher résultat du filtre
    FILE *fichier_filtrer;
    fichier_filtrer = fopen("filtrer.txt", "w");
    if (fichier_filtrer == NULL){
        perror("Impossible d'ouvrir le fichier filtrer.txt");
    }

    //Innitialisation de la variable client
    struct Client client;
    
    // Remplissage de la structure
    char ligne[500];
    while (fgets(ligne, 500, fichier) != NULL){
        char *token = strtok(ligne, ",");
        // Traitement des cas ou le champs est vide
        if (token == NULL){
            strcpy(client.nom, " ");
        }
        else{
        strcpy(client.nom, token);
        }
        token = strtok(NULL, ",");
        if (token == NULL){
            strcpy(client.prenom, " ");
        }
        else{
        strcpy(client.prenom, token);
        }
        token = strtok(NULL, ",");
        if (token == NULL){
            strcpy(client.adresse, " ");
        }
        else{
        strcpy(client.adresse, token);
        }
        token = strtok(NULL, ",");
        if (token == NULL){
            strcpy(client.ville, " ");
        }
        else{
        strcpy(client.ville, token);
        }
        token = strtok(NULL, ",");
        if (token == NULL){
            strcpy(client.code_postal, " ");
        }
        else{
        strcpy(client.code_postal, token);
        }
        token = strtok(NULL, ",");
        if (token == NULL){
            strcpy(client.telephone, " ");
        }
        else{
        strcpy(client.telephone, token);
        }
        token = strtok(NULL, ",");
        if (token == NULL){
            strcpy(client.email, " ");
        }
        else{
        strcpy(client.email, token);
        }
        // Comparaison avec la valeur donnée
        if (nom_champ == "nom"){
            if (strcmp(client.nom, val_chaine) == 0){
                fprintf(fichier_filtrer, "%s,%s,%s,%s,%s,%s,%s\n", client.nom, client.prenom, client.adresse, client.ville, client.code_postal, client.telephone, client.email);
        }
        }
        if (nom_champ == "prenom"){
            if (strcmp(client.prenom, val_chaine) == 0){
                fprintf(fichier_filtrer, "%s,%s,%s,%s,%s,%s,%s\n", client.nom, client.prenom, client.adresse, client.ville, client.code_postal, client.telephone, client.email);
        }
        }
        if (nom_champ == "adresse"){
            if (strcmp(client.adresse, val_chaine) == 0){
                fprintf(fichier_filtrer, "%s,%s,%s,%s,%s,%s,%s\n", client.nom, client.prenom, client.adresse, client.ville, client.code_postal, client.telephone, client.email);
        }
        }
        if (nom_champ == "ville"){
            if (strcmp(client.ville, val_chaine) == 0){
                fprintf(fichier_filtrer, "%s,%s,%s,%s,%s,%s,%s\n", client.nom, client.prenom, client.adresse, client.ville, client.code_postal, client.telephone, client.email);
        }
        }
        if (nom_champ == "code_postal"){
            if (strcmp(client.code_postal, val_chaine) == 0){
                fprintf(fichier_filtrer, "%s,%s,%s,%s,%s,%s,%s\n", client.nom, client.prenom, client.adresse, client.ville, client.code_postal, client.telephone, client.email);
        }
        }
        if (nom_champ == "telephone"){
            if (strcmp(client.telephone, val_chaine) == 0){
                fprintf(fichier_filtrer, "%s,%s,%s,%s,%s,%s,%s\n", client.nom, client.prenom, client.adresse, client.ville, client.code_postal, client.telephone, client.email);
        }
        }
        if (nom_champ == "email"){
            if (strcmp(client.email, val_chaine) == 0){
                fprintf(fichier_filtrer, "%s,%s,%s,%s,%s,%s,%s\n", client.nom, client.prenom, client.adresse, client.ville, client.code_postal, client.telephone, client.email);
        }
        }
    }

    // Fermeture des fichiers
    fclose(fichier);
    fclose(fichier_filtrer);
    printf("Fichier filtrer.txt créé");
}

// void filtrer_combiner_deux_champs(char *nom_annuaire, char *nom_champ1, char *nom_champ2, char *val_chaine1, char *val_chaine2)
// {
//   // Cette fonction ne marche pas, c'est un prototype !
  
//   // Ouverture de l'annuaire + Traitement des cas d'erreur
//   FILE *fichier;
//   fichier = fopen(nom_annuaire, "r");
//   if (fichier == NULL){
//       perror("Impossible d'ouvrir l'annuaire\n");
//   }

//   // Ouverture du ficher résultat du filtre
//   FILE *fichier_filtrer;
//   fichier_filtrer = fopen("filtrer.txt", "w");
//   if (fichier_filtrer == NULL){
//       perror("Impossible d'ouvrir le fichier filtrer.txt\n");
//   }

//   // Innitialisation de la variable client
//   // Trouver l'indice des champs à filtrer
//   int index_champ1 = -1, index_champ2 = -1;
//   char line[1024];
//   char *token; // Lire la ligne d'en-tête
//   int i = 0;

//   while ((token = strtok(line, ',')) != NULL) {
//     if (strcmp(token, nom_champ1) == 0) {
//       index_champ1 = i;
//     }
//     if (strcmp(token, nom_champ2) == 0) {
//       index_champ2 = i;
//     }
//     i++;
//   }

//   // Vérifier que les champs ont été trouvés
//   if (index_champ1 == -1 || index_champ2 == -1) {
//   printf("Un ou plusieurs champs introuvables dans l'en-tête de l'annuaire.\n");
//   return 1;
//   }

//   // Lire et filtrer les lignes du fichier
//   while (fgets(line, sizeof(line), nom_annuaire) != NULL) {
//     // Réinitialiser les variables utilisées par strtok
//       i = 0;
//       token = NULL;

//     // Extraire les champs de la ligne
//     char *champs[7];
//     while ((token = strtok(line, ',')) != NULL) {
//       champs[i] = token;
//       i++;
//     }
//     // Vérifier si les champs contiennent les chaînes de caractères attendues
//     if (strcmp(champs[index_champ1], val_chaine1) == 0 && strcmp(champs[index_champ2], val_chaine2) == 0) {
//     // Écrire la ligne dans le fichier de sortie
//         fprintf(fichier_filtrer, "%s,%s,%s,%s,%s,%s,%s\n", champs[0], champs[1], champs[2], champs[3], champs[4], champs[5], champs[6]);
//     }
//   }

// // Fermer les fichiers
//     fclose(nom_annuaire);
//     fclose(fichier_filtrer);
// }

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
  ligne_modifiee = (char*) malloc (i + j * (longueur_nouvel_element - longueur_ancien_element) + 1); 
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

FILE* chargement_annuaire_clients(const char* nom_annuaire)
{
  // Auteur : Aziz MELLITI
  FILE* file = fopen(nom_annuaire, "r");
  if (file == NULL) {
    printf("Impossible d'ouvrir l'annuaire\n");
    return NULL; // Erreur car il est impossible d'ouvrir l'annuaire
  }
  return file;
}

FILE* ecriture_annuaire_clients(const char* nom_fichier, const char* mode_ecriture)
{
  // Auteur : Aziz MELLITI
  FILE* sortie = fopen(nom_fichier, mode_ecriture);
  if (sortie == NULL) {
    printf("Impossible de créer/ouvrir le fichier de sortie (.txt)\n");
    return NULL; // Erreur car il est impossible de créer/ouvrir le fichier de sortie
  }

  return sortie;
}

int afficher_annuaire_clients(const char* nom_annuaire)
{
  // Auteur : Aziz MELLITI
  int retour = verifier_validite_annuaire_client(nom_annuaire);
  if (retour == -1 || retour == -3 || retour == -4) {
    return -1; // L'annuaire n'est pas valide
  }

  printf("\n");
  FILE* file = chargement_annuaire_clients(nom_annuaire);
  // Nous allons afficher le contenu du fichier
  char line[1024]; //la variable "line" peut prendre jusqu'� 1024 donn�es, ce qui est suffisant
  while (fgets(line, sizeof(line), file) != NULL) {
    // Tokenize la ligne
    char* token = strtok(line, ",");
    while (token != NULL) {
      // Affiche la valeur du token
      printf("%s ", token);
      // Va au token suivant
      token = strtok(NULL, ",");
      }
    printf("\n");
    }

  // Fermeture des fichiers
  fclose(file);

  return 0;
}

int verifier_validite_annuaire_client(const char* nom_annuaire)
{
  // Auteur : Clement LE GOASTER & Aziz MELLITI
  int i = 0;
  if (!strstr(nom_annuaire, ".csv")) { // Cherche si l'extention .csv est bien présente dans le nom de l'annuaire
    printf("L'annuaire n'est pas au format .csv : invalide\n");
    return -1;
  } 

  FILE* file = chargement_annuaire_clients(nom_annuaire);
  if (file == NULL) {
    return -2; // Erreur lors de la lecture / ecriture de l'annuaire
  }

  char line[1024];
  fgets(line, 1024, file);
  if (feof(file)) { // Cherche si la fin du fichier est directement sur la première ligne
    printf("L'annuaire n'est pas valide : il est vide\n");
    return -3;
  }

  while (fgets(line, 1024, file)) {
    if (!strstr(line, ",")) { // Cherche les commentaires séparateurs sur toutes les lignes du fichier
      i = 1;
    }
  }

  if (i == 1) {
    printf("L'annuaire csv n'est pas valide : il manque des caractères séparateurs sur une/des lignes de l'annuaire\n");
    return -4;
  }

  return 0;
}
