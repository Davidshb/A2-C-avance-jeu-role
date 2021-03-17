#include "personnage.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    personnage_new(5);

    edit_etat();

    int degat = personnage_attaquer();

    int degat2 = personnage_attaquer();

    printf("\ndégat à subir %d\n", degat);

    // on voit bien 
    printf("\ndégat à subir %d\n", degat2);

    recevoir_degat(degat);

    edit_etat();

    personnage_free();
    return 0;
}