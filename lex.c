#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"

/**

*

* @author : Mohamed Amine EL ALAOUI

* @author : KHALIL Idriss

* @author : MEFTAHI Abderrahman

* @author : LAATAATA Abderrazak

**/

#define Max_NBRE 20
#define TAILLE_TAB_SYMBOLE 50

boolean debugLEX = TRUE;





/**
 * global variables
 * 
 * */
CODE_LEX LAST;

 Token tabToken[] = {

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

    {TRUE_TOKEN ,"true"},

    {FALSE_TOKEN ,"false"},

    {PRINT_TOKEN ,"print"},

    {READ_TOKEN ,"read"},

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

    {FIRST_TOKEN ,"first"},

    {LAST_TOKEN ,"last"},

    {WHEN_TOKEN ,"when"},

    {WHILE_TOKEN ,"while"},

    {WITH_TOKEN ,"with"},

    {XOR_TOKEN ,"xor"},





    //literals = ['&','(',')','*','+',',','-','.','/',':',';','<','=','>','|'] + ['\"','#']

    {EC_TOKEN ,"&"},

    {AFFEC_MULT_TOKEN ,"=*"},

    {AFFEC_DIV_TOKEN ,"=/"},

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

    {DIV_AFFEC_TOKEN ,"/="},

    {MULT_AFFEC_TOKEN ,"*="},

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

    //{FLOAT_TOKEN, FLOAT}

    // {STRING_TOKEN, STRING}

    //,{ERREUR_TOKEN, RESTE}

};

int nbMotRes = sizeof tabToken / sizeof tabToken[0];

char Car_Cour;
boolean follow_token = FALSE;
boolean first;
Token SYM_COUR;

Erreurs MES_ERR[] = {
    {RETURN_ERR, "RETURN_ERR"},
    {IF_ERR, "IF_ERR"},
    {THEN_ERR, "THEN_ERR"},
    {CASE_ERR, "CASE_ERR"},
    {IS_ERR, "IS_ERR"},
    {SUP_ERR, "SUP_ERR"},
    {IN_ERR, "IN_ERR"},
    {FUNC_NAME_ERR, "FUNC_NAME_ERR"},
    {DOUBLE_QUOTES_ERR, "DOUBLE_QUOTES_ERR"},
    {OF_ERR, "OF_ERR"},
    {RECORD_ERR, "RECORD_ERR"},
    {APP_ERR, "APP_ERR"},
    {LOOP_ERR, "LOOP_ERR"},
    {DOUBLE_POINT_ERR, "DOUBLE_POINT"},
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
    {READ_ERR, "READ_ERR"},
    {GENCODE_TAILLE_ERR, "GENCODE_TAILLE_ERR"},
    {INST_PCODE_ERR, "INST_PCODE_ERR"}
};
int tailleERR = sizeof MES_ERR / sizeof MES_ERR[0];
FILE *fl = NULL;

void showCodeToken(Token token){


    switch((int)token.CODE){

        case ID_TOKEN:
            if(debugLEX)
                printf("ID_TOKEN");

            break;

        case NUM_TOKEN:

            if(debugLEX) printf("NUM_TOKEN");

            break;

        case FLOAT_TOKEN:

            if(debugLEX) printf("FLOAT_TOKEN");

            break;

        case BEGIN_TOKEN:

            if(debugLEX) printf("BEGIN_TOKEN");

            break;

        case FALSE_TOKEN:

            if(debugLEX) printf("FALSE_TOKEN");

            break;

        case TRUE_TOKEN:

            if(debugLEX) printf("TRUE_TOKEN");

            break;
        
        case PRINT_TOKEN:

            if(debugLEX) printf("PRINT_TOKEN");

            break;

        case READ_TOKEN:

            if(debugLEX) printf("READ_TOKEN");

            break;

        case END_TOKEN:

            if(debugLEX) printf("END_TOKEN");

            break;

        case IF_TOKEN:

            if(debugLEX) printf("IF_TOKEN");

            break;

        case THEN_TOKEN:

            if(debugLEX) printf("THEN_TOKEN");

            break;

        case WHILE_TOKEN:

            if(debugLEX) printf("WHILE_TOKEN");

            break;











        case PV_TOKEN:

            if(debugLEX) printf("PV_TOKEN");

            break;

        case PT_TOKEN:

            if(debugLEX) printf("PT_TOKEN");

            break;

        case PLUS_TOKEN:

            if(debugLEX) printf("PLUS_TOKEN");

            break;

        case MOINS_TOKEN:

            if(debugLEX) printf("MOINS_TOKEN");

            break;

        case MULT_TOKEN:

            if(debugLEX) printf("MULT_TOKEN");

            break;

        case DIV_TOKEN:

            if(debugLEX) printf("DIV_TOKEN");

            break;

        case VIR_TOKEN:

            if(debugLEX) printf("VIR_TOKEN");

            break;

        case EGAL_TOKEN:

            if(debugLEX) printf("EGAL_TOKEN");

            break;

        case MULT_AFFEC_TOKEN:

            if(debugLEX) printf("MULT_AFFEC_TOKEN");

            break;

        case DIV_AFFEC_TOKEN:

            if(debugLEX) printf("DIV_AFFEC_TOKEN");

            break;

        case AFF_TOKEN:

            if(debugLEX) printf("AFF_TOKEN");

            break;

        case INF_TOKEN:

            if(debugLEX) printf("INF_TOKEN");

            break;

        case INFEG_TOKEN:

            if(debugLEX) printf("INFEG_TOKEN");

            break;

        case SUP_TOKEN:

            if(debugLEX) printf("SUP_TOKEN");

            break;

        case SUPEG_TOKEN:

            if(debugLEX) printf("SUPEG_TOKEN");

            break;

        case DIFF_TOKEN:

            if(debugLEX) printf("DIFF_TOKEN");

            break;

        case PO_TOKEN:

            if(debugLEX) printf("PO_TOKEN");

            break;

        case PF_TOKEN:

            if(debugLEX) printf("PF_TOKEN");

            break;

        case FIN_TOKEN:

            if(debugLEX) printf("FIN_TOKEN");

            break;

        case IN_TOKEN:

            if(debugLEX) printf("IN_TOKEN");

            break;

        case DOUBLE_POINT_TOKEN:

            if(debugLEX) printf("DOUBLE_POINT_TOKEN");

            break;

        case APP_TOKEN:

            if(debugLEX) printf("APP_TOKEN");

            break;

        case DOUBLE_QUOTES_TOKEN:

            if(debugLEX) printf("DOUBLE_QUOTES_TOKEN");

            break;
        
        case IS_TOKEN:

            if(debugLEX) printf("IS_TOKEN");

            break;

        case ERREUR_TOKEN:

            if(debugLEX) printf("ERREUR_TOKEN");

            break;

    }

}

//=================================== lexical================



int estBlanc(char c) {

    return isspace(c);

}

int is_underscore(){

    return Car_Cour =='_';

}

int isAccentLettre(){

    // if(-128<Car_Cour && Car_Cour <= -102){ // FROM Ç TO Ü

    if(-96<= Car_Cour && Car_Cour <= -61 ){ //éèçàùûâêîô

        return 1;

    }

    return 0;

}

void lire_Car(){

    Car_Cour = getc(fl);

}

void lire_mot(){

    int lonLex = 0;

    SYM_COUR.NOM[lonLex++] = Car_Cour;

    lire_Car();

    while (isalpha(Car_Cour) || isdigit(Car_Cour) || is_underscore()) {

        SYM_COUR.NOM[lonLex++] = Car_Cour;

        lire_Car();

    }



    if ( isAccentLettre() ) { //é à ...

        while (isalpha(Car_Cour) || isdigit(Car_Cour) || isAccentLettre() || is_underscore()) {

            SYM_COUR.NOM[lonLex++] = Car_Cour;

            lire_Car();

        }

        detectError(ERR_ID_INV);

        SYM_COUR.CODE = ERREUR_TOKEN;

    }

    else if (lonLex <= 20) {

        // on cherche de symbole

        for(int i = 0; i<nbMotRes; i++){

            if( ! strcasecmp(SYM_COUR.NOM, tabToken[i].NOM ) ){

                SYM_COUR.CODE = tabToken[i].CODE;

                break;

            }

            else{

                SYM_COUR.CODE = ID_TOKEN;

            }

        }

    }

    else{

        detectError(ERR_ID_LONG);

        SYM_COUR.CODE = ERREUR_TOKEN;

    }

    //fin du mot

    SYM_COUR.NOM[lonLex++] = '\0';

    ungetc(Car_Cour, fl);

    if(debugLEX)    
        printf("Symcour --> %s ( ", SYM_COUR.NOM);

    if(debugLEX) 
        showCodeToken(SYM_COUR);
    
    if(debugLEX) puts(" )");



}

void lire_nombre(){

    int lonLex = 0;

    SYM_COUR.NOM[lonLex++] = Car_Cour;

    lire_Car();

    while ( isdigit(Car_Cour) ) {

        SYM_COUR.NOM[lonLex++] = Car_Cour;

        lire_Car();

    }

    SYM_COUR.CODE = NUM_TOKEN;

    if ( Car_Cour == '.') { // on switch vers la lecture d'un float

        SYM_COUR.NOM[lonLex++] = Car_Cour;

        lire_Car();

        if ( !isdigit(Car_Cour) ) {

            ungetc(Car_Cour, fl);

            SYM_COUR.NOM[lonLex - 1] = '\0';

        }

        else{

            SYM_COUR.CODE = FLOAT_TOKEN;

            while( isdigit(Car_Cour) ){

                SYM_COUR.NOM[lonLex++] = Car_Cour;

                lire_Car();

            }

        }

    }



    if ( isalpha(Car_Cour) || isAccentLettre() || is_underscore() ) { // identificateur qui commence par des digits

        while ( isalnum(Car_Cour) || isAccentLettre() || is_underscore() ) {

            SYM_COUR.NOM[lonLex++] = Car_Cour;

            lire_Car();

        }

        detectError(ERR_ID_INV);

        SYM_COUR.CODE = ERREUR_TOKEN;

    }

    //fin du mot

    SYM_COUR.NOM[lonLex++] = '\0';

    ungetc(Car_Cour, fl);


    if(debugLEX)   { 

        printf("SC --> %s ( ", SYM_COUR.NOM);

        showCodeToken(SYM_COUR);puts(" )");
    }

}

void lire_spcial(){



        switch( Car_Cour ){

            case ';':

                SYM_COUR.NOM[0] = ';';

                SYM_COUR.NOM[1] = '\0';

                SYM_COUR.CODE = PV_TOKEN;

                break;

            case '.':

                SYM_COUR.NOM[0] = '.';

                SYM_COUR.NOM[1] = '\0';

                SYM_COUR.CODE = PT_TOKEN;

                break;

            case '+':

                SYM_COUR.NOM[0] = '+';

                SYM_COUR.NOM[1] = '\0';

                SYM_COUR.CODE = PLUS_TOKEN;

                break;

            case '-':

                SYM_COUR.NOM[0] = '-';

                SYM_COUR.NOM[1] = '\0';

                SYM_COUR.CODE = MOINS_TOKEN;

                break;

            case '*':

                lire_Car();

                if( Car_Cour == '='){

                    SYM_COUR.NOM[0] = '*';

                    SYM_COUR.NOM[1] = '=';

                    // SYM_COUR.NOM[2] = '\0';

                    SYM_COUR.CODE = MULT_AFFEC_TOKEN;

                }

                else{

                    SYM_COUR.NOM[0] = '*';

                    SYM_COUR.CODE = MULT_TOKEN;

                    ungetc(Car_Cour, fl);

                }

                break;

            case '/':

                lire_Car();

                if( Car_Cour == '='){

                    SYM_COUR.NOM[0] = '/';

                    SYM_COUR.NOM[1] = '=';

                    // SYM_COUR.NOM[2] = '\0';

                    SYM_COUR.CODE = DIV_AFFEC_TOKEN;

                }

                else{

                    SYM_COUR.NOM[0] = '/';

                    SYM_COUR.CODE = DIV_TOKEN;

                    ungetc(Car_Cour, fl);

                }

                break;

            case ',':

                SYM_COUR.NOM[0] = ',';

                SYM_COUR.NOM[1] = '\0';

                SYM_COUR.CODE = VIR_TOKEN;

                break;

            case '(':

                SYM_COUR.NOM[0] = '(';

                SYM_COUR.NOM[1] = '\0';

                SYM_COUR.CODE = PO_TOKEN;

                break;

            case ')':

                SYM_COUR.NOM[0] = ')';

                SYM_COUR.NOM[1] = '\0';

                SYM_COUR.CODE = PF_TOKEN;

                break;

            case '\'':

                SYM_COUR.NOM[0] = '\'';

                SYM_COUR.NOM[1] = '\0';

                SYM_COUR.CODE = APP_TOKEN;

                break;

            case '"':

                SYM_COUR.NOM[0] = '"';

                SYM_COUR.NOM[1] = '\0';

                SYM_COUR.CODE = DOUBLE_QUOTES_TOKEN;

                break;

            case ':':

                lire_Car();

                if( Car_Cour == '='){

                    SYM_COUR.NOM[0] = ':';

                    SYM_COUR.NOM[1] = '=';

                    // SYM_COUR.NOM[2] = '\0';

                    SYM_COUR.CODE = AFF_TOKEN;

                }

                else{

                    SYM_COUR.NOM[0] = ':';

                    SYM_COUR.CODE = DOUBLE_POINT_TOKEN;

                }

                break;

            case '<':

                lire_Car();

                if( Car_Cour == '='){ // inferieur ou egal

                    SYM_COUR.NOM[0] = '<';

                    SYM_COUR.NOM[1] = '=';

                    // SYM_COUR.NOM[2] = '\0';

                    SYM_COUR.CODE = INFEG_TOKEN;

                }else if( Car_Cour == '>'){ // different

                    SYM_COUR.NOM[0] = '<';

                    SYM_COUR.NOM[1] = '>';

                    // SYM_COUR.NOM[2] = '\0';

                    SYM_COUR.CODE = DIFF_TOKEN;

                }

                else{ // inferieur strictement + caractere lu de plus

                    SYM_COUR.NOM[0] = '<';

                    // SYM_COUR.NOM[1] = '\0';

                    SYM_COUR.CODE = INF_TOKEN;

                    //on a lu un caractere de plus

                    ungetc(Car_Cour, fl);

                }

                break;

            case '>':

                lire_Car();

                if( Car_Cour == '='){ // superieur ou egal

                    SYM_COUR.NOM[0] = '>';

                    SYM_COUR.NOM[1] = '=';

                    // SYM_COUR.NOM[2] = '\0';

                    SYM_COUR.CODE = SUPEG_TOKEN;

                }

                else{ // superieur strictement + caractere lu de plus

                    SYM_COUR.NOM[0] = '>';

                    // SYM_COUR.NOM[1] = '\0';

                    SYM_COUR.CODE = SUP_TOKEN;

                    //on a lu un caractere de plus

                    ungetc(Car_Cour, fl);

                }

                break;

                case '=':

                    SYM_COUR.NOM[0] = '=';

                    SYM_COUR.NOM[1] = '\0';

                    SYM_COUR.CODE = EGAL_TOKEN;

                break;

                case EOF :

                    SYM_COUR.CODE = FIN_TOKEN;

                    break;

            default :

                detectError(ERR_CAR_INC);

                SYM_COUR.CODE = ERREUR_TOKEN;

                return;

        }

        if(debugLEX) {printf("Symcour --> %s ( ", SYM_COUR.NOM);

        showCodeToken(SYM_COUR);puts(" )");
        }

}

void lire_commentaire(void ){

    while( Car_Cour == '-'){

        lire_Car();


        if( Car_Cour == '-'){
            
            lire_Car();
            
            while(Car_Cour != '\n'){
            
                lire_Car();
            }
            lire_Car();

            while (estBlanc(Car_Cour))

                lire_Car();
        }
        else{
            char c = Car_Cour;
            if(debugLEX)
                printf("<%c>\n", c);
            fputc(Car_Cour, fl);
            Car_Cour = '-';
            return;
        }
    }
}

void detectError( Erreurs_t er){

    int i = 0;

    for(; i < tailleERR; i++){
        if(er == MES_ERR[i].CODE_ERR)
            break;
    }

    printf("erreur %s\n", MES_ERR[i].mes);

    //exit(EXIT_FAILURE);

}

void nextToken(void) {

    if(follow_token){

        follow_token = FALSE;
        SYM_COUR.CODE = LAST;
        return;

    }

    lire_Car();

    memset(SYM_COUR.NOM, '\0', 20); //new word(token)

    while (estBlanc(Car_Cour))

        lire_Car();

    if( Car_Cour == '-'){

        lire_commentaire();

    }

    while (estBlanc(Car_Cour))

        lire_Car();


    if( isalpha( Car_Cour) || isAccentLettre() ){

        lire_mot();

    }
        
    else if( isdigit( Car_Cour) ){

            lire_nombre();

    }

    else{ // caractere speciaux

            lire_spcial();

    }
    LAST = SYM_COUR.CODE;
}


