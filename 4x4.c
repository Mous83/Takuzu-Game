//
// Created by edema on 15/04/2022.
//
#include "takuzu.h"

// On crée un fichier c regroupant les fonctions liées à la matric 4x4

// Pour créer une grille de takuzu valide on se base sur les nombres binaires

// On créer une fonction qui transforme un nombre entier en son nombre binaire correspondant sous forme de tableau
int* binary_conversion(int val)
{
    int * tab = (int*) malloc(4*sizeof(int));

    for (int i=3 ; i >= 0; i--)
    {
        tab[i] = val%2;
        val = val/2;
    }


    return tab;
}

//On créer une fonction qui prends un nombre  binaire et renvoie son inverse en decimal
int inverse_ligne(int* tab)
{
    int tab_2[4] = {};

    for (int j =0; j<4;j++)
    {
        tab_2[j] = tab[j];
    }

    int inverse = 0;
    int pui=3;


    for (int i = 0; i<4;i++)
    {
        if(tab_2[i] == 1)
        {
            tab_2[i] = 0;
        }
        else if (tab_2[i] == 0)
        {
            tab_2[i] = 1;
        }
    }

    for (int k = 0 ; k<4; k++)
    {
        inverse += tab_2[k]*pow(2,pui);
        pui --;
    }

    return inverse;
}

int** map_valide_4_4(int ** map)
{

    map = (int**) malloc(4* sizeof(int*));

    for (int i = 0;i<4;i++)
    {
        map[i]=(int*)malloc(4*sizeof(int));
    }

    map = fill_map_4x4(map);

    return map;

}

// On remplie notre map 4x4
int** fill_map_4x4(int** map)
{

    srand(time(NULL));

    int val;

    //On prend aléatoirement un nombre decimale qui contient autant de 1 que de 0 en binaire
    do
    {
        val = rand()%16;

    } while ((val != 3)&&(val != 5)&&(val != 6)&&(val != 9)&&(val != 10)&&(val != 12));

    // Grâce aux fonctions préalablement défini on créer un nombre binaire valide et son inverse correspondant aux deux premières lignes de la matrice 4x4

    int * T = binary_conversion(val);
    int inv = inverse_ligne(T);
    int * T2 = binary_conversion(inv);
    int val2;

    do
    {
        val2 = rand()%16;

    } while ((val2 != 3)&&(val2 != 5)&&(val2 != 6)&&(val2 != 9)&&(val2 != 10)&&(val2 != 12));


//On recherche aléatoirement un nombre valide différent du premier
    while ((val == val2)||(val2 == inv))
    {

        do
        {
            val2 = rand()%16;

        } while ((val2 != 3)&&(val2 != 5)&&(val2 != 6)&&(val2 != 9)&&(val2 != 10)&&(val2 != 12));


    }

    // On créer deux nouveau nombre binaire correspondant au lignes 3 et 4 de la matrice 4x4
    int * T3 = binary_conversion(val2);
    int inv2 = inverse_ligne(T3);
    int * T4 = binary_conversion(inv2);

    map[0] = T;
    map[1] = T2;
    map[2] = T3;
    map[3] = T4;

    return map;

}

// On affiche notre carte dans le cas d'une 4x4
void print_map_4x4(int** map)
{
    printf("          %c",'A');
    // On affiche les indices de A a D pour simplifier à l'utilisateur

    for (int j=0; j<4-1;j++)
    {
        printf("         %c",'B'+j);
    }
    printf("\n");


    printf("     ......................................... \n");
    for(int i=0; i<4;i++)
    {
        printf(" %d   :",i+1);
        for(int j=0;j<4;j++)
        {
            if ((map[i][j] != -1)&&(map[i][j] != -5)&&(map[i][j] != -2)&&(map[i][j]!= -7))
            {
                printf("    %d    :", map[i][j]);
            }
            //Si la valeur de la case est -1 cela signifie que la case est masqué pour le joueur on affiche alors un vide à cet emplacement
            else if (map[i][j] == -1)
            {
                printf("         :");
            }
                //Si la valeur de la case est -5 cela signifie que la case est neutre pour le joueur on affiche alors une croix à cet emplacement
            else if (map[i][j] == -5)
            {
                color(4,0);
                printf("    x    ");
                color(15,0);
                printf(":");
            }
            else if (map[i][j] == -2)
            {
                color(14,0);
                printf("    +    ");
                color(15,0);
                printf(":");
            }
            else if (map[i][j] == -7)
            {
                color(10,0);
                printf("    +    ");
                color(15,0);
                printf(":");
            }
        }
        printf("\n");
        printf("     :.........:.........:.........:.........: \n");
    }
    printf("\n");

}

//On créer une fonction qui créer un masque aléatoire
int** masque_alea()
{
    int ** masque = (int**) malloc(4* sizeof(int*));

    for(int i = 0;i<4;i++)
    {
        masque[i]=(int*)malloc(4*sizeof(int));
    }

    // On choisi aléatoirement de remplir les cases de 1 ou 0
    srand(time(NULL));
    for(int i=0;i<4;i++)
    {
        for(int j = 0; j < 4; j++)
        {
            int aleatoire = rand() % 2;
            masque[i][j] = aleatoire;
        }
    }

    return masque;
}

//On créer notre grille de jeu
int ** grille_de_jeu(int** map, int** masque)
{

    int ** grille = (int**) malloc(4* sizeof(int*));

    for (int i = 0;i<4;i++)
    {
        grille[i]=(int*)malloc(4*sizeof(int));
    }
    // On remplit notre grille de jeu par les valeurs de la grille solutions
    for(int k = 0 ; k<4 ; k++)
    {
        for(int l=0; l<4; l++)
        {
            grille[k][l] = map[k][l];
        }
    }
    //On remplit par -1 les cases pour lesquelles masque[i][j] = 1
    for(int k = 0 ; k<4 ; k++)
    {
        for(int l=0; l<4; l++)
        {
           if(masque[k][l] == 1)
           {
               grille[k][l] = -1;
           }
        }
    }


    return grille;
}

//On creer la fonction pour faire jouer l'utilisateur
void jouer_4x4(int ** masque)
{
    //On créer une grille de jeu
    int ** solutions = NULL;
    int ** grille = NULL;
    solutions = map_valide_4_4(solutions);
    grille = grille_de_jeu(solutions,masque);

    // On initialise les vie du joueur et un booléen
    int verif = 0;
    int vie = 3;
    printf("\n \n \n");
    // tant que verif est nul le jeu est en cours
    do
    {
        printf("\n");
        char colonne = 'z';
        int ligne = -1;
        int i;
        int j;
        do {
            //On affiche la grille et on demande au joueur de se diriger vers une case

            if (vie == 3)
            {
                printf("     Vie:");
                color(4,0);
                printf(" %c %c %c \n\n",3,3,3);
                color(15,0);
            }
            else if (vie == 2)
            {
                printf("     Vie:");
                color(4,0);
                printf(" %c %c \n\n",3,3);
                color(15,0);
            }
            else if ( vie == 1)
            {
                printf("     Vie:");
                color(4,0);
                printf(" %c \n\n",3);
                color(15,0);
            }
            print_map_4x4(grille);

            do {

                printf("Entrez une case a remplir (exemple A1,B2,C3...):\n");
                scanf(" %c%d", &colonne,&ligne);

            }while ( ( (colonne > 'D' )||( colonne < 'A') )||( (ligne > 4 )||( ligne < 1) ) );



            switch (colonne) {
                case 'A':
                    j = 0;
                    break;
                case 'B':
                    j = 1;
                    break;
                case 'C':
                    j = 2;
                    break;
                case 'D':
                    j = 3;
                    break;
            }

            switch (ligne) {
                case 1:
                    i = 0;
                    break;
                case 2:
                    i = 1;
                    break;
                case 3:
                    i = 2;
                    break;
                case 4:
                    i = 3;
                    break;
            }

            //Si la grille n'est pas masqué on ne peut rien faire
            if(grille[i][j] != -1)
            {
                color(14,0);
                printf("Vous ne pouvez pas modifier cette case \n");
                color(15,0);
            }

        }while(grille[i][j] != -1);


        //Si la grille est masqué on demande au joueur de saisir 1 ou 0
        int val = -1;
        do {
            printf("Entrez 0 ou 1 en (%c%d) ou 2 pour abandonner: \n",colonne,ligne);
            scanf("%d",&val);

        }while((val < 0)||(val > 2));

        if (val == 2)
        {
            color(4,0);
            printf("\nQuel dommage tu as abandonne...\n");
            sleep(3);
            color(15,0);
            free4x4(masque);
            free4x4(solutions);
            free4x4(grille);
            menu_resoudre_grille();
        }


        //On verifie la validité du coup du joueur
        int valide = coup_valide(val,grille,i,j);

        //On renvoie un message selon le type de coup jouer
        switch (valide) {


            case 0:
            {

                color(14,0);
                printf("\n     Coup valide !\n");
                color(15,0);
                grille[i][j] = val;
                sleep(1);
                break;

            }
            case 1:
            {
                color(10, 0);
                printf("\n     Coup correct ! \n");
                color(15, 0);
                grille[i][j] = val;
                sleep(1);
                break;

            }

            case - 1 :
            {
                color(4, 0);
                printf("\n     Coup incorrect ! \n");
                color(15, 0);
                vie--;
                sleep(1);
                break;

            }

            case -2: {

                color(4, 0);
                printf("\n     Tu es bloque ! \n");
                color(15, 0);
                sleep(1);
                grille[i][j] = -5;
                print_map_4x4(grille);
                sleep(3);
                vie = 0;
                break;
            }
        }

        int cpt_1 = 0;
        int cpt_0 = 0;
        //Apres chaque coup on verifie en comptant le nombre de -1 si la grille est rempli
        int cpt_m1 = 0;
        for( int k = 0; k<4 ; k++)
        {
            for (int l = 0 ; l<4 ; l++)
            {
                if (grille[k][l] == -1 )
                {
                    cpt_m1++;
                }
                if (grille[k][l] == 0 )
                {
                    cpt_0++;
                }
                if (grille[k][l] == 1 )
                {
                    cpt_1++;
                }
            }
        }
        //On verifie après chaque coup le nombre de vies
        if (vie <= 0)
        {
            verif = -1;
        }
        //Si la grille est rempli la partie est fini
        if ((cpt_m1 == 0)&&(cpt_0 == cpt_1)&&(cpt_0 == 8))
        {
            verif = 1;
        }


    }while(verif == 0 );
    printf("\n");
    //Selon s'il a gagner ou perdu on affiche un message a l'utilisateur
    if (verif == 1)
    {
        print_map_4x4(grille);
        color(10,0);
        printf("\nFelications tu as gagne ! Essaie les grilles 8x8 !\n");
        color(15,0);
    }
    else if(verif == -1)
    {
        color(4,0);
        printf("\nDommage tu as perdu ! Retente ta chance ! \n");
        color(15,0);
    }
    sleep(3);
    free4x4(solutions);
    free4x4(masque);
    free4x4(grille);
    menu_resoudre_grille();
}

//On créer une fonction qui verifie la validite du coup jouer par l'utilisateur
int coup_valide(int val,int ** grille,int ligne,int colonne)
{
    int coup = -2;

    //On appelle 3 autres fonctions et selon ce qu'elles renvoient on determine la validite du coup
    int incorrec = incorrect(grille,val,ligne,colonne);
    int correc = correct( grille ,val ,ligne ,colonne);
    int bloque = bloquer(grille,ligne,colonne);

    //Si le joueur est bloqué
    if (bloque == 1)
    {
        coup = - 2;
    }
    //Si le coup du joueur est incorrect
    else if (incorrec == 1)
    {
        coup = -1;
    }
    //Si le joueur a joué le bon coup
    else if (correc == 1 )
    {
        coup = 1;
    }
    //Si le joueur n'avait aucune obligation sur son coup
    else
        coup = 0;

    return coup;
}

int correct(int ** grille, int val,int ligne, int colonne)
{
    //Pour determiner si un coup est correct:
    int cpt0_lig = 0;
    int cpt1_lig = 0 ;
    int cpt0_col = 0;
    int cpt1_col = 0;
    int verif = -1;
    //On compte le nombre de 1 et de 0 sur la ligne et sur la colonne sur laquelle il joue
    for(int i = 0;i<4;i++)
    {
        if(grille[ligne][i]==0)
        {
            cpt0_lig++;
        }
        else if (grille[ligne][i] == 1)
        {
            cpt1_lig++;
        }
    }

    for(int j = 0;j<4;j++)
    {
        if(grille[j][colonne]==0)
        {
            cpt0_col++;
        }
        else if (grille[j][colonne] == 1)
        {
            cpt1_col++;
        }
    }

    //Si le nombre de 0 sur la ligne ou la colonne est déjà égale à 2 et le nombre de 1 < 2 alors il ne peut que jouer 1
    if (val == 1)
    {
        if((cpt1_lig <= 1) && (cpt0_lig == 2))
        {
            verif = 1;
        }
        else if((cpt1_col <= 1) && (cpt0_col == 2))
        {
            verif = 1;
        }
    }
    //Si le nombre de 1 sur la ligne ou la colonne est déjà égale à 2 el le nombre de 0 < 2 alors il ne peut que jouer 0
    if (val == 0)
    {
        if((cpt0_lig <= 1) && (cpt1_lig == 2))
        {
            verif = 1;
        }
        else if((cpt0_col <= 1) && (cpt1_col == 2))
        {
            verif = 1;
        }
    }

    return verif;

}

int incorrect(int ** grille, int val,int ligne, int colonne)
{
    int cpt0_lig = 0;
    int cpt1_lig = 0 ;
    int cpt0_col = 0;
    int cpt1_col = 0;
    int verif = -1;
//De meme que pour les coup correct on compte les nombres de 0 et 1 sur la lignes et la colonnes jouées
    for(int i = 0;i<4;i++)
    {
        if(grille[ligne][i]==0)
        {
            cpt0_lig++;
        }
        else if (grille[ligne][i] == 1)
        {
            cpt1_lig++;
        }
    }

    for(int j = 0;j<4;j++)
    {
        if(grille[j][colonne]==0)
        {
            cpt0_col++;
        }
        else if (grille[j][colonne] == 1)
        {
            cpt1_col++;
        }
    }
// Si le joueur joue 1 alors qu'il y en a deja deux sur la ligne ou la colonne , le coup est incorrect
    if( val == 1)
    {
        if((cpt1_lig >= 2) || (cpt1_col >= 2))
        {
            verif = 1;
        }
    }
    //Si le joueur joue 0 alors qu'il y en a deja deux sur la ligne ou la colonne , le coup est incorrect
    else if (val == 0)
    {
        if ((cpt0_lig >= 2) || (cpt0_col >= 2)) {
            verif = 1;
        }
    }
    return verif;

}

int bloquer(int** grille, int ligne, int colonne)
{
    int cpt0_lig = 0;
    int cpt1_lig = 0 ;
    int cpt0_col = 0;
    int cpt1_col = 0;
    int verif = -1;
//On recompte également le nombre de 1 et de 0
    for(int i = 0;i<4;i++)
    {
        if(grille[ligne][i]==0)
        {
            cpt0_lig++;
        }
        else if (grille[ligne][i] == 1)
        {
            cpt1_lig++;
        }
    }

    for(int j = 0;j<4;j++)
    {
        if(grille[j][colonne]==0)
        {
            cpt0_col++;
        }
        else if (grille[j][colonne] == 1)
        {
            cpt1_col++;
        }
    }
    //Si il y a deux 1 sur colonne joué et deux 0 sur la ligne joué ou inversement le joueur se retrouve bloqué, il a directement perdu
    if(((cpt1_col >= 2)&&(cpt0_lig >= 2))||((cpt0_col >= 2)&&(cpt1_lig >= 2)))
    {
        verif = 1;
    }
    return verif;
}

//On créer une fonction qui permet a l'utilisateur de creer un masque sur laquelle jouer
int ** creation_masque()
{

    //On demande à l'utlisateur de saisir le nombre d'éléments à masquer selon le niveau de difficulté souhaiter
    printf("CREER VOTRE GRILLE : \n\n\n");
    int nombre;
    printf("Saisir le nombre d'elements que vous souhaitez cacher (plus il y en a plus le jeu est difficile) \n");
    do
    {
        printf("entre 1 et 16 \n");
        scanf("%d", &nombre);
    }
    while ((nombre > 16)||(nombre < 1));

    int ** M;
    M = (int**) malloc(4* sizeof(int*));

    for (int i = 0;i<4;i++)
    {
        M[i]=(int*)malloc(4*sizeof(int));
    }

    for(int k = 0 ; k<4 ; k++)
    {
        for(int l=0; l<4; l++)
        {
            M[k][l] = -5;
        }
    }
    //L'utilisateur saisi manuellement chaque grille qu'il veut retirer
    do
    {

        char colonne = 'z';
        int ligne = -1;
        int i;
        int j;

        print_map_4x4(M);
        do {
            printf("Entrez une case a remplir (exemple A1,B2,C3...):\n");
            scanf(" %c%d", &colonne,&ligne);

        } while ( ( (colonne > 'D' )||( colonne < 'A') )||( (ligne > 4 )||( ligne < 1) ) );


        switch (colonne) {
            case 'A':
                j = 0;
                break;
            case 'B':
                j = 1;
                break;
            case 'C':
                j = 2;
                break;
            case 'D':
                j = 3;
                break;
        }

        switch (ligne) {
            case 1:
                i = 0;
                break;
            case 2:
                i = 1;
                break;
            case 3:
                i = 2;
                break;
            case 4:
                i = 3;
                break;
        }
        //Si la case souhaitée n'est pas déjà masque elle prends la valeur -1
        if (M[i][j] != -7)
        {
            M[i][j] = -7;
            nombre--;
        }
        else
        {
            color(14, 0);
            printf("Cette case est deja masque! \n");
            color(15, 0);
        }

    } while (nombre > 0);

    //On affiche sa grille au joueur
    print_map_4x4(M);

    printf("Voila votre grille est prete ! \n\n");
    for(int k = 0 ; k<4 ; k++)
    {
        for(int l=0; l<4; l++)
        {
            if (M[k][l] == -7)
            {
                M[k][l] = 1;
            }
            else
                M[k][l] = 0;

        }
    }
    sleep(5);

    return M;
}

//On créer une fonction qui resout automatiquement une grille 4x4
void resolution_4x4(int ** masque)
{
    int **solutions = NULL;
    int **grille = NULL;
    srand(time(NULL));
    solutions = map_valide_4_4(solutions);
    grille = grille_de_jeu(solutions, masque);

    //Dans une boucle for le robot se deplace de case en case
    printf("(TAZUKU): ");
    color(14,0);
    printf("Voici la grille que je dois resoudre: \n\n");
    color(15,0);
    print_map_4x4(grille);
    int fini = 0;

    int suite_2 = 0;
    do {
        color(15, 0);
        printf("Saisissez 1 pour commencer\n");
        scanf("%d", &suite_2);
    } while (suite_2 != 1);
    do
    {
        int i = 0;
        int j = 0;
        do
        {


            i = rand() % 4;
            j = rand() % 4;

        } while (grille[i][j] != -1);
        char colonne = 'z';

        switch (j)
        {
            case 0:
                colonne = 'A';
                break;
            case 1:
                colonne = 'B';
                break;
            case 2:
                colonne = 'C';
                break;
            case 3:
                colonne = 'D';
                break;
        }

        //Si la case ou il est situé est masqué il y met la solution
        if (grille[i][j] == -1)
        {

            printf("(TAZUKU): ");
            color(14,0);
            printf("Je vais en %c%d \n\n", colonne, i + 1);
            color(15,0);
            grille[i][j] = -2;
            print_map_4x4(grille);
            int suite_1 = 0;
            do
            {
                color(15,0);
                printf("Saisissez 1 pour voir la solution\n");
                scanf("%d",&suite_1);
            }while(suite_1 != 1);
            int val = solutions[i][j];

            //Selon la nature de la solution le robot affiche un message
            int valide = coup_valide(val, grille, i, j);

            switch (valide)
            {
                case 1:
                    coup_forcer(grille,val,i,j,colonne);
                    break;

                case 0:
                    grille[i][j] = val;
                    printf("(TAZUKU): ");
                    color(14,0);
                    printf("Il n'y a aucune contrainte ici je peux mettre un (%d) en %c%d\n\n",val,colonne,i+1);
                    color(15,0);
                    print_map_4x4(grille);
                    break;

            }


        }
        int cpt_1 = 0;
        for (int k = 0; k < 4; k++)
        {
            for (int l = 0; l < 4; l++)
            {
                if (grille[k][l] == -1)
                {
                    cpt_1++;
                }
            }
        }
        if (cpt_1 == 0)
        {
            fini = 1;
        }
        else
        {
            int suite = 0;
            do {
                color(15, 0);
                printf("Saisissez 1 pour voir la prochaine etape ou 2 pour quitter\n");
                scanf("%d", &suite);
            } while ((suite != 1)&&(suite != 2));

            if (suite == 2)
            {
                free4x4(masque);
                free4x4(solutions);
                free4x4(grille);
                menu_robot_resoudre_grille();
            }
        }

    }while(fini == 0);

    sleep(2);
    color(14,0);
    printf("\n\nEt voila la grille est resolu, passons a une 8x8 ! \n\n");
    color(15,0);
    sleep(5);
    free4x4(masque);
    free4x4(solutions);
    free4x4(grille);
    menu_robot_resoudre_grille();
}

void coup_forcer(int ** grille, int val , int ligne ,int colonne, char colonne_c)
{
    //On compte le nombre de 1 et de 0 et on determine dans quelle cas le robot a ete forcer de jouer 1 ou 0
    int cpt_0_lig = 0;
    int cpt_0_col = 0;
    int cpt_1_lig = 0;
    int cpt_1_col = 0;
    for (int k = 0; k < 4; k++)
    {
        if (grille[k][colonne] == 0)
        {
            cpt_0_lig++;
        }
    }
    for (int l = 0; l < 4; l++)
    {
        if (grille[ligne][l] == 0)
        {
            cpt_0_col++;
        }
    }
    for (int k = 0; k < 4; k++)
    {
        if (grille[k][colonne] == 1)
        {
            cpt_1_lig++;
        }
    }
    for (int l = 0; l < 4; l++)
    {
        if (grille[ligne][l] == 1)
        {
            cpt_1_col++;
        }
    }
    // Si il y a deux 0 sur la même ligne ou deux 0 sur la même colonne, le robot a été contraint de jouer 1
    if (val == 1)
    {
        grille[ligne][colonne] = val;
        if (cpt_0_col == 2) {
            printf("(TAZUKU): ");
            color(14,0);
            printf("Il y a deux (0) sur la ligne %d donc je mets un (1) en %c%d\n\n", ligne + 1,colonne_c,ligne+1);
            color(15,0);
        } else if (cpt_0_lig == 2) {
            printf("(TAZUKU): ");
            color(14,0);
            printf("Il y a deux (0) sur la colonne %c  donc je mets un (1) en %c%d\n\n", colonne_c,colonne_c,ligne + 1);
            color(15,0);
        }
        print_map_4x4(grille);
    }
        // Si il y a deux 1 sur la même ligne ou deux 1 sur la même colonne, le robot a été contraint de jouer 0
    else if (val == 0)
    {
        grille[ligne][colonne] = val;
        if (cpt_1_col == 2)
        {
            printf("(TAZUKU):");
            color(14,0);
            printf("Il y a deux (1) sur la ligne %d donc je mets un (0) en %c%d\n\n", ligne + 1,colonne_c,ligne +1);
            color(15,0);
        }
        else if (cpt_1_lig == 2)
        {
            printf("(TAZUKU):");
            color(14,0);
            printf("Il y a deux (1) sur la colonne %c  donc je mets un (0) en %c%d \n\n", colonne_c,colonne_c,ligne + 1);
            color(15,0);
        }
        print_map_4x4(grille);
    }
}

//On créer une fonction qui genere une grille de takuzu 4x4 valide aléatoirement en reprennant les étapes de map_valid_4_4
void generer4x4()
{

    int choix_1 = -1;
    do {
        printf("\n\n");
        printf("Que souhaitez-vous faire ?\n");
        printf("1 - Generer une grille 4x4 de Takuzu \n2 - Generer une grille 4x4 avec les Etapes de generation\n");
        scanf("%d",&choix_1);
    }while((choix_1 < 1)||(choix_1) > 2);

    switch (choix_1)
    {
        case 1:
            color(14,0);
            printf("\nVoici une grille de Takuzu valide de taille 4x4:\n\n");
            color(15,0);
            sleep(1);
            printf("  Selection en cours ");
            sleep(1);
            printf(" .");
            sleep(1);
            printf(" .");
            sleep(1);
            printf(" .");
            sleep(1);
            printf("\n\n");
            sleep(1);
            int ** M = map_valide_4_4(masque_alea());
            print_map_4x4(M);
            free4x4(M);
            break;

        case 2: {
            int suite = 0;
            color(14, 0);
            printf(" - On souhaite generer une grille 4x4 de Takuzu valide \n\n");
            color(15, 0);
            do {
                printf("Saisissez 1 pour voir la prochaine etape\n");
                scanf("%d", &suite);
            } while (suite != 1);

            color(14, 0);
            printf(" - Pour cela, TAZUKU choisi un nombre aleatoire entre 1 et 15\n");
            printf("   Les nombres entre 1 et 15 sont composes de 4 chiffres en binaires.\n   Il formeront donc une ligne de la grille compose de 1 et de 0\n\n");

            int val;
            srand(time(NULL));
            do {
                val = rand() % 16;

            } while ((val != 3) && (val != 5) && (val != 6) && (val != 9) && (val != 10) && (val != 12));
            do {
                color(15, 0);
                printf("Saisissez 1 pour voir la prochaine etape\n");
                scanf("%d", &suite);
            } while (suite != 1);
            color(14, 0);
            printf(" - On choisi ce nombre pour qu'il soit compose de deux 1 et deux 0 en binaire\n\n");

            sleep(3);
            color(15, 0);
            printf("  Selection en cours ");
            sleep(1);
            printf(" .");
            sleep(1);
            printf(" .");
            sleep(1);
            printf(" .");
            sleep(1);
            color(14, 0);
            printf("\n\n - Le nombre choisi ici est %d soit ", val);

            int *T = binary_conversion(val);

            for (int i = 0; i < 4; i++) {
                printf("%d ", T[i]);
            }
            printf(" en binaire \n");

            do {
                color(15, 0);
                printf("\nSaisissez 1 pour voir la prochaine etape\n");
                scanf("%d", &suite);
            } while (suite != 1);
            color(14, 0);
            printf(" - On choisi de meme 3 autres nombres tous differents:\n\n");

            sleep(3);
            color(15, 0);
            printf("  Selection en cours ");
            sleep(1);
            printf(" .");
            sleep(1);
            printf(" .");
            sleep(1);
            printf(" .");
            sleep(1);
            color(14, 0);
            printf("\n\n - Les nombres choisis sont: \n");

            int inv = inverse_ligne(T);
            int *T2 = binary_conversion(inv);
            int val2;

            do {
                val2 = rand() % 16;

            } while ((val2 != 3) && (val2 != 5) && (val2 != 6) && (val2 != 9) && (val2 != 10) && (val2 != 12));

            while ((val == val2) || (val2 == inv)) {

                do {
                    val2 = rand() % 16;

                } while ((val2 != 3) && (val2 != 5) && (val2 != 6) && (val2 != 9) && (val2 != 10) && (val2 != 12));


            }
            int *T3 = binary_conversion(val2);
            int inv2 = inverse_ligne(T3);
            int *T4 = binary_conversion(inv2);
            printf(" - %d soit ", inv);
            for (int i = 0; i < 4; i++) {
                printf("%d ", T2[i]);
            }
            printf("en binaire \n");
            printf(" - %d soit ", val2);
            for (int i = 0; i < 4; i++) {
                printf("%d ", T3[i]);
            }
            printf("en binaire \n");
            printf(" - %d soit ", inv2);
            for (int i = 0; i < 4; i++) {
                printf("%d ", T4[i]);
            }
            printf("en binaire \n\n");
            do {
                color(15, 0);
                printf("Saisissez 1 pour voir la prochaine etape\n");
                scanf("%d", &suite);
            } while (suite != 1);
            color(14, 0);
            printf("Et voila en transferant les nombres binaires dans une matrice on obtient une grille takuzu valide\n\n");
            color(15, 0);
            sleep(5);
            int **M = (int **) malloc(4 * sizeof(int *));
            for (int i = 0; i < 4; i++) {
                M[i] = (int *) malloc(4 * sizeof(int));
            }
            M[0] = T;
            M[1] = T2;
            M[2] = T3;
            M[3] = T4;
            print_map_4x4(M);

            free4x4(M);
            break;
        }
    }

    int choix = -1;
    do {
        printf("1 - Generer une nouvelle grille 4x4\n2 - Retour au menu principale\nSaisir le numero de votre choix: \n");
        scanf("%d",&choix);
    }while((choix < 1)||(choix > 2));

    switch (choix)
    {
        case 1:
            generer4x4();
        case 2:
            menu();
    }
}

//On créer une fonction qui libère l'espace occupé par les matrices 4x4 utilisée
void free4x4(int ** map)
{
    for(int i = 0; i < 4; i++)
    {
        free(map[i]);
    }
    free(map);
    map = NULL;
}
