#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"
#include "semanticAnalyser.h"

/**

*

* @author : Mohamed Amine EL ALAOUI

* @author : KHALIL Idriss

* @author : MEFTAHI Abderrahman

* @author : LAATAATA Abderrazak

**/


#define debugSEM 1

int OFFSET = -1; //OFFSET
int OFFSET_VARIABE = -1;



void showTS(){
    for(int i = 0; i <= OFFSET; i++){
        if(debugSEM)
        printf("%d - %s",i, TAB_IDFS[i] . NOM);
        
        //NATURE
        if(debugSEM)printf(" - %s", getNature(TAB_IDFS[i] . NIDF));

        //TYPE
        if(debugSEM){
            if(TAB_IDFS[i].TIDF == var_integer){
                printf(" - Integer\n");
            }
            else if(TAB_IDFS[i].TIDF == var_float){
                printf(" - Float\n");
            }
            else if(TAB_IDFS[i].TIDF == var_boolean){
                printf(" - Boolean\n");
            }
            else if(TAB_IDFS[i].TIDF == var_string){
                printf(" - String\n");
            }
            else if(TAB_IDFS[i].TIDF == var_char){
                printf(" - Char\n");
            }
            else if(TAB_IDFS[i].TIDF == var_void){
                printf(" - Void\n");
            }
            else{
                // ERROR TO GENERATE;
            }
        }
    }
}
void insertIDFS(NSYM nsym){
    int trouve = 0, i=0;
    while (!trouve && i<= OFFSET) {
        
        if (strcasecmp(TAB_IDFS[i].NOM, SYM_COUR.NOM) == 0) {
            trouve = 1;
            if(debugSEM){
                if(TAB_IDFS[i].NIDF == TCONST ){
                    printf("ERR: %s est deja declare comme const\n", SYM_COUR.NOM);
                    exit(EXIT_FAILURE);
                }
                else if(TAB_IDFS[i].NIDF == TVAR ){
                    printf("ERR: %s est deja declare comme variable\n", SYM_COUR.NOM);
                    exit(EXIT_FAILURE);
                }
                else if(TAB_IDFS[i].NIDF == TFUNC ){
                    printf("ERR: %s est deja declare comme fonction\n", SYM_COUR.NOM);
                    exit(EXIT_FAILURE);
                }
                else if(TAB_IDFS[i].NIDF == TPROC ){
                    printf("ERR: %s est deja declare comme procedure\n", SYM_COUR.NOM);
                    exit(EXIT_FAILURE);
                }
                else if(TAB_IDFS[i].NIDF == TPACK ){
                    printf("ERR: %s est deja declare comme package\n", SYM_COUR.NOM);
                    exit(EXIT_FAILURE);
                }
            }
            
        }
        i++;
    }
    if (!trouve) {
        strcpy(TAB_IDFS[++OFFSET].NOM, SYM_COUR.NOM);
        TAB_IDFS[OFFSET].NIDF = nsym;
        TAB_IDFS[OFFSET].ADRESSE = OFFSET;
        if(TAB_IDFS[i].NIDF == TVAR || TAB_IDFS[i].NIDF == TCONST){
                TAB_IDFS[OFFSET].ADRESSE = ++OFFSET_VARIABE;
        }
            
    }
}
int verifIDexist(NSYM nsym, char * NOM){
    int trouve = 0, i=0;
    while (!trouve && i<= OFFSET) {
        if (strcasecmp(TAB_IDFS[i].NOM, NOM) == 0) {
            trouve = 1;
            if(nsym == TBOTH && (TAB_IDFS[i].NIDF == TVAR || TAB_IDFS[i].NIDF == TCONST)){
                break;
            }
            if(TAB_IDFS[i].NIDF != nsym){
                if(debugSEM)printf("ERR: %s n'est pas une %s\n", NOM, getNature(nsym));
                exit(-1);
            }
        }
        else i++;
    }
    if (!trouve) {
        if(debugSEM)printf("ERR: %s n'est pas declare\n", NOM);
        exit(-1);
    }
    else{ //sym trouvé
        return i;
    }
    return -1;
}
char * getNature(NSYM nsym){

    char * result = (char *) malloc(100 * sizeof(char));

    if(nsym == TCONST)
        strcpy(result, "CONST");
    else if(nsym == TVAR){
        strcpy(result, "VAR");
    }
    else if(nsym == TPROC){
        strcpy(result, "PROC");
    }
    else if(nsym == TFUNC){
        strcpy(result, "FUNC");
    }
    else if(nsym == TPACK){
        strcpy(result, "PACK");
    }

    return result;
}
