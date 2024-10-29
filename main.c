#include "takuzu.h"



int main()
{
    menu();
}



//On creer un menu renvoyant aux différentes partie du projet, resoudre une grille, resolution automatique d'une grille, generation aléatoire d'une grille
void menu()
{
    color(15,0);
    printf("\n\n%c ",5);
    color(10,0);
    printf("MENU PRINCIPAL ");
    color(15,0);
    printf("%c \n\n\n",5);
    color(15,0);
    int choix = 0;

    do {

        printf("Ou souhaitez-vous aller ? \n\n");
        printf("1 - Resoudre une grille de Takuzu\n");
        printf("2 - Solution d'une grille de Takuzu\n");
        printf("3 - Generer une grille de Takuzu\n");
        printf("\nSaisissez le numero correspondant a votre choix:\n");
        scanf("%d",&choix);

    }while((choix < 1)||(choix>3));

    switch (choix)
    {
        case 1:
            menu_resoudre_grille();
            break;

        case 2:
            menu_robot_resoudre_grille();
            break;

        case 3:
            menu_generer();
            break;
    }


}

//menu de resolution d'une grille lorque la taille choisi est une 4x4 le joueur peut alors crer son propre masque ou jouer sur une grille aléatoire
void menu_resoudre_4x4()
{
    int choix = 0;
    int ** Mask = NULL;
    do {

        color(15,0);
        printf("\n\n%c ",5);
        color(10,0);
        printf("RESOUDRE UNE GRILLE 4x4");
        color(15,0);
        printf("%c \n\n\n",5);
        color(15,0);

        printf("1 - Creer une grille \n");
        printf("2 - Jouer sur une grille aleatoire \n");
        printf("3 - Retourner au menu principal\n");
        printf("\nSaisissez le numero correspondant a votre choix:\n ");
        scanf("%d",&choix);

    } while ((choix < 1)||(choix>3));

    switch (choix)
    {
        case 1:
            Mask = creation_masque();
            jouer_4x4(Mask);
            break;
        case 2:
            Mask = masque_alea();
            jouer_4x4(Mask);
            break;
        case 3:
            menu();
            break;
    }
}

//le joueur choisi sur quelle taille de grille il voudrait jouer
void menu_resoudre_grille()
{

    int choix = 0;
    do {

        color(15,0);
        printf("\n\n%c ",5);
        color(10,0);
        printf("RESOUDRE UNE GRILLE ");
        color(15,0);
        printf("%c \n\n\n",5);
        color(15,0);

        printf("Quelle taille de grille voulez-vous resoudre ? \n\n");
        printf("1 - Grille 4x4 \n");
        printf("2 - Grille 8x8 \n");
        printf("3 - Retourner au menu principal\n\n");
        printf("\nSaisissez le numero correspondant a votre choix:\n ");
        scanf("%d",&choix);


    }while((choix < 1)||(choix>3));

    switch (choix)
    {
        case 1 :
            menu_resoudre_4x4();
            break;

        case 2:
            menu_resoudre_8x8();
            break;

        case 3 :
            menu();
            break;

    }


}

//Menu de resolution automatique d'une grille, le joueur choisi sur quelle taille donner au robot
void menu_robot_resoudre_grille()
{
    int choix = 0;
    do {

        color(15,0);
        printf("\n\n%c ",5);
        color(10,0);
        printf("SOLUTION D'UNE GRILLE PAR LE ROBOT TAZUKU ");
        color(15,0);
        printf("%c \n\n\n",5);
        color(15,0);
        printf("Quelle taille de grille voulez-vous que TAZUKU resolve ? \n\n");
        printf("1 - Grille 4x4 \n");
        printf("2 - Grille 8x8 \n");
        printf("3 - Retourner au menu principal\n");
        printf("\nSaisissez le numero correspondant a votre choix:\n ");
        scanf("%d",&choix);


    }while((choix < 1)||(choix>3));

    switch (choix)
    {
        case 1:
            menu_robot_4x4();
            break;

        case 2:
            menu_robot_8x8();
            break;

        case 3:
            menu();
            break;

    }
}

//Menu de resolution automatique si la taille choisi est 4x4, le joueur chois de donner un masque au robot ou de le voir resoudre une grille aleatoire
void menu_robot_4x4()
{
    int choix = 0;
    int ** masque = NULL;

    do {

        color(15,0);
        printf("\n\n%c ",5);
        color(10,0);
        printf("SOLUTION D'UNE GRILLE 4x4 PAR LE ROBOT TAZUKU ");
        color(15,0);
        printf("%c \n\n\n",5);
        color(15,0);
        printf("1 - Creer une grille a resoudre \n");
        printf("2 - Resoudre sur une grille aleatoire \n");
        printf("3 - Retouner au menu principal\n");
        printf("\nSaisissez le numero correspondant a votre choix:\n ");
        scanf("%d",&choix);

    } while ((choix < 1)||(choix>3));

    switch (choix)
    {
        case 1:
            masque = creation_masque();
            resolution_4x4(masque);
            break;

        case 2:
            masque = masque_alea();
            resolution_4x4(masque);
            break;

        case 3:
            menu();
            break;
    }

}

//Menu de generation d'une grille valide, le joueur choisi la taille de grille qu'il veut voir generee
void menu_generer()
{
    color(15,0);
    printf("\n\n%c ",5);
    color(10,0);
    printf("GENERER UNE GRILLE ");
    color(15,0);
    printf("%c \n\n\n",5);
    color(15,0);
    int choix = 0;

    do {
        printf("Quelle taille de grille voulez-vous generer ? \n\n");
        printf("1 - Grille 4x4 \n");
        printf("2 - Grille 8x8 \n");
        printf("3 - Retourner au menu principal\n");
        printf("\nSaisissez le numero correspondant a votre choix:\n");
        scanf("%d", &choix);
    } while ((choix < 1) || (choix > 3));

    switch (choix)
    {

        case 1:
            generer4x4();
            break;


        case 2:
            generer8x8();
            break;

        case 3:
            menu();
            break;


    }
}


//menu de resolution d'une grille lorque la taille choisi est une 4x4 le joueur peut alors crer son propre masque ou jouer sur une grille aléatoire
void menu_resoudre_8x8()
{
    int choix = 0;
    int ** Mask = NULL;
    do {

        color(15,0);
        printf("\n\n%c ",5);
        color(10,0);
        printf("RESOUDRE UNE GRILLE 8x8");
        color(15,0);
        printf(" %c \n\n\n",5);
        color(15,0);
        printf("1 - Creer une grille \n");
        printf("2 - Jouer sur une grille aleatoire \n");
        printf("3 - Retourner au menu principal\n");
        printf("\nSaisissez le numero correspondant a votre choix:\n ");
        scanf("%d",&choix);

    } while ((choix < 1)||(choix>3));

    switch (choix)
    {
        case 1:
            Mask = creation_masque8x8();
            jouer_8x8(Mask);
            break;
        case 2:
            Mask = alea_masque8x8();
            jouer_8x8(Mask);
            break;
        case 3:
            menu();
            break;
    }
}

//Menu de resolution automatique si la taille choisi est 8x8, le joueur chois de donner un masque au robot ou de le voir resoudre une grille aleatoire
void menu_robot_8x8()
{
    int choix = 0;
    int ** masque = NULL;

    do {

        color(15,0);
        printf("\n\n%c ",5);
        color(10,0);
        printf("SOLUTION D'UNE GRILLE 8x8 PAR LE ROBOT TAZUKU ");
        color(15,0);
        printf("%c \n\n\n",5);
        color(15,0);
        printf("1 - Creer une grille a resoudre \n");
        printf("2 - Resoudre sur une grille aleatoire \n");
        printf("3 - Retouner au menu principal\n");
        printf("\nSaisissez le numero correspondant a votre choix:\n ");
        scanf("%d",&choix);

    } while ((choix < 1)||(choix>3));

    switch (choix)
    {
        case 1:
            masque = creation_masque8x8();
            resolution_8x8(masque);
            break;

        case 2:
            masque = alea_masque8x8();
            resolution_8x8(masque);
            break;

        case 3:
            menu();
            break;
    }
}

// fonction d'affichage de couleurs
void color(int couleurDuTexte,int couleurDeFond)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}


