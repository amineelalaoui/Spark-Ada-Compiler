#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"

#define Max_NBRE 20
#define TAILLE_TAB_SYMBOLE 50
#define debugSEM 1


typedef enum{TCONST = 1, TVAR = 2, TPROC = 3, TFUNC = 4, TPACK = 5, TBOTH = 6} NSYM; // nature des idfs (variable, constante)
//TBOTH : pour var et const

typedef enum{
    var_void,
    var_integer,
    var_float,
    var_boolean,
    var_string,
    var_char
} TSYM; // le type des idfs

typedef union{
    float num_val; // Float ,double, int ,boolean,ay haja fiha arkam
    char *string_value;
}Var_value;

typedef struct{
    char NOM[20];
    NSYM NIDF;
    TSYM TIDF;
    Var_value var_val;
    int ADRESSE;
}T_TAB_IDF;

T_TAB_IDF TAB_IDFS[TAILLE_TAB_SYMBOLE];

extern int OFFSET; //OFFSET
extern int OFFSET_VARIABE; //OFFSET

typedef enum{CST_ON, CST_OFF}testCST;

extern void insertIDFS(NSYM nsym);
extern int verifIDexist(NSYM nsym, char * NOM);
extern void showTS();
extern TSYM VariableType();
extern char * getNature(NSYM nsym);

FILE *outFile;
