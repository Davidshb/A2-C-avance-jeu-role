#include "personnage.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int chance();

struct Personnage_t
{
    int vie;
    int force;
    int nb_potion;
};

Personnage *Personnage_new()
{
    Personnage *res = malloc(sizeof(Personnage));

    res->force = FORCE;
    res->vie = VIE_MAX;
    res->nb_potion = NB_POTIONS;

    return res;
}

void Personnage_free(Personnage *this)
{
    free(this);
}

int Personnage_est_vivant(Personnage *this)
{
    return this->vie > 0;
}

int Personnage_attaquer(Personnage *this)
{
    return this->force + chance();
}

int Personnage_boire_potion(Personnage *this)
{
    this->nb_potion--;
    if (chance() == 1)
    {
        printf("la potion s'est cassée");
        return 0;
    }
    int res = this->vie + PV_POTION;

    if(res < VIE_MAX)
        this->vie = res;
    else
        this->vie = VIE_MAX;
    return 1;
}

void Personnage_voir_etat(Personnage* this)
{
    printf("\n\n%%%%%%%%%%%%\n");
    printf("Vie : %d\n", this->vie);
    printf("Force: %d\n", this->force);
    printf("Potion: %d\n", this->nb_potion);
}

void Personnage_recevoir_degat(Personnage* this, int degat)
{
    this->vie -= degat;
}

static int chance()
{
    static int force = 0;
    if (force == 0)
    {
        srand(time(NULL));
        force = 1;
    }

    return rand() % 4 + 1;
}