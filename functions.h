/**
 * @file functions.h
 * @author Clément, Haithem, Aziz
 * @brief Fichier d'en-tête pour les fonctions contenues dans functions.c & dans le main
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * @brief Permet d'ajouter des clients dans l'annuaire
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
int ajouter_client(const char* nom_annuaire, const char* nom_p, const char* prenom_p, const char* code_postal_p, const char* ville_p, const char* telephone_p, const char* mel_p, const char* profession_p);

/**
 * @brief Permet de supprimer un client de l'annuaire
 * 
 * @param nom_annuaire Nom de l'annuaire pour lire les données (format .csv)
 * @param mel_p Email du client à supprimer
 */
int supprimer_client(const char* nom_annuaire, const char* mel_p);

/**
 * @brief Permet de modifier le mail d'un client déja présent dans l'annuaire
 * 
 * @param nom_annuaire Nom de l'annuaire pour lire les données (format .csv)
 * @param mel_p Email à remplacer
 * @param nv_mel_p Nouvel email du client
 * @return int 
 */
int modifier_mel_client(const char* nom_annuaire, const char* mel_p, const char* nv_mel_p);

/**
 * @brief Permet de remplacer un élément par un autre dans une chaine de charactères
 * 
 * @param nom_chaine Nom de la chaine où se situe l'élément à remplacer
 * @param ancien_element Chaine de charactères contenant l'ancien élément
 * @param nouvel_element Nouvelle chaine de charactères contenant le nouvel élément
 * @return char* 
 */
char* remplacer_element(const char* nom_chaine, const char* ancien_element, const char* nouvel_element);

/**
 * @brief Fonction qui trie l'annuaire par l'ordre alphabétiques des noms des clients
 * 
 * @param nom_annuaire Nom de l'annuaire à trier (format .csv)
 * @return int 
 */
int trier_clients_par_nom(const char* nom_annuaire);

/**
 * @brief Fonction qui permet de charger l'annuaire dans un pointeur "file"
 * 
 * @param nom_annuaire Nom de l'annuaire à charger dans le pointeur "file"
 */
FILE* chargement_annuaire_clients(const char* nom_annuaire);

/**
 * @brief Fonction qui créer un fichier de sortie pour l'annuaire
 * 
 * @param nom_fichier Nom du fichier à créer (avec le format)
 * @param mode_ecriture Mode d'écriture souhaité (a : append, w : write, ou r : read)
 * @return FILE* 
 */
FILE* ecriture_annuaire_clients(const char* nom_fichier, const char* mode_ecriture);

/**
 * @brief Fonction qui permet de printer l'annuaire dans un fichier de sortie
 * 
 * @param nom_pt Nom du pointeur vers le fichier annuaire
 * @param nom_pt_sortie Nom du pointeur vers le fichier de sortie
 */
void afficher_annuaire_clients(FILE* nom_pt, FILE* nom_pt_sortie);

/**
 * @brief Fonction qui verifie si l'annuaire client n'est pas vide
 * 
 * @param nom_annuaire Nom de l'annuaire à verifier
 */
int verifier_validite_annuaire_client(const char* nom_annuaire);