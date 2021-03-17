#ifndef _PERSONNAGE_H
#define _PERSONNAGE_H

void personnage_new(int);
void personnage_free();

int personnage_est_vivant();

int personnage_attaquer();

int personnage_boire_potion();

void edit_etat();

void recevoir_degat(int);
#endif