

#ifndef PROJET_TAKUZU_H
#define PROJET_TAKUZU_H
#endif //PROJET_TAKUZU_H


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <windows.h>



// fonctions du main.c
void menu();
void menu_resoudre_grille();
void menu_robot_resoudre_grille();
void menu_resoudre_4x4();
void menu_robot_4x4();
void menu_resoudre_8x8();
void menu_robot_8x8();
void menu_generer();
void color(int couleurDuTexte,int couleurDeFond);



//fonctions de 4x4.c

int* binary_conversion(int val);
int inverse_ligne(int *tab );
int ** fill_map_4x4(int** map);
void print_map_4x4(int** map);
int ** map_valide_4_4(int ** map);
int ** creation_masque();
int** masque_alea();
int ** grille_de_jeu(int** map, int ** masque);
void jouer_4x4(int ** masque);
int correct(int ** grille, int val,int ligne, int colonne);
int incorrect(int ** grille, int val,int ligne, int colonne);
int bloquer(int** grille, int ligne, int colonne);
int coup_valide(int val,int ** grille,int ligne,int colonne);
void resolution_4x4(int ** maasque);
void coup_forcer(int ** grille, int val , int ligne ,int colonne, char colonne_c);
void generer4x4();
void free4x4(int ** map);



//fonctions de 8x8.c
int** map_valide_8x8();
int* binary_conversion8x8(int val);
int comparer_3_ligne(int ** grille, int ligne);
int comparer_colone8x8(int ** matrice);
int comparer_colone_2(int ** matrice);
void print_map8x8(int** map);
int ** alea_masque8x8();
int ** creation_masque8x8();
int** grille8x8(int ** solution, int ** masque);
void jouer_8x8(int ** masque);
int coup_valide_8x8(int val, int ** grille ,int ligne, int colonne);
int correct8x8(int ** grille, int val,int ligne, int colonne);
int correct_deux_daffile(int ** grille, int val,int ligne, int colonne);
int correct_deux_separer(int ** grille, int val, int ligne, int colonne);
int incorrect8x8(int ** grille, int val,int ligne, int colonne);
int deux_daffile_separer(int ** grille, int ligne, int colonne, int val);
int deux_daffile_ligne_col(int ** grille, int ligne, int colonne, int val);
int bloquer8x8(int** grille, int ligne, int colonne);
int bloquer_deux_daffile(int** grille, int ligne, int colonne, int val);
int bloquer_deux_separer(int** grille, int ligne, int colonne, int val);
void resolution_8x8(int ** masque);
void coup_forcer8x8(int ** grille, int val , int ligne ,int colonne, char colonne_c);
void generer8x8();
void free8x8(int ** map);