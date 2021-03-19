#ifndef _PERSONNAGE_H
#define _PERSONNAGE_H

#define PV_POTION 25
#define FORCE 7
#define VIE_MAX 100
#define NB_POTIONS 5

#define DEGAT_ALEA_MIN 1
#define DEGAT_ALEA_MAX 6
#define POPO_CASSE_ALEA 5
#define POPO_BOIRE_MIN 1
#define POPO_BOIRE_MAX 7

#include <stdbool.h>

typedef struct Personnage_t Personnage;

Personnage *Personnage_new();

void Personnage_free(Personnage *this);

int Personnage_attaquer(Personnage *this);

void Personnage_recevoir_degat(Personnage *this, int degat);

bool Personnage_boire_potion(Personnage *this);

int Personnage_attaquer(Personnage *this);

void Personnage_voir_etat(Personnage *this);

int Personnage_est_vivant(Personnage *this);

void Personnage_voir_deux_etats(Personnage *j1, Personnage *j2);

bool Personnage_a_des_potions(Personnage *this);

bool Personnage_full_pv(Personnage *this);

int Personnage_gagnant(Personnage *j1, Personnage *j2);

#endif