#include <stdio.h>
#include "personnage.h"
#include "partie.h"

void choix_joueur(int j)
{
    int action_joueur;
    printf("à votre tour joueur %d\n", j);
    printf("1 -> attaquer joueur%d\n2 -> boire potion\n choix : ", j % 2 + 1);
    scanf("%d", &action_joueur);
    if (action_joueur == 1)
        attaquer();
    else if (action_joueur == 2)
        boire_potion();
}

void main()
{
    while (1)
    {
        switch (getEtat())
        {
        case FIN_S:
            printf("appuyer sur entrer pour démarrer la partie");
            getchar();
            lancer_partie();
            break;
        case JOUEUR_1_S:
            choix_joueur(1);
            break;
        case JOUEUR_2_S:
            choix_joueur(2);
            break;
        }
    }
}