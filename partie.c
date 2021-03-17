#include <stdio.h>
#include "partie.h"

static Personnage *j1, *j2;

static void performAction(TransitionAction action);

static void attaque(Personnage *attaquant, Personnage *attaque);
static void boire_popo(Personnage *joueur);
static void demarrerPartie();
static void fin_partie();

static Etat etatPartie = FIN_S;

Etat getEtat()
{
    return etatPartie;
}

static void run_fsm_partie(Entree entree)
{
    TransitionAction anAction;
    Etat aState;

    anAction = mySm[etatPartie][entree].action;
    aState = mySm[etatPartie][entree].destinationEtat;

    etatPartie = aState;
    performAction(anAction);
}

static void performAction(TransitionAction action)
{
    switch (action)
    {
    case NOP_A:
        break;
    case ATTAQUE_J1_A:
        attaque(j1, j2);
        break;
    case ATTAQUE_J2_A:
        attaque(j2, j1);
        break;
    case BOIRE_POPO_J1_A:
        boire_popo(j1);
        break;
    case BOIRE_POPO_J2_A:
        boire_popo(j2);
        break;
    case FIN_A:
        fin_partie();
        break;
    case DEMARRE_A:
        demarrerPartie();
        break;
    }
}

static void demarrerPartie()
{
    j1 = Personnage_new();
    j2 = Personnage_new();
}

static void fin_partie()
{
    printf("fin de la partie");
    Personnage_voir_etat(j1);
    Personnage_voir_etat(j2);
    Personnage_free(j1);
    Personnage_free(j2);
}

static void attaque(Personnage *attaquant, Personnage *attaque)
{
    int degat = Personnage_attaquer(attaquant);
    Personnage_recevoir_degat(attaque, degat);
    Personnage_voir_etat(attaque);
    if (!Personnage_est_vivant(attaque))
        run_fsm_partie(PV_0_E);
}

static void boire_popo(Personnage *joueur)
{
    int res = Personnage_boire_potion(joueur);
    Personnage_voir_etat(attaque);
    if (res)
        printf("la potion a été bu\n");
    else
        printf("la potion n'a pas été bu\n");
}

void attaquer()
{
    run_fsm_partie(ATTAQUER_E);
}

void boire_potion()
{
    run_fsm_partie(BOIRE_POPO_E);
}

void lancer_partie()
{
    run_fsm_partie(DEMARRER_E);
}
