#include "personnage.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    personnage_new(5);

    edit_etat();

    int degat = personnage_attaquer();

    printf("\ndégat à subir %d\n", degat);

    recevoir_degat(degat);

    edit_etat();

    personnage_free();
    return 0;
}