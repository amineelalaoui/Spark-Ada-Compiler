#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexical.h"


int main(int argc, char* argv[]){
    if (!argv[1]) {
        printf("fichier n'exste pas\n");
        exit(EXIT_FAILURE);
    }
    fl = fopen(argv[1], "r");
    while(Car_Cour != EOF){
        nextToken();
    }

    fclose(fl);
    return 0;
}


void showCodeToken(Token token){

    switch(token.CODE){
        case ID_TOKEN:
            printf("ID_TOKEN");
            break;
        case NUM_TOKEN:
            printf("NUM_TOKEN");
            break;
        case BEGIN_TOKEN:
            printf("BEGIN_TOKEN");
            break;
        case END_TOKEN:
            printf("END_TOKEN");
            break;
        case IF_TOKEN:
            printf("IF_TOKEN");
            break;
        case THEN_TOKEN:
            printf("THEN_TOKEN");
            break;
        case WHILE_TOKEN:
            printf("WHILE_TOKEN");
            break;





        case PV_TOKEN:
            printf("PV_TOKEN");
            break;
        case PT_TOKEN:
            printf("PT_TOKEN");
            break;
        case PLUS_TOKEN:
            printf("PLUS_TOKEN");
            break;
        case MOINS_TOKEN:
            printf("MOINS_TOKEN");
            break;
        case MULT_TOKEN:
            printf("MULT_TOKEN");
            break;
        case DIV_TOKEN:
            printf("DIV_TOKEN");
            break;
        case VIR_TOKEN:
            printf("VIR_TOKEN");
            break;
        case EGAL_TOKEN:
            printf("EGAL_TOKEN");
            break;
        case AFF_TOKEN:
            printf("AFF_TOKEN");
            break;
        case INF_TOKEN:
            printf("INF_TOKEN");
            break;
        case INFEG_TOKEN:
            printf("INFEG_TOKEN");
            break;
        case SUP_TOKEN:
            printf("SUP_TOKEN");
            break;
        case SUPEG_TOKEN:
            printf("SUPEG_TOKEN");
            break;
        case DIFF_TOKEN:
            printf("DIFF_TOKEN");
            break;
        case PO_TOKEN:
            printf("PO_TOKEN");
            break;
        case PF_TOKEN:
            printf("PF_TOKEN");
            break;
        case FIN_TOKEN:
            printf("FIN_TOKEN");
            break;
        case DOUBLE_POINT_TOKEN:
            printf("DOUBLE_POINT_TOKEN");
            break;
        case APP_TOKEN:
            printf("APP_TOKEN");
            break;
        case DOUBLE_QUOTES_TOKEN:
            printf("DOUBLE_QUOTES_TOKEN");
            break;
        case ERREUR_TOKEN:
            printf("ERREUR_TOKEN");
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
            if( ! strcmp(SYM_COUR.NOM, tabToken[i].NOM ) ){
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
    printf("Symcour --> %s ( ", SYM_COUR.NOM);
    showCodeToken(SYM_COUR);puts(" )");

}
void lire_nombre(){
    int lonLex = 0;
    SYM_COUR.NOM[lonLex++] = Car_Cour;
    lire_Car();
    while ( isdigit(Car_Cour) ) {
        SYM_COUR.NOM[lonLex++] = Car_Cour;
        lire_Car();
    }

    if ( Car_Cour == '.') { // on switch vers la lecture d'un float
        SYM_COUR.NOM[lonLex++] = Car_Cour;
        lire_Car();
        if ( !isdigit(Car_Cour) ) {
            ungetc(Car_Cour, fl);
            SYM_COUR.NOM[lonLex - 1] = '\0';
        }
        else{
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
    else if (lonLex <= Max_NBRE) {
        SYM_COUR.CODE = NUM_TOKEN;
    }
    else{ // Nombre est tres long
        detectError(ERR_NBR_LONG);
        SYM_COUR.CODE = ERREUR_TOKEN;
    }
    //fin du mot
    SYM_COUR.NOM[lonLex++] = '\0';
    ungetc(Car_Cour, fl);

    printf("SC --> %s ( ", SYM_COUR.NOM);
    showCodeToken(SYM_COUR);puts(" )");
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
                SYM_COUR.NOM[0] = '*';
                SYM_COUR.NOM[1] = '\0';
                SYM_COUR.CODE = MULT_TOKEN;
                break;
            case '/':
                SYM_COUR.NOM[0] = '/';
                SYM_COUR.NOM[1] = '\0';
                SYM_COUR.CODE = DIV_TOKEN;
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
        printf("Symcour --> %s ( ", SYM_COUR.NOM);
        showCodeToken(SYM_COUR);puts(" )");
}
void lire_commentaire(void ){
    int finComment = 0;
    lire_Car();
    if( Car_Cour == '*'){
        lire_Car();
        while(finComment == 0){
            while( (Car_Cour != '*') && (Car_Cour != EOF) ){lire_Car();}
            if( Car_Cour == '*' ){
                lire_Car();
                if( Car_Cour == '}'){ // fin du commentaire
                    finComment = 1;
                    SYM_COUR.NOM[0] = '{';
                    SYM_COUR.NOM[1] = '*';
                    SYM_COUR.NOM[2] = '*';
                    SYM_COUR.NOM[3] = '}';
                    SYM_COUR.NOM[4] = '\0';
                }
            }
            else{ // EOF mais pas fin du commentaire
                detectError(ERR_COM_INC);
                exit(EXIT_FAILURE);
            }
        }
    }
}
int detectError( Erreurs_t er){
    int i = 0;
    for(; i < tailleERR, er != MES_ERR[i].CODE_ERR; i++);
    printf("erreur %s\n", MES_ERR[i].mes);
    //exit(EXIT_FAILURE);
}
void nextToken(void) {
    if(follow_token){
        follow_token = false;
        return;
    }
    lire_Car();
    memset(SYM_COUR.NOM, '\0', 20); //new word(token)
    while (estBlanc(Car_Cour))
        lire_Car();
    if( isalpha( Car_Cour) || isAccentLettre() ){
        lire_mot();
    }
    else if( isdigit( Car_Cour) ){
            lire_nombre();
    }
    else if( Car_Cour == '{'){ // on supose qu'on va lire un commentaire
            lire_commentaire();
    }
    else{ // caractere speciaux
            lire_spcial();
    }
}
