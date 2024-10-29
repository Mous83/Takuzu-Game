//
// Created by edema on 22/04/2022.
//
#include "takuzu.h"

// On créer un fonction qui permet d'afficher une grille de jeu dans le cas d'une 8x8
void print_map8x8(int** map)
{
    printf("          %c",'A');
    for (int j=0; j<8-1;j++)
    {
        printf("         %c",'B'+j);
    }

    printf("\n");

    printf("     ................................................................................. \n");
    for(int i=0; i<8;i++)
    {
        printf(" %d   :",i+1);
        for(int j=0;j<8;j++)
        {

            if ((map[i][j] != -1)&&(map[i][j] != -5)&&(map[i][j] != -2)&&(map[i][j] != -7))
            {
                printf("    %d    :", map[i][j]);
            }
                //Si la valeur de la case est -1 cela signifie que la case est masqué pour le joueur on affiche alors un vide à cet emplacement
            else if (map[i][j] == -1)
            {
                printf("         :");
            }
                //Si la valeur de la case est -5 cela signifie que le joueur est bloqué à cette emplacement, la case est donc barrer
            else if (map[i][j] == -5)
            {
                color(4,0);
                printf("    x    ");
                color(15,0);
                printf(":");
            }
                //Si la valeur de la case est -2 cela signifie que la case est neutre pour le joueur on affiche alors une croix à cet emplacement
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
        printf("     :.........:.........:.........:.........:.........:.........:.........:.........: \n");

    }
    printf("\n");

    return;
}

//On créer une fonction qui génère une grille de takuzu valide de taille 8x8
int** map_valide_8x8()
{
    int **map = (int **) malloc(8 * sizeof(int *));

    for (int i = 0; i < 8; i++)
    {
        map[i] = (int *) malloc(8 * sizeof(int));
    }
    for (int i = 0; i<8;i++ )
    {
        for (int j = 0; j < 8; j++)
        {
            map[i][j] = -1;
        }
    }

    int tab[33] =  {43, 45, 51, 53, 54, 75, 77, 83, 85, 86, 89, 90, 101, 102, 105, 106, 108, 147, 149, 150,
                    153, 154, 165, 166, 169, 170, 172, 178, 180, 202, 204, 210, 212};


    int ligne = 0;
    int status = 0;
    int fini = 0;

    srand(time(NULL));

    do
    {
        int val = tab[rand()%33];

        map[ligne] = binary_conversion8x8(val);


        if (ligne >= 2)
        {
            while(comparer_3_ligne(map,ligne) == 0)
            {
                val = tab[rand()%33];
                map[ligne] = binary_conversion8x8(val);
            }

            status++;
            ligne ++;
        }
        else if (ligne < 2)
        {
            status++;
            ligne++;
        }
        if(status == 8)
        {
            int colonne = comparer_colone8x8(map);
            int colonne_2 = comparer_colone_2(map);

            if ((colonne == 1)&&(colonne_2 == 1))
            {
                fini = 1;
            }
            else
            {
                status = 0;
                ligne = 0;
            }

        }

    }while((status < 8)&&(fini == 0));

    return map;
}

//On créer une fonction qui génère un masque automatique
int ** alea_masque8x8()
{
    int ** masque = (int**) malloc(8*sizeof(int*));

    for(int i = 0;i<8;i++)
    {
        masque[i]=(int*)malloc(8*sizeof(int));
    }

    // On choisi aléatoirement de remplir les cases de 1 ou 0
    srand(time(NULL));

    for(int i=0;i<8;i++)
    {
        for(int j = 0; j < 8; j++)
        {
            int aleatoire = rand() % 2;
            masque[i][j] = aleatoire;
        }
    }

    return masque;
}

//On créer une fonction qui permet à l'utilisateur de générer un masque
int ** creation_masque8x8()
{

    //On demande à l'utlisateur de saisir le nombre d'éléments à masquer selon le niveau de difficulté souhaiter
    printf("CREER VOTRE GRILLE : \n\n\n");
    int nombre;
    printf("Saisir le nombre d'elements que vous souhaitez cacher (plus il y en a, plus le jeu est difficile) \n");
    do
    {
        printf("entre 1 et 63 \n");
        scanf("%d", &nombre);
    }
    while ((nombre > 63)||(nombre < 1));

    int ** M;
    M = (int**) malloc(8* sizeof(int*));

    for (int i = 0;i<8;i++)
    {
        M[i]=(int*)malloc(8*sizeof(int));
    }

    for(int k = 0 ; k<8 ; k++)
    {
        for(int l=0; l<8; l++)
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

        print_map8x8(M);
        do {
            printf("Entrez une case a remplir (exemple A1,B2,C3...):\n");
            scanf(" %c%d", &colonne,&ligne);

        } while ( ( (colonne > 'H' )||( colonne < 'A') )||( (ligne > 8 )||( ligne < 1) ) );


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
            case 'E':
                j = 4;
                break;
            case 'F':
                j = 5;
                break;
            case 'G':
                j = 6;
                break;
            case 'H':
                j = 7;
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
            case 5:
                i = 4;
                break;
            case 6:
                i = 5;
                break;
            case 7:
                i = 6;
                break;
            case 8:
                i = 7;
                break;
        }
        //Si la case souhaitée n'est pas déjà masque elle prends la valeur -1
        if (M[i][j] != -7)
        {
            M[i][j] = -7;
            nombre--;
        }
        else if (M[i][j] == -7)
        {
            color(14, 0);
            printf("Cette case est deja masque! \n");
            color(15, 0);
            sleep(1);
        }
    } while (nombre > 0);

    //On affiche sa grille au joueur
    print_map8x8(M);
    printf("Voila votre grille est prete ! \n\n");

    for(int k = 0 ; k<8 ; k++)
    {
        for(int l=0; l<8; l++)
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

//On créer une fonction qui gènere la grille de jeu 8x8 grace au masquq et la grille valide
int** grille8x8(int ** solution, int ** masque)
{
    int ** grille = (int**) malloc(8* sizeof(int*));

    for (int i = 0;i<8;i++)
    {
        grille[i]=(int*)malloc(8*sizeof(int));
    }
    // On remplit notre grille de jeu par les valeurs de la grille solutions
    for(int k = 0 ; k<8 ; k++)
    {
        for(int l=0; l<8; l++)
        {
            grille[k][l] = solution[k][l];
        }
    }
    //On remplit par -1 les cases pour lesquelles masque[i][j] = 1
    for(int k = 0 ; k<8 ; k++)
    {
        for(int l=0; l<8; l++)
        {
            if(masque[k][l] == 1)
            {
                grille[k][l] = -1;
            }
        }
    }


    return grille;

}

//On créer la fonction qui permet à l'utilisateur de jouer au takuzu sur une grillle de taille 8x8
void jouer_8x8(int ** masque)
{

    //On créer une grille de jeu
    int ** solution = NULL;
    int ** grille = NULL;
    solution = map_valide_8x8();
    grille = grille8x8(solution,masque);

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
            print_map8x8(grille);

            do {
                printf("Entrez une case a remplir (exemple A1,B2,C3...):\n");
                scanf(" %c%d", &colonne,&ligne);

            } while ( ( (colonne > 'H' )||( colonne < 'A') )||( (ligne > 8 )||( ligne < 1) ) );


            switch (colonne)
            {
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
                case 'E':
                    j = 4;
                    break;
                case 'F':
                    j = 5;
                    break;
                case 'G':
                    j = 6;
                    break;
                case 'H':
                    j = 7;
                    break;
            }

            switch (ligne)
            {
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
                case 5:
                    i = 4;
                    break;
                case 6:
                    i = 5;
                    break;
                case 7:
                    i = 6;
                    break;
                case 8:
                    i = 7;
                    break;
            }

            //Si la grille n'est pas masqué on ne peut rien faire
            if(grille[i][j] != -1)
            {
                color(14,0);
                printf("Vous ne pouvez pas modifier cette case \n\n");
                color(15,0);
            }

        }while(grille[i][j] != -1);

        //Si la grille est masqué on demande au joueur de saisir 1 ou 0
        int val = -1;
        do {
            printf("Entrez 0 ou 1 en %c%d ou 2 pour abandonner :\n",colonne,ligne);
            scanf("%d",&val);

        }while((val < 0)||(val > 2));

        if (val == 2)
        {
            color(4,0);
            printf("Quel dommage tu as abandonne...\n");
            sleep(3);
            color(15,0);
            free8x8(solution);
            free8x8(masque);
            free8x8(grille);
            menu_resoudre_grille();
        }

        sleep(1);
        //On verifie la validité du coup du joueur
        int valide = coup_valide_8x8(val,grille,i,j);

        switch (valide)
        {


            //On renvoie un message selon le type de coup jouer
            case 0:
            {
                color(14, 0);
                printf("\n     Coup valide !\n");
                color(15, 0);
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
            case 2:
                color(10, 0);
                printf("\n     Coup correct ! \n");
                color(15, 0);
                grille[i][j] = val;
                sleep(1);
                break;

            case 3:

                color(10, 0);
                printf("\n     Coup correct ! \n");
                color(15, 0);
                grille[i][j] = val;
                sleep(1);
                break;

            case -1:
            {
                color(4, 0);
                printf("\n     Coup incorrect ... ! \n");
                color(15, 0);
                vie--;
                sleep(1);
                break;
            }
            case -2:
            {

                color(4, 0);
                printf("\n     Coup incorrect ... ! \n");
                color(15, 0);
                vie--;
                sleep(1);
                break;
            }
            case -3:
                color(4, 0);
                printf("\n     Coup incorrect ... ! \n");
                color(15, 0);
                vie--;
                sleep(1);
                break;

            case -4:
            {
                color(4, 0);
                printf("\n     Tu es bloque ... ! \n");
                color(15, 0);
                sleep(1);
                grille[i][j] = -5;
                print_map8x8(grille);
                sleep(3);
                vie = 0;
                break;
            }
            case -5:
            {
                color(4, 0);
                printf("\n     Tu es bloque ... ! \n");
                color(15, 0);
                sleep(1);
                grille[i][j] = -5;
                print_map8x8(grille);
                sleep(3);
                vie = 0;
                break;
            }
            case -6:
            {
                color(4, 0);
                printf("\n     Tu es bloque ... ! \n");
                color(15, 0);
                sleep(2);
                grille[i][j] = -5;
                print_map8x8(grille);
                sleep(3);
                vie = 0;
                break;
            }

        }

        int cpt_1 = 0;
        int cpt_0 = 0;
        //Apres chaque coup on verifie en comptant le nombre de -1 si la grille est rempli
        int cpt_m1 = 0;
        for( int k = 0; k<8 ; k++)
        {
            for (int l = 0 ; l<8 ; l++)
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
        if ((cpt_m1 == 0)&&(cpt_0 == cpt_1)&&(cpt_0 == 32))
        {
            verif = 1;
        }


    }while(verif == 0 );
    printf("\n");
    //Selon s'il a gagner ou perdu on affiche un message a l'utilisateur
    if (verif == 1)
    {
        print_map8x8(grille);
        color(10,0);
        printf("\nFelications tu as gagne ! Tu es beaucoup trop fort passes au Sudoku !\n");
        color(15,0);
    }
    else if(verif == -1)
    {
        color(4,0);
        printf("\n Dommage, tu as perdu ! Retente ta chance ... !");
        color(15,0);
    }
    sleep(3);

    free8x8(solution);
    free8x8(masque);
    free8x8(grille);
    menu_resoudre_grille();

}

//On créer une fonction qui détermine la validité du coup joué
int coup_valide_8x8(int val, int ** grille,int ligne, int colonne)
{
    int coup = -10;

    //On appelle 9 autres fonctions et selon ce qu'elles renvoient on determine la validite du coup
    int incorrec_3= incorrect8x8(grille,val,ligne,colonne);
    int incorrec_2 = deux_daffile_ligne_col(grille,ligne,colonne,val);
    int incorrec_1 = deux_daffile_separer(grille,ligne,colonne,val);
    int correct_3 = correct8x8( grille ,val ,ligne ,colonne);
    int correct_2 = correct_deux_separer(grille,val,ligne,colonne);
    int correct_1 = correct_deux_daffile(grille,val,ligne,colonne);
    int bloque = bloquer8x8(grille,ligne,colonne);
    int bloque_2 = bloquer_deux_daffile(grille,ligne,colonne,val);
    int bloque_3 = bloquer_deux_separer(grille,ligne,colonne,val);


    if (bloque == 1)
    {
        coup = - 4;
    }
    else if(bloque_2 == 1)
    {
        coup = -5;
    }
    else if (bloque_3 == 1)
    {
        coup = -6;
    }
    else if (incorrec_1 == 1)
    {
        coup = -1;

    }
    else if (incorrec_2 == 1)
    {
        coup = -2;

    }
    else if (incorrec_3 == 1)
    {
        coup = -3;
    }
    else if (correct_1 == 1)
    {
        coup = 1;

    }
    else if (correct_3 == 1)
    {
        coup = 3;
    }
    else if (correct_2 == 1)
    {
        coup = 2;
    }
    else
        coup = 0;


    return coup;

}

//Les fonctions qui regardent si le coup est est correct

//Si le coup est correct car il ya deja 4 zero ou 4 un sur la ligne ou la colonne
int correct8x8(int ** grille, int val,int ligne, int colonne)
{
    //Pour determiner si un coup est correct:
    int cpt0_lig = 0;
    int cpt1_lig = 0 ;
    int cpt0_col = 0;
    int cpt1_col = 0;
    int verif = 0;
    //On compte le nombre de 1 et de 0 sur la ligne et sur la colonne sur laquelle il joue
    for(int i = 0;i<8;i++)
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

    for(int j = 0;j<8;j++)
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

    //Si le nombre de 0 sur la ligne ou la colonne est déjà égale à 4 et le nombre de 1 < 4 alors il ne peut que jouer 1


    if ((val == 1))
    {
        if((cpt1_lig <= 3) && (cpt0_lig == 4))
        {

            verif = 1;
        }
        else if((cpt1_col <= 3) && (cpt0_col == 4))
        {
            verif = 1;
        }
    }
    //Si le nombre de 1 sur la ligne ou la colonne est déjà égale à 4 el le nombre de 0 < 4 alors il ne peut que jouer 0
    if ((val == 0))
    {
        if((cpt0_lig <= 3) && (cpt1_lig == 4))
        {
            verif = 1;
        }
        else if((cpt0_col <= 3) && (cpt1_col == 4))
        {
            verif = 1;
        }
    }
    return verif;

}

// Si le coup est correct car il y a deux valeur qui se suivent
int correct_deux_daffile(int ** grille, int val,int ligne, int colonne)
{

    int verif = 0;


    if( val == 1)
    {
        if(deux_daffile_ligne_col(grille,ligne,colonne,0) == 1)
        {
            verif = 1;
        }

    }
    if(val == 0)
    {
        if(deux_daffile_ligne_col(grille,ligne,colonne,1) == 1)
        {
            verif = 1;
        }
    }


    return verif;
}

// Si le coup est valide car la case est encadrée par la valeur inverse
int correct_deux_separer(int ** grille, int val, int ligne, int colonne)
{
    int verif = 0;

    if(val == 1)
    {
        if (deux_daffile_separer(grille,ligne,colonne,0) == 1)
        {
            verif = 1;
        }
    }
    if (val == 0)
    {
        if(deux_daffile_separer(grille,ligne,colonne,1) == 1)
        {
            verif = 1;
        }
    }
    return verif;
}

//Les fonctions qui regardent si le coup est est correct

//Si le coup est incorrect car il ya deja 4 zero ou 4 un sur la ligne ou la colonne
int incorrect8x8(int ** grille, int val,int ligne, int colonne) {
    int verif = 0;


    int cpt0_lig = 0;
    int cpt1_lig = 0;
    int cpt0_col = 0;
    int cpt1_col = 0;

    //De meme que pour les coup correct on compte les nombres de 0 et 1 sur la lignes et la colonnes jouées
    for (int i = 0; i < 8; i++) {
        if (grille[ligne][i] == 0) {
            cpt0_lig++;
        } else if (grille[ligne][i] == 1) {
            cpt1_lig++;
        }
    }

    for (int j = 0; j < 8; j++) {
        if (grille[j][colonne] == 0) {
            cpt0_col++;
        } else if (grille[j][colonne] == 1) {
            cpt1_col++;
        }
    }

    // Si le joueur joue 1 alors qu'il y en a deja quatre sur la ligne ou la colonne , le coup est incorrect
    if (val == 1) {
        if ((cpt1_lig >= 4) || (cpt1_col >= 4)) {
            verif = 1;

        }

    }
        //Si le joueur joue 0 alors qu'il y en a deja quatre sur la ligne ou la colonne , le coup est incorrect
    else if (val == 0) {
        if ((cpt0_lig >= 4) || (cpt0_col >= 4)) {
            verif = 1;
        }
    }
    return verif;



    return verif;
}

// Si le coup est incorrect car il y a deux valeur qui se suivent
int deux_daffile_ligne_col(int ** grille, int ligne, int colonne, int val)
{
    //On copie notre matrice au centre d'une matrice 12x12
    int** mat_12 = (int**)malloc(12*sizeof(int*));
    for(int i = 0; i< 12; i++)
    {
        mat_12[i] = (int*) malloc(12*sizeof(int));
    }
    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            if (((i < 2)||(j < 2))||((i > 9 )||(j>9)))
            {
                mat_12[i][j] = 0;
            }
            else
            if(grille[i-2][j-2] == 0)
            {
                //On remplace les 0 de notre de matrice par des 3
                mat_12[i][j] = 3;
            }
            else if(grille[i-2][j-2] == 1)
            {
                mat_12[i][j] =grille[i-2][j-2] ;
            }
        }
    }

    int verif = 0;

    int i = ligne + 2;
    int j = colonne + 2;
    int somme_gauche = 0;
    int somme_droite = 0;
    int somme_bas = 0;
    int somme_haut = 0;

    //On somme les valeurs encadrant notre case
    somme_droite = mat_12[i][j+1] + mat_12[i][j+2];
    somme_gauche = mat_12[i][j-1] + mat_12[i][j-2];
    somme_haut = mat_12[i-1][j] + mat_12[i-2][j];
    somme_bas = mat_12[i+1][j] + mat_12[i+2][j];

    if (val == 1)
    {
        //Si la valeur joué est 1 la somme des valeurs encadrantes doit être différente de 2
        if ((somme_gauche == 2) || (somme_droite == 2) || (somme_haut == 2) || (somme_bas == 2))
        {
            verif = 1;
        }

    }
    else if(val == 0 )
    {
        //Si la valeur joué est 0 la somme des valeurs encadrantes doit être différente de 6 ( car 0 est devenu 3 )
        if ((somme_gauche == 6)||(somme_droite == 6)||(somme_haut == 6)||(somme_bas == 6))
        {
            verif = 1;
        }
    }

    return verif;

}

// Si le coup est incorrect car la case est encadrée par la valeur inverse
int deux_daffile_separer(int ** grille, int ligne, int colonne, int val)
{
    //On copie notre grille de jeu au centre d'une matrice 12x12
    int** mat_12 = (int**)malloc(12*sizeof(int*));
    for(int i = 0; i< 12; i++)
    {
        mat_12[i] = (int*) malloc(12*sizeof(int));
    }
    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 12; ++j)
        {
            if (((i < 2)||(j < 2))||((i > 9 )||(j>9)))
            {
                mat_12[i][j] = 0;
            }
            else
            if(grille[i-2][j-2] == 0)
            {
                //On remplace les 0 par des 3
                mat_12[i][j] = 3;
            }
            else if(grille[i-2][j-2] == 1)
            {
                mat_12[i][j] =grille[i-2][j-2] ;
            }
        }
    }

    int verif = 0;

    int i = ligne + 2;
    int j = colonne + 2;
    int somme_gauche_droite = 0;
    int somme_haut_bas = 0;

    //On somme les valeurs juste à  gauxhe et juste à droite de la case joué et les valeurs juste au-dessus et juste en-dessous de la case
    somme_gauche_droite = mat_12[i][j-1] + mat_12[i][j+1];
    somme_haut_bas = mat_12[i+1][j] + mat_12[i-1][j];

    if (val == 1)
    {
        //On verifie que la somme est différent de 2 si le coup joué est 1
        if ((somme_gauche_droite == 2) || (somme_haut_bas == 2))
        {
            verif = 1;
        }
    }
    else if (val ==0)
    {
        //On verifie que la somme est différent de 6 si le coup joué est 0
        if ((somme_gauche_droite == 6) || (somme_haut_bas == 6))
        {
            verif = 1;
        }
    }

    return verif;
}

//Les fonctions qui détermine si le joueur est bloqué

//Si il est bloqué car il y a deja  4 zero et 4 un sur les lignes et colonnes de la case joué
int bloquer8x8(int** grille, int ligne, int colonne)
{
    int cpt0_lig = 0;
    int cpt1_lig = 0 ;
    int cpt0_col = 0;
    int cpt1_col = 0;
    int verif = -1;
//On recompte également le nombre de 1 et de 0
    for(int i = 0;i<8;i++)
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

    for(int j = 0;j<8;j++)
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
    //Si il y a quatre 1 sur colonne joué et quatre 0 sur la ligne joué ou inversement le joueur se retrouve bloqué, il a directement perdu

    if(((cpt1_col >= 4)&&(cpt0_lig >= 4))||((cpt0_col >= 4)&&(cpt1_lig >= 4)))
    {
        verif = 1;
    }
    return verif;
}

//Si il est bloqué car la case joué est separer de 1 et de 0
int bloquer_deux_separer(int** grille, int ligne, int colonne, int val)
{
    int verif = 0;
    int incorrect_1 = deux_daffile_separer(grille,ligne,colonne,1);
    int incorrect_2 = deux_daffile_separer(grille,ligne,colonne,0);


    if ((incorrect_1 == 1)&&(incorrect_2 == 1))
    {
        verif = 1;
    }

    return  verif;
}

//Si il est bloqué car le case est suivi de deux zero et de deux un
int bloquer_deux_daffile(int** grille, int ligne, int colonne, int val)
{
    int verif = 0;

    int incorrect_1 = deux_daffile_ligne_col(grille,ligne,colonne,1);
    int incorrect_2 = deux_daffile_ligne_col(grille,ligne,colonne,0);

    if((incorrect_2 == 1)&&(incorrect_1 == 1))
    {
        verif = 1;
    }

    return verif;
}

//On créer une fonction qui résout une grille de jeu automatique
void resolution_8x8(int ** masque)
{
    int **solutions = NULL;
    int **grille = NULL;
    srand(time(NULL));
    solutions = map_valide_8x8();
    grille = grille8x8(solutions, masque);

//Dans une boucle for le robot se deplace de case en case
    printf("(TAZUKU): ");
    color(14,0);
    printf("Voici la grille que je dois resoudre: \n\n");
    color(15,0);
    print_map8x8(grille);
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

            i = rand() % 8;
            j = rand() % 8;

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
            case 4:
                colonne = 'E';
                break;
            case 5:
                colonne = 'F';
                break;
            case 6:
                colonne = 'G';
                break;
            case 7:
                colonne = 'H';
                break;
        }

        //Si la case où il est situé est masqué il y met la solution
        if (grille[i][j] == -1)
        {

            printf("(TAZUKU): ");
            color(14,0);
            printf("Je vais en %c%d \n\n", colonne, i + 1);
            color(15,0);
            grille[i][j] = -2;
            print_map8x8(grille);

            int suite_1 = 0;
            do {
                color(15, 0);
                printf("Saisissez 1 pour voir la solution\n");
                scanf("%d", &suite_1);
            } while (suite_1 != 1);

            int val = solutions[i][j];

            int valide = coup_valide_8x8(val, grille, i, j);

            int inv;

            if(val == 1)
            {
                inv = 0;
            }
            else if(val == 0)
            {
                inv = 1;
            }

            //Selon la nature de la solution le robot affiche un message
            switch (valide)
            {
                case 1:
                {
                    grille[i][j] = val;
                    printf("(TAZUKU): ");
                    color(14, 0);
                    printf("Il y a deux (%d) de suite, je dois mettre un (%d) en %c%d !\n\n",inv,val, colonne, i + 1);
                    color(15, 0);
                    print_map8x8(grille);

                    break;
                }

                case 0:
                    grille[i][j] = val;
                    printf("(TAZUKU): ");
                    color(14,0);
                    printf("Il n'y a aucune contrainte ici je peux mettre un (%d) en %c%d !\n\n",val,colonne,i+1);
                    color(15,0);
                    print_map8x8(grille);

                    break;

                case 2:

                    grille[i][j] = val;
                    printf("(TAZUKU): ");
                    color(14,0);
                    printf("La case %c%d est entouree de deux (%d) je dois mettre un (%d) ! \n\n",colonne,i+1,inv,val);
                    color(15,0);
                    print_map8x8(grille);
                    break;

                case 3:
                    coup_forcer8x8(grille,val,i,j,colonne);
                    break;
            }


        }

        int cpt_1 = 0;
        for (int k = 0; k < 8; k++)
        {
            for( int l = 0; l < 8; l++)
            {
                if (grille[k][l] == -1)
                {
                    cpt_1++;
                }
            }
        }
        if( cpt_1 == 0)
        {
           fini = 1;
        }
        else
        {
            int suite = 0;
            do {
                color(15, 0);
                printf("Saisissez 1 pour voir la prochaine etape ou 2 pour quitter \n");
                scanf("%d", &suite);
            } while ((suite != 1)&&(suite != 2));
            if (suite == 2)
            {
                free8x8(masque);
                free8x8(grille);
                free8x8(solutions);
                menu_robot_resoudre_grille();
            }

        }

    }while(fini == 0);
    color(14,0);
    printf("\n\nEt voila la grille est resolu ! \n\n",1);
    color(15,0);
    sleep(3);
    free8x8(masque);
    free8x8(solutions);
    free8x8(grille);
    menu_robot_resoudre_grille();
}

void coup_forcer8x8(int ** grille, int val , int ligne ,int colonne, char colonne_c)
{
    //On compte le nombre de 1 et de 0 et on determine dans quelle cas le robot a ete forcer de jouer 1 ou 0
    int cpt_0_lig = 0;
    int cpt_0_col = 0;
    int cpt_1_lig = 0;
    int cpt_1_col = 0;
    for (int k = 0; k < 8; k++)
    {
        if (grille[k][colonne] == 0)
        {
            cpt_0_lig++;
        }
    }
    for (int l = 0; l < 8; l++)
    {
        if (grille[ligne][l] == 0)
        {
            cpt_0_col++;
        }
    }
    for (int k = 0; k < 8; k++)
    {
        if (grille[k][colonne] == 1)
        {
            cpt_1_lig++;
        }
    }
    for (int l = 0; l < 8; l++)
    {
        if (grille[ligne][l] == 1)
        {
            cpt_1_col++;
        }
    }
    // Si il y a quatre 0 sur la même ligne ou quatre 0 sur la même colonne, le robot a été contraint de jouer 1
    if (val == 1)
    {

        grille[ligne][colonne] = val;
        if (cpt_0_col == 4) {
            printf("(TAZUKU): ");
            color(14,0);
            printf("Il y a quatre (0) sur la ligne %d donc je mets un (1) en %c%d !\n\n", ligne + 1, colonne_c, ligne+1);
            color(15,0);
        } else if (cpt_0_lig == 4) {
            printf("(TAZUKU): ");
            color(14,0);
            printf("Il y a quatre (0) sur la colonne %c  donc je mets un (1) en %c%d !\n\n", colonne_c, colonne_c, ligne+1);
            color(15,0);
        }
        print_map8x8(grille);
    }
        // Si il y a quatre 1 sur la même ligne ou quatre 1 sur la même colonne, le robot a été contraint de jouer 0
    else if (val == 0)
    {
        grille[ligne][colonne] = val;

        if (cpt_1_col == 4)
        {
            printf("(TAZUKU): ");
            color(14,0);
            printf("Il y a quatre (1) sur la ligne %d donc je mets un (0) en %c%d !\n\n", ligne + 1,colonne_c,ligne + 1);
            color(15,0);
        }
        else if (cpt_1_lig == 4)
        {
            printf("(TAZUKU): ");
            color(14,0);
            printf("Il y a quatre (1) sur la colonne %c  donc je mets un (0) en %c%d !\n\n", colonne_c,colonne_c,ligne+1);
            color(15,0);
        }
        print_map8x8(grille);
    }
}

//On créer une fonction qui affiche une grille de jeu 8x8 valide
void generer8x8()
{
    color(14,0);
    printf("Voici une grille de Takuzu valide de taille 8x8:\n\n");
    color(15,0);
    sleep(1);
    color(15, 0);
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
    int ** M = map_valide_8x8();
    print_map8x8(M);
    int choix = -1;
    free8x8(M);
    do {
        printf("1 - Generer une nouvelle grille 8x8\n2 - Retour au menu principale\nSaisir le numero de votre choix: \n");
        scanf("%d",&choix);
    }while((choix < 1)||(choix > 2));

    switch (choix)
    {
        case 1:
            generer8x8();
            break;
        case 2:
            menu();
            break;
    }
}

//On créer une fonction qui libère l'espace occupé par les matrices 4x4 utilisée
void free8x8(int ** map)
{
    for(int i = 0; i < 8; i++)
    {
        free(map[i]);
    }
    free(map);
    map = NULL;
}

//On créer une fonction qui compare 3 lignes
int comparer_3_ligne(int ** map, int ligne)
{
    int verif = 1;
    for(int i = 0; i < 8; i++)
    {
       if((map[ligne][i]==map[ligne-1][i])&&(map[ligne][i] == map[ligne-2][i]))
       {
           verif = 0;
       }
    }
    return verif;
}

//On créer une fonction qui change une une valeurs en son nombre binaire
int* binary_conversion8x8(int val)
{
    int * tab = (int*) malloc(8*sizeof(int));

    for (int i=7 ; i >= 0; i--)
    {
        tab[i] = val%2;
        val = val/2;
    }


    return tab;
}

//On créer une fonction qui comparer les lignes d'une matrice deux à deux pour detecter si il y en a deux identiques
int comparer_colone_2(int ** matrice)
{
    int verif = 1;
    int somme=0;

    //On parcours la matrice deux fois
    for (int i=0;i<7;i++){


        for (int j=i+1;j<8;j++){

            for (int f=0;f<8;f++){

                //Si deux valeurs sont identiques ont les sommes
                if (matrice[f][i]==matrice[f][j])
                    somme++;

            }
            //Si la somme est égale à 8 la fonction est nulle
            if (somme==8)
                verif = 0;
            somme=0;
        }
    }
    return verif;
}

//On créer un fonction qui comparer une colone d'une matrice pour vérifier qu'il y ait bien uniquement 4 un et 4 zero
int comparer_colone8x8(int ** matrice)
{

    int verif = 1;

    //On parcours chaque colonne
    for (int j = 0 ; j < 8 ; j++)
    {

        int cpt_1 = 0;
        int cpt_0 = 0;

        for (int i = 0; i < 8; i++)
        {
            //On compte le nombre de 0 et de 1
            if (matrice[i][j] == 0)
            {
                cpt_0++;

            } else if (matrice[i][j] == 1)
            {
                cpt_1++;
            }
        }

        //Si l'un des compteur est supérieur à 4 le fonction est nulle
        if ((cpt_0 > 4) || (cpt_1 > 4))
        {
            verif = 0;
            return verif;
        }
    }


    return verif;
}

