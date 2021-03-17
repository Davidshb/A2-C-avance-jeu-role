#include "personnage.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

static int vie = -1;
static int force = -1;
static int nb_potion = -1;

static int chance();

void personnage_new(int _force) {
    srand(time(NULL));
    vie = 100;
    force = _force;
    nb_potion = 10;
}

void personnage_free() {
    int vie = -1;
    int force = -1;
    int nb_potion = -1;
}

int personnage_est_vivant() {
    return vie > 0;
}

int personnage_attaquer() {
    return force + chance();
}

int personnage_boire_potion() {
    nb_potion--;
    if(chance() == 1) {
        printf("la potion s'est cassée");
        return 0;
    }
    vie += 10;
    return 1;
}

void edit_etat() {
    printf("\n\n%%%%%%%%%%%%\n");
    printf("Vie : %d\n", vie);
    printf("Force: %d\n", force);
    printf("Potion: %d\n", nb_potion);
}

void recevoir_degat(int degat) {
    vie -= degat;
}


static int chance() {
    return rand() % 4 + 1;
}