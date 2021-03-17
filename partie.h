#ifndef _PARTIE_H
#define _PARTIE_H

#include "personnage.h"

typedef enum
{
    JOUEUR_1_S,
    JOUEUR_2_S,
    FIN_S,
    NB_ETAT
} Etat;

typedef enum
{
    NOP_A=0,
    DEMARRE_A,
    ATTAQUE_J1_A,
    ATTAQUE_J2_A,
    BOIRE_POPO_J1_A,
    BOIRE_POPO_J2_A,
    FIN_A
} TransitionAction;

typedef enum
{
    ATTAQUER_E = 0,
    BOIRE_POPO_E,
    PV_0_E,
    DEMARRER_E,
    NB_ENTREE
} Entree;

typedef struct
{
    Etat destinationEtat;
    TransitionAction action;
} Transition;

static Transition mySm[NB_ETAT][NB_ENTREE] = {
    [JOUEUR_1_S][ATTAQUER_E] = {JOUEUR_2_S, ATTAQUE_J1_A},
    [JOUEUR_1_S][BOIRE_POPO_E] = {JOUEUR_2_S, BOIRE_POPO_J1_A},
    [JOUEUR_1_S][PV_0_E] = {FIN_S, FIN_A},
    [JOUEUR_2_S][ATTAQUER_E] = {JOUEUR_1_S, ATTAQUE_J2_A},
    [JOUEUR_2_S][BOIRE_POPO_E] = {JOUEUR_1_S, BOIRE_POPO_J2_A},
    [JOUEUR_2_S][PV_0_E] = {FIN_S, FIN_A},
    [FIN_S][DEMARRER_E] = {JOUEUR_1_S, DEMARRE_A}
};

void attaquer();
void boire_potion();
void lancer_partie();
void afficher_mae();

Etat getEtat();

#endif
