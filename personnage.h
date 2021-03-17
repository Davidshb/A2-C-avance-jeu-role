#ifndef _PERSONNAGE_H
#define _PERSONNAGE_H

#define PV_POTION 25
#define FORCE 7
#define VIE_MAX 100
#define NB_POTIONS 5

typedef struct Personnage_t Personnage;

Personnage *Personnage_new();

void Personnage_free(Personnage *this);

int Personnage_attaquer(Personnage *this);

void Personnage_recevoir_degat(Personnage *this, int degat);

int Personnage_boire_potion(Personnage *this);

int Personnage_attaquer(Personnage *this);

void Personnage_voir_etat(Personnage *this);

int Personnage_est_vivant(Personnage *this);

#endif