#ifndef _PARTIE_H
#define _PARTIE_H

#include "personnage.h"
#include <stdbool.h>

static bool continue_partie = true;

typedef enum
{
    TOUR_J1_S,
    TOUR_J2_S,
    FIN_S,
    INIT_S,
    NB_ETAT
} Etat;

typedef enum
{
    NOP_A=0,
    DEMARRE_A,
    TOUR_J1_A,
    TOUR_J2_A,
    ARRET_A,
    FIN_A
} TransitionAction;

typedef enum
{
    ACTION_E = 0,
    FIN_E,
    DEMARRER_E,
    START_E,
    ARRET_E,
    NB_ENTREE
} Entree;

typedef struct
{
    Etat destinationEtat;
    TransitionAction action;
} Transition;

static Transition mySm[NB_ETAT][NB_ENTREE] = {
    [TOUR_J1_S][ACTION_E] = {TOUR_J2_S, TOUR_J2_A},
    [TOUR_J1_S][FIN_E] = {FIN_S, FIN_A},
    [TOUR_J2_S][ACTION_E] = {TOUR_J1_S, TOUR_J1_A},
    [TOUR_J2_S][FIN_E] = {FIN_S, FIN_A},
    [FIN_S][DEMARRER_E] = {INIT_S, DEMARRE_A},
    [INIT_S][START_E] = {TOUR_J1_S, TOUR_J1_A},
    [FIN_S][ARRET_E] = {FIN_S, ARRET_A}
};

void action_suivante();

#endif
