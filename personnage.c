#include "personnage.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
    return this->force + chance(DEGAT_ALEA_MIN, DEGAT_ALEA_MAX);
}

bool Personnage_boire_potion(Personnage *this)
{
    this->nb_potion--;
    if (chance(0, POPO_CASSE_ALEA) == 1)
    {
        printf("la potion s'est cassée");
        return false;
    }
    int tmp = this->vie;
    int res = tmp + PV_POTION + chance(POPO_BOIRE_MIN, POPO_BOIRE_MAX);

    if (res < VIE_MAX)
        this->vie = res;
    else
        this->vie = VIE_MAX;

    printf("%d --> %d\n", tmp, this->vie);

    return true;
}

void Personnage_voir_etat(Personnage *this)
{
    printf("Vie : %d\n", this->vie);
    printf("Force: %d\n", this->force);
    printf("Potion: %d\n", this->nb_potion);
}

void Personnage_recevoir_degat(Personnage *this, int degat)
{
    this->vie -= degat;
}

/**
 * return [range_min;range_max[
 */
static int chance(int range_min, int range_max)
{
    int diff = range_max - range_min;
    if (diff <= 0)
        return 0;

    return rand() % diff + range_min;
}

void Personnage_voir_deux_etats(Personnage *j1, Personnage *j2)
{
    printf("Vie :        %-3d       %-3d\n", j1->vie, j2->vie);
    printf("Force :      %-3d       %-3d\n", j1->force, j2->force);
    printf("nb potions : %d         %d\n", j1->nb_potion, j2->nb_potion);
}

bool Personnage_a_des_potions(Personnage *this)
{
    return this->nb_potion > 0;
}

bool Personnage_full_pv(Personnage *this)
{
    return this->vie == VIE_MAX;
}

int Personnage_gagnant(Personnage *j1, Personnage *j2)
{
    return j1->vie > j2->vie ? 1 : 2;
}