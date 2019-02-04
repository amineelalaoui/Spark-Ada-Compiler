#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"
#include "pseudo_code_generator.h"
#include "semanticAnalyser.h"

/**
*
* @author : Mohamed Amine EL ALAOUI
* @author : KHALIL Idriss
* @author : MEFTAHI Abderrahman
* @author : LAATAATA Abderrazak
**/

FILE *outFile=NULL;

int PC = 0;


void GENERER1(MNEMONIQUES MNE){
    
    if (PC == TAILLECODE) {
        detectError(GENCODE_TAILLE_ERR);
    }
    PC++;
    PCODE[PC].MNE = MNE;
}
void GENERER2(MNEMONIQUES MNE, int A){
    
    if (PC == TAILLECODE) {
        detectError(GENCODE_TAILLE_ERR);
    }
    PC++;
    PCODE[PC].MNE = MNE;
    PCODE[PC].SUITE = A;
}
void showMNE(MNEMONIQUES mne){
    
    switch (mne){
        case ADD:
            printf("ADD");
            break;
        case SUB:
            printf("SUB");
            break;
        case MUL:
            printf("MUL");
            break;
        case DIV:
            printf("DIV");
            break;
        case EQL:
            printf("EQL");
            break;
        case NEQ:
            printf("NEQ");
            break;
        case GTR:
            printf("GTR");
            break;
        case LSS:
            printf("LSS");
            break;
        case GEQ:
            printf("GEQ");
            break;
        case LEQ:
            printf("LEQ");
            break;
        case PRN:
            printf("PRN");
            break;
        case INN:
            printf("INN");
            break;
        case INT:
            printf("INT");
            break;
        case LDI:
            printf("LDI");
            break;
        case LDA:
            printf("LDA");
            break;
        case LDV:
            printf("LDV");
            break;
        case  STO:
            printf("STO");
            break;
        case BRN:
            printf("BRN");
            break;
        case BZE:
            printf("BZE");
            break;
        case HLT:
            printf("HLT");
            break;
        case AND:
            printf("AND");
            break;
        case XOR:
            printf("XOR");
            break;
        case OR:
            printf("OR");
            break;
        case DIV_AFFEC:
            printf("DIV_AFFEC");
            break;
        case MULT_AFFEC:
            printf("MULT_AFFEC");
            break;
        default:
            printf("Unknown");
            break;
    }
}
void showGenCode(){
    for(int i = 0; i <= PC; i++){
        printf("%4d  ", i );
        showMNE(PCODE[i].MNE);
        
        if(PCODE[i].MNE == LDA || PCODE[i].MNE == LDI || PCODE[i].MNE == INT || PCODE[i].MNE == BZE || PCODE[i].MNE == BRN)
            printf(" %d", PCODE[i].SUITE);
        puts("");
        //SaveInstToFile(PCODE[i], stdout);
        //SaveInstToFile(PCODE[i], stdout);
    }
}
void SaveInstToFile(INSTRUCTION INST, FILE* FICH_SORTIE){
    switch( INST.MNE){
        case LDA: fprintf(FICH_SORTIE, "%s\t%d\n", "LDA", INST.SUITE); break;
        case LDI: fprintf(FICH_SORTIE, "%s\t%d\n", "LDI", INST.SUITE); break;
        case INT: fprintf(FICH_SORTIE, "%s\t%d\n", "INT", INST.SUITE); break;
        case BZE: fprintf(FICH_SORTIE, "%s\t%d\n", "BZE", INST.SUITE); break;
        case BRN: fprintf(FICH_SORTIE, "%s\t%d\n", "BRN", INST.SUITE); break;
        case LDV: fprintf(FICH_SORTIE, "%s\n", "LDV"); break;
        case ADD: fprintf(FICH_SORTIE, "%s\n", "ADD"); break;
        case SUB: fprintf(FICH_SORTIE, "%s\n", "SUB"); break;
        case MUL: fprintf(FICH_SORTIE, "%s\n", "MUL"); break;
        case DIV: fprintf(FICH_SORTIE, "%s\n", "DIV"); break;
        case LEQ: fprintf(FICH_SORTIE, "%s\n", "LEQ"); break;
        case GEQ: fprintf(FICH_SORTIE, "%s\n", "GEQ"); break;
        case NEQ: fprintf(FICH_SORTIE, "%s\n", "NEQ"); break;
        case LSS: fprintf(FICH_SORTIE, "%s\n", "LSS"); break;
        case GTR: fprintf(FICH_SORTIE, "%s\n", "GTR"); break;
        case HLT: fprintf(FICH_SORTIE, "%s\n", "HLT"); break;
        case STO: fprintf(FICH_SORTIE, "%s\n", "STO"); break;
        case AND: fprintf(FICH_SORTIE, "%s\n", "AND"); break;
        case OR: fprintf(FICH_SORTIE, "%s\n", "OR"); break;
        case MOD: fprintf(FICH_SORTIE, "%s\n", "MOD"); break;
        case INN: fprintf(FICH_SORTIE, "%s\n", "INN"); break;
        case PRN: fprintf(FICH_SORTIE, "%s\n", "PRN"); break;
        case EQL: fprintf(FICH_SORTIE, "%s\n", "EQL"); break;
        default: detectError(INST_PCODE_ERR); break;
    }
}
void SavePCodeToFile(char *filename){
    if (!filename)  {
        outFile = fopen("b.pcode", "w+");
    }
    else{
        outFile = fopen(filename, "w+");
    }
    for(int i = 0; i <= PC; i++){
        SaveInstToFile(PCODE[i], outFile);   
    }
    fclose(outFile);
}


