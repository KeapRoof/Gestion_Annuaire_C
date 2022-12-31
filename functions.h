/**
 * @file functions.h
 * @author Haithem, Aziz, Clement
 * @brief en-tête pour la précompilation
 * @version 0.1
 */

#pragma once

void ajouter_client(const char* nom_annuaire, const char* nom_p, const char* prenom_p, const char* code_postal_p, const char* ville_p, const char* telephone_p, const char* mel_p, const char* profession_p);

void supprimer_client(const char* nom_annuaire, const char* mel_p);

int modifier_mel_client(const char* nom_annuaire, const char* mel_p, const char* nv_mel_p);

char* remplacer_element(const char* nom_chaine, const char* ancien_element, const char* nouvel_element);