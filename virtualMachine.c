#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define TAILLE_PILE 400
#define TAILLE_PCODE  400

#define debug 0
// structures pour le chargement de code -- les tokens --
typedef enum {
    NUM, ADD, SUB, MUL, DIV, EQL, NEQ,
    GTR, LSS, GEQ, LEQ, PRN, INN, INT,
    LDI, LDA, LDV ,STO, BRN, BZE, HLT,AND, OR, MOD,
    ERREUR_TOKEN, FIN_TOKEN
}CODE_LEX;
typedef struct {
    CODE_LEX CODE;
    char NOM[20]; //peut contenir des nombres
} Token;
Token tabToken[] = {
    {ADD, "ADD"},
    {SUB, "SUB"},
    {MUL, "MUL"},
    {DIV, "DIV"},
    {EQL, "EQL"},
    {NEQ, "NEQ"},
    {GTR, "GTR"},
    {LSS, "LSS"},
    {GEQ, "GEQ"},
    {LEQ, "LEQ"},
    {PRN, "PRN"},
    {INN, "INN"},
    {INT, "INT"},
    {LDI, "LDI"},
    {LDA, "LDA"},
    {LDV, "LDV"},
    {STO, "STO"},
    {BRN, "BRN"},
    {BZE, "BZE"},
    {HLT, "HLT"},
    {AND, "AND"},
    {OR, "OR"},
    {MOD, "MOD"},
    //{NUM_TOKEN, NUM}
    // {FIN_TOKEN, EOF}
};
int nbMotRes = sizeof tabToken / sizeof tabToken[0];
char Car_Cour;
Token SYM_COUR;

// structures pour le remplissage de la table du PCODE

typedef struct {
    CODE_LEX MNE;
    int SUITE;
}INSTRUCTION;
INSTRUCTION PCODE[TAILLE_PCODE];
int PC = -1;
int OFFSET=-1; //OFFSET

//---------------------- GESTION DES ERREURS --------------------
typedef enum{
    ADD_ERR,
    SUB_ERR,
    MUL_ERR,
    DIV_ERR,
    EQL_ERR,
    NEQ_ERR,
    GTR_ERR,
    LSS_ERR,
    GEQ_ERR,
    LEQ_ERR,
    PRN_ERR,
    INN_ERR,
    INT_ERR,
    LDI_ERR,
    LDA_ERR,
    LDV_ERR,
    STO_ERR,
    BRN_ERR,
    BZE_ERR,
    HLT_ERR,
    AND_ERR,
    OR_ERR,
    MOD_ERR,
    ERR_FICH_VID,
    ERR_ID_INV,
    ERR_NBR_LONG,
    NUM_ERR,
    GENCODE_TAILLE_ERR,
    INST_PCODE_ERR
}Erreurs_t;

typedef struct  {
    Erreurs_t CODE_ERR;
    char mes[40];
} Erreurs;

Erreurs MES_ERR[] = {
    {ADD_ERR, "ADD_ERR"},
    {SUB_ERR, "SUB_ERR"},
    {MUL_ERR, "MUL_ERR"},
    {DIV_ERR, "DIV_ERR"},
    {EQL_ERR, "EQL_ERR"},
    {NEQ_ERR, "NEQ_ERR"},
    {GTR_ERR, "GTR_ERR"},
    {LSS_ERR, "LSS_ERR"},
    {GEQ_ERR, "GEQ_ERR"},
    {LEQ_ERR, "LEQ_ERR"},
    {PRN_ERR, "PRN_ERR"},
    {INN_ERR, "INN_ERR"},
    {INT_ERR, "INT_ERR"},
    {LDI_ERR, "LDI_ERR"},
    {LDA_ERR, "LDA_ERR"},
    {LDV_ERR, "LDV_ERR"},
    {STO_ERR, "STO_ERR"},
    {BRN_ERR, "BRN_ERR"},
    {BZE_ERR, "BZE_ERR"},
    {HLT_ERR, "HLT_ERR"},
    {AND_ERR, "AND_ERR"},
    {OR_ERR, "OR_ERR"},
    {MOD_ERR, "MOD_ERR"},
    {NUM_ERR, "NUM_ERR"},
    { ERR_FICH_VID, "FICHIER: vide"},
    {ERR_ID_INV, "IDF: non valide "},
    {ERR_NBR_LONG, "NUMBER: tres long"},
    {GENCODE_TAILLE_ERR, "GENCODE_TAILLE_ERR"},
    {INST_PCODE_ERR, "INST_PCODE_ERR"}
};
int tailleERR = sizeof MES_ERR / sizeof MES_ERR[0];
//signatures des fonctoins utilisees
void showCodeToken(Token token);
int estBlanc(char c);
void lire_Car();
void Lire_MNE();
void Lire_Suite();
int detectError( Erreurs_t er);
void nextToken(void);

// ===================== la structure pile ==================
int MEM[TAILLE_PILE];
int SP = -1; // tete de la pile

// =====================interpretation du pcode ======================
void INTER_PCODE();
void INTER_INST(INSTRUCTION INST);


// ====================== chargement du pcode =======================
void ECRIRE1(CODE_LEX MNE);
void ECRIRE2(CODE_LEX MNE, int A);
void LOADER();
void showLoadCode();
void showMNE(CODE_LEX mne);
// ====================== analyse syntaxique ========================
void PCODE_NT(); // le non terminal pcode
void INST_PCODE();

FILE *FL_in = NULL;
int main(int argc, char* argv[]){
    if (!argv[1]) {
        printf("fichier n'exste pas\n");
        exit(EXIT_FAILURE);
    }
    FL_in = fopen(argv[1], "r");
    LOADER();
    fclose(FL_in);
    showLoadCode();
    INTER_PCODE();
    // printf("SP = %d OFFSET = %d PC = %d\n", SP, OFFSET, PC);
    
    return 0;
}


// =====================interpretation du pcode ======================
void INTER_PCODE(){
    PC=0;
    while (PCODE[PC].MNE!=HLT){
        if(debug){
            printf("======= ");
            showMNE(PCODE[PC].MNE);
            printf(" =======\n");
        }
            INTER_INST(PCODE[PC]);
        if( debug){
            printf("----- SP = %d\tPC = %d\n", SP, PC);
            for(int i = 0; i <= SP; i++){
                printf("MEM[%d] %d\n",i, MEM[i]);
            }
        }
    }
}

void INTER_INST(INSTRUCTION INST){
    int val1, adr, val2;
    switch(INST.MNE){
        case INT:
                OFFSET=SP=INST.SUITE;
                PC++;
            break;
        case LDI:
                MEM[++SP]=INST.SUITE;
                PC++;
            break;
        case LDA:
                MEM[++SP]=INST.SUITE;
                PC++;
            break;
        case STO:
                val1=MEM[SP--];
                adr=MEM[SP--];
                MEM[adr]=val1;
                PC++;
            break;
        case LDV:
                adr=MEM[SP--];
                MEM[++SP]=MEM[adr];
                PC++;
            break;
        case EQL:
                val2=MEM[SP--];
                val1=MEM[SP--];
                MEM[++SP]=(val1==val2);
                PC++;
            break;
        case NEQ:
                val2=MEM[SP--];
                val1=MEM[SP--];
                MEM[++SP]=(val1 != val2);
                PC++;
            break;
        case LSS:
                val2=MEM[SP--];
                val1=MEM[SP--];
                MEM[++SP]=(val1<val2);
                PC++;
            break;
        case LEQ:
                val2=MEM[SP--];
                val1=MEM[SP--];
                MEM[++SP]=(val1<=val2);
                PC++;
            break;
        case GTR:
                val2=MEM[SP--];
                val1=MEM[SP--];
                MEM[++SP]=(val1>val2);
                PC++;
            break;
        case GEQ:
                val2=MEM[SP--];
                val1=MEM[SP--];
                MEM[++SP]=(val1>=val2);
                PC++;
            break;
        case ADD:
                val2 = MEM[SP--];
                val1 = MEM[SP--];
                MEM[++SP] = (val1+ val2);
                PC++;
            break;
        case SUB:
                val2 = MEM[SP--];
                val1 = MEM[SP--];
                MEM[++SP] = (val1- val2);
                PC++;
            break;
        case MUL:
                val2 = MEM[SP--];
                val1 = MEM[SP--];
                MEM[++SP] = (val1* val2);
                PC++;
            break;
        case DIV:
                val2 = MEM[SP--];
                val1 = MEM[SP--];
                MEM[++SP] = (val1/ val2);
                PC++;
            break;
        case INN:
                adr = MEM[SP--];
                scanf("%d", &val1);
                MEM[adr] = val1;
                PC++;
            break;
        case PRN:
                printf("%d\n", MEM[SP--]);
                PC++; break;
        case BZE:
                if (MEM[SP--]==0)
                    PC=INST.SUITE;
                else PC++;
            break;
        case BRN:
                PC=INST.SUITE;
                break;
        case AND:
                val2 = MEM[SP--];
                val1 = MEM[SP--];
                MEM[++SP] = (val1 && val2);
                PC++;
            break;
        case OR:
                val2 = MEM[SP--];
                val1 =  MEM[SP--];
                MEM[++SP] = (val1 || val2);
                PC++;
            break;
        case MOD:
                val2 = MEM[SP--];
                val1 =  MEM[SP--];
                MEM[++SP] = (val1 % val2);
                PC++;
            break;
    }
}


// ====================== chargement du pcode =======================
void ECRIRE1(CODE_LEX MNE){
    
    if (PC == TAILLE_PCODE) {
        printf("GENCODE_TAILLE_ERR");
        exit(EXIT_FAILURE);
    }
    PC++;
    PCODE[PC].MNE = MNE;
}
void ECRIRE2(CODE_LEX MNE, int A){
    
    if (PC == TAILLE_PCODE) {
        printf("GENCODE_TAILLE_ERR");
        exit(EXIT_FAILURE);
    }
    PC++;
    PCODE[PC].MNE = MNE;
    PCODE[PC].SUITE = A;
}
void LOADER(){
    nextToken();
    PCODE_NT();
    if( SYM_COUR.CODE = FIN_TOKEN){
        puts("BRAVO =============");
    }
    else{
        puts("PAS BRAVO :((((((((((((((((((((((((((((((");
    }
    
}

// ============ syntaxique ================
void Test_Symbole (CODE_LEX cl, Erreurs_t COD_ERR){
    if (SYM_COUR.CODE == cl){
        nextToken();
    }
    else{
        detectError(COD_ERR);
    }
}

void PCODE_NT(){
    // PCODE_NT ::= INT NUM {INST_PCODE} HLT
    
    // printf("SYM_CUR %s\n", SYM_COUR.NOM);
    Token INT_tk = SYM_COUR;
    Test_Symbole(INT, INT_ERR);
    Token NUM_tk = SYM_COUR;
    Test_Symbole(NUM, NUM_ERR);
    ECRIRE2(INT_tk.CODE, atoi(NUM_tk.NOM));

    while(SYM_COUR.CODE != HLT){
        INST_PCODE();
    }

    ECRIRE1(HLT);
    Test_Symbole(HLT, HLT_ERR);
}
void INST_PCODE(){
    // INST_PCODE ::= ADD | SUB|EQL|…| [LDA | BZE|BRN|LDI] NUM
    
    CODE_LEX mne = SYM_COUR.CODE;
    switch (mne){
        case ADD:
        case SUB:
        case MUL:
        case DIV:
        case EQL:
        case NEQ:
        case GTR:
        case LSS:
        case GEQ:
        case LEQ:
        case PRN:
        case INN:
        case LDV:
        case STO:
        case AND:
        case OR:
        case MOD:
            ECRIRE1(mne);
            nextToken();
            break;
        case LDA:
        case LDI:
        case BZE:
        case BRN:
            nextToken(); //suite
            ECRIRE2(mne, atoi(SYM_COUR.NOM));
            Test_Symbole(NUM, NUM_ERR); // juste pour verifier et passer au next token
            break;
        case HLT: break;
        default:
            detectError(INST_PCODE_ERR);
            break;
    }
}

void showLoadCode(){
    for(int i = 0; i <= PC; i++){
        printf("%4d  ", i);
        showMNE(PCODE[i].MNE);
        printf(" %d\n", PCODE[i].SUITE);
    }
}
void showMNE(CODE_LEX mne){
    
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
        case OR:
            printf("OR");
            break;
        case MOD:
            printf("MOD");
            break;
        default:
            printf("Unknown");
            break;
    }
}
//=================================== lexical================

int estBlanc(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}
void lire_Car(){
    Car_Cour = getc(FL_in);
}


void Lire_MNE(){
    int lonLex = 0;
    SYM_COUR.NOM[lonLex++] = Car_Cour;
    lire_Car();
    while (isalpha(Car_Cour)) {
        SYM_COUR.NOM[lonLex++] = Car_Cour;
        lire_Car();
    }
    //fin du mot
    SYM_COUR.NOM[lonLex++] = '\0';
    ungetc(Car_Cour, FL_in);
    int i = 0;
    while( (i < nbMotRes) && (strcasecmp(SYM_COUR.NOM, tabToken[i].NOM) != 0) ){
        i++;
    }
    if( i< nbMotRes) {
        SYM_COUR.CODE = tabToken[i].CODE;
    }
    else{
        detectError(INST_PCODE_ERR);
    }
    
    
}


void Lire_Suite(){
    int lonLex = 0;
    SYM_COUR.NOM[lonLex++] = Car_Cour;
    lire_Car();
    if( Car_Cour == '+'|| Car_Cour == '-'){
        SYM_COUR.NOM[lonLex++] = Car_Cour;
        lire_Car();
    }
    
    while ( isdigit(Car_Cour) ) {
        SYM_COUR.NOM[lonLex++] = Car_Cour;
        lire_Car();
    }

    if ( isalpha(Car_Cour) ) {
        while ( isalnum(Car_Cour) ) {
            SYM_COUR.NOM[lonLex++] = Car_Cour;
            lire_Car();
        }
        detectError(ERR_ID_INV);
        SYM_COUR.CODE = ERREUR_TOKEN;
    }
    else if (lonLex <= 11) {
        SYM_COUR.CODE = NUM;
    }
    else{ // Nombre est tres long
        detectError(ERR_NBR_LONG);
        SYM_COUR.CODE = ERREUR_TOKEN;
    }
    //fin du mot
    SYM_COUR.NOM[lonLex++] = '\0';
    ungetc(Car_Cour, FL_in);
}

int detectError( Erreurs_t er){
    int i = 0;
    for(; i < tailleERR, er != MES_ERR[i].CODE_ERR; i++);
    printf("erreur %s\n", MES_ERR[i].mes);
    exit(EXIT_FAILURE);
}

void nextToken(void) {
    
    lire_Car();
    memset(SYM_COUR.NOM, '\0', 20); //new word(token)
    while (estBlanc(Car_Cour))
        lire_Car();
        
    if( isdigit( Car_Cour) || Car_Cour == '+'|| Car_Cour== '-'){
            Lire_Suite();
    }
    else if( isalpha( Car_Cour) ){
        Lire_MNE();
    }
    else if( Car_Cour == EOF){
        SYM_COUR.CODE = FIN_TOKEN;
    }
    else {
        detectError(INST_PCODE_ERR);
    }
}
