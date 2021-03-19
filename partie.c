#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "partie.h"
#include "personnage.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void clear_console()
{
    printf("\e[1;1H\e[2J");
}

static Personnage *j1, *j2;

static void performAction(TransitionAction action);

static Entree attaque(Personnage *attaquant, Personnage *attaque);
static void boire_popo(Personnage *joueur);
static void run_fsm_partie(Entree entree);

static Entree fcn_init();
static Entree fin_partie();

static Etat etatPartie = FIN_S;

static Entree transitionSuivante = DEMARRER_E;

static Entree choix_joueur(Personnage *joueur_ayant_la_main, Personnage *joueur_autre, int j)
{
    int action_joueur = -1;
    bool joueur_a_des_potions = Personnage_a_des_potions(joueur_ayant_la_main);

    do
    {
        clear_console();
        printf("à votre tour joueur %d\n", j);
        printf("-------------j1--------j2--\n");
        Personnage_voir_deux_etats(j1, j2);
        printf("---------------------------\n");
        printf("1 -> attaquer joueur%d\n2 -> boire potion\n choix : ", j % 2 + 1);
        if (!scanf("%d", &action_joueur))
            while (getchar() != '\n')
                ;
        if (action_joueur == 2)
        {
            // possibilité de faire une fonction mais un peu la flemme
            if (!joueur_a_des_potions)
            {
                clear_console();
                printf("Vous n'avez plus de potion !\n Appuyer sur entrer...\n");
                getchar();
                getchar();
                action_joueur = -1;
            }
            else if (Personnage_full_pv(joueur_ayant_la_main))
            {
                clear_console();
                printf("Vous êtes déjà à 100 PV\n Appuyer sur entrer...\n");
                getchar();
                getchar();
                action_joueur = -1;
            }
        }
    } while (!(action_joueur == 1 || action_joueur == 2));

    Entree res = ACTION_E;

    if (action_joueur == 1)
        res = attaque(joueur_ayant_la_main, joueur_autre);
    else
        boire_popo(joueur_ayant_la_main);

    return res;
}

void action_suivante()
{
    run_fsm_partie(transitionSuivante);
}

static void run_fsm_partie(Entree entree)
{
    TransitionAction anAction;
    Etat aState;

    anAction = mySm[etatPartie][entree].action;
    aState = mySm[etatPartie][entree].destinationEtat;

    performAction(anAction);
    etatPartie = aState;
}

static void performAction(TransitionAction action)
{
    switch (action)
    {
    case NOP_A:
        break;
    case DEMARRE_A:
        transitionSuivante = fcn_init();
        break;
    case TOUR_J1_A:
        transitionSuivante = choix_joueur(j1, j2, 1);
        break;
    case TOUR_J2_A:
        transitionSuivante = choix_joueur(j2, j1, 2);
        break;
    case FIN_A:
        transitionSuivante = fin_partie();
        break;
    case ARRET_A:
        continue_partie = false;
        break;
    }
}

static Entree fcn_init()
{
    int t = 4;
    while (t)
    {
        clear_console();
        printf("les règles sont simples. Vous jouez à tour de rôle\n");
        printf("le premier à 0 pv a perdu. Vous infligez chacun %d de dégat additionné à\n", FORCE);
        printf("des dégats aléatoires entre %d et %d. donc vous infligez entre %d et %d\n", DEGAT_ALEA_MIN, DEGAT_ALEA_MAX, DEGAT_ALEA_MIN + FORCE, DEGAT_ALEA_MAX + FORCE);
        printf("pour les potions vous avez une chance sur %d qu'elle se casse.\n", POPO_CASSE_ALEA);
        printf("et pour finir en buvant une potion elle vous régène entre %d et %d de pv\n", PV_POTION + POPO_BOIRE_MIN, PV_POTION + POPO_BOIRE_MAX);
        printf("Appuyer sur entrer pour lancer la partie...%c", t == 4 ? '\0' :'\n');
        if(t == 4)
            getchar();
        printf("%d ...\n", t-1);
        sleep(1);
        t--;
    }

    j1 = Personnage_new();
    j2 = Personnage_new();

    return START_E;
}

static Entree fin_partie()
{
    clear_console();
    printf("fin de la partie\n");
    printf("-------------j1--------j2--\n");
    Personnage_voir_deux_etats(j1, j2);
    Personnage_free(j1);
    Personnage_free(j2);

    printf("Joueur %d a gangé !\n", Personnage_gagnant(j1, j2));

    int choix = -1;

    do
    {
        printf("Relancer une game ? 1 -> oui | 2 -> non\n choix : ");
        if (!scanf("%d", &choix))
            while (getchar() != '\n')
                ;

    } while (choix != 1 || choix != 2);

    if (choix == 1)
        return DEMARRER_E;
    else
        return ARRET_E;
}

static Entree attaque(Personnage *attaquant, Personnage *cible)
{
    int degat = Personnage_attaquer(attaquant);
    Personnage_recevoir_degat(cible, degat);
    Personnage_voir_etat(cible);

    if (!Personnage_est_vivant(cible))
        return FIN_E;
    return ACTION_E;
}

static void boire_popo(Personnage *joueur)
{
    clear_console();
    int res = Personnage_boire_potion(joueur);

    if (!res)
        printf("la potion s'est malheureusement cassée\n");
    printf("appuyer sur entrer pour passer à la suite ...\n");
    getchar();
    getchar();
}
