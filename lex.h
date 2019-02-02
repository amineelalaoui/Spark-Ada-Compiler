#ifndef LEX_H_INCLUDED
#define LEX_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define true 1
#define false 0
#define Max_NBRE 20
/*
* DECLARATION DES CLASSES LEXICALES
*/
typedef enum {
// lexemes de ada 2012
ABORT_TOKEN, ABS_TOKEN, ABSTRACT_TOKEN,
ACCEPT_TOKEN, ACCESS_TOKEN, ALIASED_TOKEN,
ALL_TOKEN, AND_TOKEN, ARRAY_TOKEN, AT_TOKEN,
BEGIN_TOKEN, BODY_TOKEN, CASE_TOKEN, CONSTANT_TOKEN,
DECLARE_TOKEN, DELAY_TOKEN, DELTA_TOKEN, DIGITS_TOKEN,
DO_TOKEN, ELSE_TOKEN, ELSIF_TOKEN, END_TOKEN,
ENTRY_TOKEN, EXCEPTION_TOKEN, EXIT_TOKEN, FOR_TOKEN,
FUNCTION_TOKEN, GENERIC_TOKEN, GOTO_TOKEN,
IF_TOKEN, IN_TOKEN, INTERFACE_TOKEN, IS_TOKEN,
LIMITED_TOKEN, LOOP_TOKEN, MOD_TOKEN,
NEW_TOKEN, NOT_TOKEN, NULL_TOKEN, OF_TOKEN,
OR_TOKEN, OTHERS_TOKEN, OUT_TOKEN, OVERRIDING_TOKEN,
PACKAGE_TOKEN, PRAGMA_TOKEN, PRIVATE_TOKEN,
PROCEDURE_TOKEN, PROTECTED_TOKEN,RAISE_TOKEN, RANGE_TOKEN,
RECORD_TOKEN, REM_TOKEN, RENAMES_TOKEN,
REQUEUE_TOKEN, RETURN_TOKEN, REVERSE_TOKEN,
SELECT_TOKEN, SEPARATE_TOKEN, SOME_TOKEN,
SUBTYPE_TOKEN,
SYNCHRONIZED_TOKEN, TAGGED_TOKEN,
TASK_TOKEN, TERMINATE_TOKEN, THEN_TOKEN,
TYPE_TOKEN, UNTIL_TOKEN, USE_TOKEN,
WHEN_TOKEN, WHILE_TOKEN, WITH_TOKEN, XOR_TOKEN,
/////////////////////////////////////////
COM_TOKEN,

ID_TOKEN, NUM_TOKEN,ERREUR_TOKEN,
PV_TOKEN, PT_TOKEN, PLUS_TOKEN, MOINS_TOKEN, MULT_TOKEN,
DIV_TOKEN, VIR_TOKEN, AFF_TOKEN,EGAL_TOKEN, INF_TOKEN, INFEG_TOKEN,
SUP_TOKEN, SUPEG_TOKEN, DIFF_TOKEN, PO_TOKEN, PF_TOKEN,
FIN_TOKEN, DOUBLE_POINT_TOKEN, APP_TOKEN, DOUBLE_QUOTES_TOKEN
} CODE_LEX ;


typedef struct {
    CODE_LEX CODE;
    char NOM[20];
} Token;

typedef enum{
    TRUE,
    FALSE
} boolean;

static boolean follow_token = false;

static Token tabToken[] = {
    {ABORT_TOKEN ,"abort"},
    {ABS_TOKEN ,"abs"},
    {ABSTRACT_TOKEN ,"abstract"},
    {ACCEPT_TOKEN ,"accept"},
    {ACCESS_TOKEN ,"access"},
    {ALIASED_TOKEN ,"aliased"},
    {ALL_TOKEN ,"all"},
    {AND_TOKEN ,"and"},
    {ARRAY_TOKEN ,"array"},
    {AT_TOKEN ,"at"},
    {BEGIN_TOKEN ,"begin"},
    {BODY_TOKEN ,"body"},
    {CASE_TOKEN ,"case"},
    {CONSTANT_TOKEN ,"constant"},
    {DECLARE_TOKEN ,"declare"},
    {DELAY_TOKEN ,"delay"},
    {DELTA_TOKEN ,"delta"},
    {DIGITS_TOKEN ,"digits"},
    {DO_TOKEN ,"do"},
    {ELSE_TOKEN ,"else"},
    {ELSIF_TOKEN ,"elsif"},
    {END_TOKEN ,"end"},
    {ENTRY_TOKEN ,"entry"},
    {EXCEPTION_TOKEN ,"exception"},
    {EXIT_TOKEN ,"exit"},
    {FOR_TOKEN ,"for"},
    {FUNCTION_TOKEN ,"function"},
    {GENERIC_TOKEN ,"generic"},
    {GOTO_TOKEN ,"goto"},
    {IF_TOKEN ,"if"},
    {IN_TOKEN ,"in"},
    {INTERFACE_TOKEN ,"interface"},
    {IS_TOKEN ,"is"},
    {LIMITED_TOKEN ,"limited"},
    {LOOP_TOKEN ,"loop"},
    {MOD_TOKEN ,"mod"},
    {NEW_TOKEN ,"new"},
    {NOT_TOKEN ,"not"},
    {NULL_TOKEN ,"null"},
    {OF_TOKEN ,"of"},
    {OR_TOKEN ,"or"},
    {OTHERS_TOKEN ,"others"},
    {OUT_TOKEN ,"out"},
    {OVERRIDING_TOKEN ,"overriding"},
    {PACKAGE_TOKEN ,"package"},
    {PRAGMA_TOKEN ,"pragma"},
    {PRIVATE_TOKEN ,"private"},
    {PROCEDURE_TOKEN ,"procedure"},
    {PROTECTED_TOKEN, "protected"},
    {RAISE_TOKEN ,"raise"},
    {RANGE_TOKEN ,"range"},
    {RECORD_TOKEN ,"record"},
    {REM_TOKEN ,"rem"},
    {RENAMES_TOKEN ,"renames"},
    {REQUEUE_TOKEN ,"requeue"},
    {RETURN_TOKEN ,"return"},
    {REVERSE_TOKEN ,"reverse"},
    {SELECT_TOKEN ,"select"},
    {SEPARATE_TOKEN ,"separate"},
    {SOME_TOKEN ,"some"},
    {SUBTYPE_TOKEN ,"subtype"},
    {SYNCHRONIZED_TOKEN ,"synchronized"},
    {TAGGED_TOKEN ,"tagged"},
    {TASK_TOKEN ,"task"},
    {TERMINATE_TOKEN ,"terminate"},
    {THEN_TOKEN ,"then"},
    {TYPE_TOKEN ,"type"},
    {UNTIL_TOKEN ,"until"},
    {USE_TOKEN ,"use"},
    {WHEN_TOKEN ,"when"},
    {WHILE_TOKEN ,"while"},
    {WITH_TOKEN ,"with"},
    {XOR_TOKEN ,"xor"},


    //literals = ['&','(',')','*','+',',','-','.','/',':',';','<','=','>','|'] + ['\"','#']
    //les caractere speciaux
    {PV_TOKEN ,";"},
    {DOUBLE_POINT_TOKEN ,":"},
    {PT_TOKEN ,"."},
    {PLUS_TOKEN ,"+"},
    {MOINS_TOKEN ,"-"},
    {MULT_TOKEN ,"*"},
    {DIV_TOKEN ,"/"},
    {VIR_TOKEN ,","},
    {EGAL_TOKEN ,"="},
    {AFF_TOKEN ,":="},
    {INF_TOKEN ,"<"},
    {INFEG_TOKEN ,"<="},
    {SUP_TOKEN ,">"},
    {SUPEG_TOKEN ,">="},
    {DIFF_TOKEN ,"<>"},
    {PO_TOKEN ,"("},
    {PF_TOKEN ,")"},
    {APP_TOKEN ,"'"},
    {DOUBLE_QUOTES_TOKEN ,"\""},
    {COM_TOKEN ,"--"},
    //{FIN_TOKEN ,EOF},
    //{ID_TOKEN, ID},
    //{NUM_TOKEN, NUM}
    //,{ERREUR_TOKEN, RESTE}
};

int nbMotRes = sizeof tabToken / sizeof tabToken[0];
char Car_Cour;
static Token SYM_COUR;

/*
* GESTION DES ERREURS
*/

typedef enum{
    ERR_CAR_INC,
    ERR_FICH_VID,
    ERR_ID_LONG,
    ERR_ID_INV,
    ERR_NBR_LONG,
    ERR_OP_INC,
    ERR_COM_INC,
    ERR_FLOAT_INV,

    PROGRAM_ERR,
    ID_ERR,
    PV_ERR,
    PT_ERR,
    EGAL_ERR,
    NUM_ERR,
    CONST_VAR_BEGIN_ERR,
    BEGIN_ERR,
    END_ERR,
    INST_END_ERR,
    AFF_ERR,
    PO_ERR,
    PF_ERR,
    IF_THEN_ERR,
    OP_COMPAR_ERR,
    FACT_NOT_FOUND_ERR,
    WHILE_DO_ERR,
    WRITE_ERR,
    READ_ERR
}Erreurs_t;

typedef struct  {
    Erreurs_t CODE_ERR;
    char mes[40];
} Erreurs;

Erreurs MES_ERR[] = {
    {ERR_FLOAT_INV, "ERR_FLOAT_INV"},
    { ERR_CAR_INC, "CARACRETE: inconnu"},
    { ERR_FICH_VID, "FICHIER: vide"},
    {ERR_ID_LONG, "IDF: tres long"},
    {ERR_ID_INV, "IDF: non valide "},
    {ERR_NBR_LONG, "NUMBER: tres long"},
    {ERR_OP_INC, "OPERATEUR: non complet"},
    {ERR_COM_INC, "COMMENTAIRE: delimiteur absent"},
    {PROGRAM_ERR, "PROGRAM_ERR"},
    {ID_ERR, "ID_ERR"},
    {PV_ERR, "PV_ERR"},
    {PT_ERR, "PT_ERR"},
    {EGAL_ERR, "EGAL_ERR"},
    {NUM_ERR, "NUM_ERR"},
    {CONST_VAR_BEGIN_ERR, "CONST_VAR_BEGIN_ERR"},
    {BEGIN_ERR, "BEGIN_ERR"},
    {END_ERR, "END_ERR"},
    {INST_END_ERR, "INST_END_ERR"},
    {AFF_ERR, "AFF_ERR"},
    {PO_ERR, "PO_ERR"},
    {PF_ERR, "PF_ERR"},
    {IF_THEN_ERR, "IF_THEN_ERR"},
    {OP_COMPAR_ERR, "OP_COMPAR_ERR"},
    {FACT_NOT_FOUND_ERR, "FACT_NOT_FOUND_ERR"},
    {WHILE_DO_ERR, "WHILE_DO_ERR"},
    {WRITE_ERR, "WRITE_ERR"},
    {READ_ERR, "READ_ERR"}
};
int tailleERR = sizeof MES_ERR / sizeof MES_ERR[0];

//signatures des fonctions utilisees
void showCodeToken(Token token);
int estBlanc(char c);
int isAccentLettre();
int is_underscore();
void lire_Car();
void lire_mot();
void lire_nombre();
void lire_spcial();
void lire_commentaire(void );
int detectError( Erreurs_t er);
void nextToken(void);
FILE *fl = NULL;

#endif // LEX_H_INCLUDED
