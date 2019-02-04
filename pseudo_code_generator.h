#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"

#define TAILLECODE  400
#define debugPSCODE 1

typedef enum {
    ADD,SUB,MUL,DIV,EQL,NEQ,GTR,
			LSS,GEQ,LEQ, PRN,INN,INT,LDI,LDA,LDV,
			STO,BRN,BZE,HLT, MOD, AND, DIV_AFFEC, MULT_AFFEC, XOR, OR
}MNEMONIQUES;



typedef struct {
    MNEMONIQUES MNE;
    int SUITE;
}INSTRUCTION;


extern void GENERER1(MNEMONIQUES MNE);
extern void GENERER2(MNEMONIQUES MNE, int A);
extern void showMNE(MNEMONIQUES mne);
extern void showGenCode();
extern void SaveInstToFile(INSTRUCTION INST, FILE* FICH_SORTIE);
extern void SavePCodeToFile(char* path);

INSTRUCTION PCODE[TAILLECODE];
extern int PC; // = 0

