#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * @brief Permet d'ajouter des clients dans le fichier .csv
 * 
 * @param nom_annuaire Nom de l'annuaire pour lire les données (format .csv)
 * @param nom_p Nom du client à ajouter
 * @param prenom_p Prénom du client à ajouter
 * @param code_postal_p Code postal du client à ajouter
 * @param ville_p Ville où le client réside
 * @param telephone_p Numéro de téléphone du client à ajouter
 * @param mel_p Email du client à ajouter
 * @param profession_p Profession du client à ajouter
 */
void ajouter_client(const char* nom_annuaire, const char* nom_p, const char* prenom_p, const char* code_postal_p, const char* ville_p, const char* telephone_p, const char* mel_p, const char* profession_p);

/**
 * @brief 
 * 
 * @param nom_annuaire Nom de l'annuaire pour lire les données (format .csv)
 * @param mel_p Email du client à supprimer
 */
void supprimer_client(const char* nom_annuaire, const char* mel_p);

/**
 * @brief 
 * 
 * @param nom_annuaire Nom de l'annuaire pour lire les données (format .csv)
 * @param mel_p Email à remplacer
 * @param nv_mel_p Nouvel email du client
 * @return int 
 */
int modifier_mel_client(const char* nom_annuaire, const char* mel_p, const char* nv_mel_p);

/**
 * @brief 
 * 
 * @param nom_chaine Nom de la chaine où se situe l'élément à remplacer
 * @param ancien_element Chaine de charactères contenant l'ancien élément
 * @param nouvel_element Nouvelle chaine de charactères contenant le nouvel élément
 * @return char* 
 */
char* remplacer_element(const char* nom_chaine, const char* ancien_element, const char* nouvel_element);

/**
 * @brief 
 * 
 * @param nom_annuaire Nom de l'annuaire à trier (format .csv)
 * @return int 
 */
int trier_clients_par_nom(const char* nom_annuaire);