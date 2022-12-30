#pragma once

void ajouter_client(const char* nom_annuaire, const char* nom_p, const char* prenom_p, const char* code_postal_p, const char* ville_p, const char* telephone_p, const char* mel_p, const char* profession_p);

void supprimer_client(const char* nom_annuaire, const char* mel_p);

void modifier_mel_client(const char* nom_annuaire, const char* mel_p, const char* nv_mel_p);

char* remplacer_mot(const char* chaine_de_characteres, const char* remplacer, const char* remplacant);