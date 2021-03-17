#include "personnage.h"
#include <stdio.h>

void main() {
    Personnage* pers1 = Personnage_new(), *pers2 = Personnage_new();

    Personnage_voir_etat(pers1);

    int degat = Personnage_attaquer(pers1);

    Personnage_recevoir_degat(pers2, degat);

    Personnage_voir_etat(pers2);

    Personnage_boire_potion(pers2);

    Personnage_voir_etat(pers2);

    Personnage_free(pers1);
    Personnage_free(pers2);
}