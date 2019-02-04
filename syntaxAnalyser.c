#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"
#include "semanticAnalyser.h"
#include "pseudo_code_generator.h"



#define debugSYNT 1



int last_IND = 0;
int last_INDO = 0;
boolean drapMINUS = 0;


/**

*

* @author : Mohamed Amine EL ALAOUI

* @author : KHALIL Idriss

* @author : MEFTAHI Abderrahman

* @author : LAATAATA Abderrazak

**/



boolean list_with_use_clause();

boolean enumeration_type_definition();

boolean multiple_id();

boolean with_use_clause();

boolean subprogram_specification();

boolean type_declaration();

boolean parameter_specification();

boolean other_parameter_specification();

boolean formal_part();

boolean basic_declaration();




boolean subprogram_body();

boolean program();

boolean integer_type_definition();

boolean real_type_definition();

boolean array_type_definition();

boolean record_type_definition();

boolean component_list();

boolean component_item();

boolean component_item();

boolean sequence_statement();

boolean statement();

boolean simple_statement();

boolean null_statement();

boolean lire_number();

boolean exit_statement();

boolean goto_statement();

boolean object_number_declaration();

boolean sequence_statement();

boolean statement();

boolean null_statement();

boolean exit_statement();

boolean goto_statement();

boolean procedure_call_or_assign_statement();

boolean params();

boolean return_statement();

boolean compound_statement();

boolean if_statement();

boolean case_statement();

boolean case_statement_alt();

boolean loop_statement();

boolean block_statement();

boolean expression();

boolean relation();

boolean simple_expression();

boolean term ();

boolean factor();

boolean primary();

boolean package_body();

boolean package_body_aux();

boolean package_body_adb();

boolean refinement_definition();

boolean package_implementation();

boolean package_body_ads();

boolean pragma_argument_association();

boolean main_program();
boolean print();
boolean read();


int main(int argc, char* argv[]){

  if (!argv[1]) {

        printf("fichier n'exste pas\n");

        exit(EXIT_FAILURE);

    }

    fl = fopen(argv[1], "r");

    nextToken();

    if(main_program()){

        printf("YEEES\n");

    }

    else

        printf("NOOO\n");


    if(debugSEM)
        showTS();
    
    if(debugPSCODE)
        showGenCode();

    SavePCodeToFile(argv[2]);

    fclose(fl);

    return 0;

}





// integer_type_definition -> range T_NUMERIC .. T_NUMERIC | mod expression



// 9 - enumeration_type_definition ->'(' id [ , id]*  ')'



boolean enumeration_type_definition(){

    if(debugSYNT)
        printf("enumeration_type_definition\n");

    if(SYM_COUR.CODE == PO_TOKEN){

        nextToken();

        if(SYM_COUR.CODE == ID_TOKEN){

            nextToken();

            while(SYM_COUR.CODE == VIR_TOKEN){

                nextToken();

                if(SYM_COUR.CODE != ID_TOKEN){

                    detectError(ID_ERR);
                    return FALSE;

                }

                nextToken();

            }

            if(SYM_COUR.CODE == PF_TOKEN)

                return TRUE;
            
            else
                
                detectError(PF_ERR);

        }
        else
            detectError(ID_ERR);

    }
    else
        detectError(PO_ERR);

    return FALSE;

}



//2_2 - multiple_id -> .id multiple_id | epsilon

//FIRST = (.);

//FOLLOW = USE ID PROCEDURE FUNCTION


boolean multiple_id(){

    if(debugSYNT)
        printf("multiple_id\n");

    boolean result = FALSE;

    if (SYM_COUR.CODE == USE_TOKEN ||

        SYM_COUR.CODE == WITH_TOKEN ||

        SYM_COUR.CODE == PROCEDURE_TOKEN ||

        SYM_COUR.CODE == FUNCTION_TOKEN ||
        
        SYM_COUR.CODE == VIR_TOKEN
        ){

        follow_token = TRUE;

        result = TRUE;

    }

    else if(SYM_COUR.CODE == PT_TOKEN){

        nextToken();

        if(SYM_COUR.CODE == ID_TOKEN){

            nextToken();

            if(multiple_id()){

                result = TRUE;

            }

        }
        else
            detectError(ID_ERR);

    }
    else
        detectError(PT_ERR);
    

    return result;

}



//2_1 with_use_clause -> (use | with) id multiple_id {, id multiple_id}*



boolean with_use_clause(){

    if(debugSYNT)
        printf("with_use_clause\n");

    boolean result = FALSE;

    if(SYM_COUR.CODE == USE_TOKEN ||

        SYM_COUR.CODE == WITH_TOKEN){

		nextToken();

		if(SYM_COUR.CODE == ID_TOKEN){

            nextToken();

            if(multiple_id()){

                nextToken();

                while(SYM_COUR.CODE == VIR_TOKEN){
                    
                    nextToken();

                    if(SYM_COUR.CODE == ID_TOKEN){

                        nextToken();

                        if(!multiple_id()){

                            return FALSE;
                        
                        }
                    }
                    else{

                        detectError(ID_ERR);
                        return FALSE;
                    }
                }

                follow_token = TRUE;

                result = TRUE;

            }

        }
        else
            detectError(ID_ERR);

    }



	return result;

}



//1_2 - list_with_use_clause -> with_use_clause list_with_use_clause | epsilon

//FIRST = (use, with)

//FOLLOW = (procedure, function)

//VV

boolean list_with_use_clause(){

    if(debugSYNT)
        printf("list_with_use_clause\n");

    boolean result = FALSE;

    if (SYM_COUR.CODE == PROCEDURE_TOKEN ||

        SYM_COUR.CODE == FUNCTION_TOKEN){

        follow_token = TRUE;

        result = TRUE;

    }

    else if(with_use_clause()){

        nextToken();

        if(list_with_use_clause()){

            result = TRUE;

        }

    }

    return result;

}




//8 - type_declaration -> type id is (enumeration_type_definition | integer_type_definition | real_type_definition | record_type_definition | array_type_definition);



boolean type_declaration(){


    if(debugSYNT)
        printf("type_declaration\n");

    if(SYM_COUR.CODE == TYPE_TOKEN){

        nextToken();

        if(SYM_COUR.CODE == ID_TOKEN){

            nextToken();

            if(SYM_COUR.CODE == IS_TOKEN){

                nextToken();

                if(SYM_COUR.CODE == PO_TOKEN){

                    if(enumeration_type_definition()){

                        nextToken();

                        if(SYM_COUR.CODE == PV_TOKEN)

                            return TRUE;

                        else{
                            
                            detectError(PV_ERR);
                            return FALSE;

                        }

                    }

                }

                if(SYM_COUR.CODE == RECORD_TOKEN){

                    if(record_type_definition()){

                        nextToken();

                        if(SYM_COUR.CODE == PV_TOKEN)

                            return TRUE;

                        else{
                            
                            detectError(PV_ERR);
                            return FALSE;

                        }

                    }

                }

                if(SYM_COUR.CODE == RANGE_TOKEN){

                    if(integer_type_definition()){

                        nextToken();

                        if(SYM_COUR.CODE == PV_TOKEN)

                            return TRUE;

                        else{
                            
                            detectError(PV_ERR);
                            return FALSE;

                        }
                    }

                }

                if(SYM_COUR.CODE == DIGITS_TOKEN){

                    if(real_type_definition()){

                        nextToken();

                        if(SYM_COUR.CODE == PV_TOKEN)

                            return TRUE;

                        else{
                            
                            detectError(PV_ERR);
                            return FALSE;

                        }
                    }

                }

                if(SYM_COUR.CODE == ARRAY_TOKEN){

                    if(array_type_definition()){

                        nextToken();

                        if(SYM_COUR.CODE == PV_TOKEN)

                            return TRUE;

                        else{
                            
                            detectError(PV_ERR);
                            return FALSE;

                        }

                    }

                }

            }

            else
                detectError(IS_ERR);

        }

        else
            detectError(ID_ERR);

    }

    return FALSE;

}



// 6 - parameter_specification -> id [, id]* : [in | out] id [:= expression]



boolean parameter_specification(){

    if(debugSYNT)
        printf("parameter_specification\n");

    if(SYM_COUR.CODE == ID_TOKEN){

        nextToken();

        while(SYM_COUR.CODE == VIR_TOKEN){
            nextToken();
            if(SYM_COUR.CODE != ID_TOKEN){
                detectError(ID_ERR);
                return FALSE;
            }
            nextToken();
        }

        if(SYM_COUR.CODE == DOUBLE_POINT_TOKEN){

            nextToken();

            if(SYM_COUR.CODE == IN_TOKEN || SYM_COUR.CODE == OUT_TOKEN){

                nextToken();

            }

            if(SYM_COUR.CODE == ID_TOKEN){

                nextToken();

                if(SYM_COUR.CODE == PV_TOKEN || SYM_COUR.CODE == PF_TOKEN){

                    follow_token = TRUE;

                    return TRUE;

                }

                if(SYM_COUR.CODE == DOUBLE_POINT_TOKEN){

                    nextToken();

                    if(SYM_COUR.CODE == EGAL_TOKEN){

                        nextToken();

                        if(expression())

                            return TRUE;

                    }
                    else
                        detectError(EGAL_ERR);

                }
                else
                    detectError(DOUBLE_POINT_ERR);

            }
            else
                detectError(ID_ERR);

        }
        else
            detectError(DOUBLE_POINT_ERR);

    }
    else    
        detectError(ID_ERR);

    return FALSE;

}

// 5_2 other_parameter_specification -> ; parameter_specification other_parameter_specification | epsilon

//FOLLOW )



boolean other_parameter_specification(){

    if(debugSYNT)
        printf("other_parameter_specification\n");

    if(SYM_COUR.CODE == PF_TOKEN){

        follow_token = TRUE;

        return TRUE;

    }

    if(SYM_COUR.CODE == PV_TOKEN){

        nextToken();

        if(parameter_specification()){

            nextToken();

            if(other_parameter_specification())

                return TRUE;

        }

    }
    else
        detectError(PV_ERR);

    return TRUE;

}



//5_1 - formal_part -> parameter_specification other_parameter_specification



boolean formal_part(){

    if(debugSYNT)
        printf("formal_part\n");

    if(parameter_specification()){

        nextToken();


        if(other_parameter_specification()){

            return TRUE;

        }

    }

    return FALSE;

}





// 8 - basic_declaration -> type_declaration | object_number_declaration | subprogram_body



boolean basic_declaration(){

    if(debugSYNT)
        printf("basic_declaration\n");

    
    boolean result = FALSE;


    if(SYM_COUR.CODE == PROCEDURE_TOKEN || SYM_COUR.CODE == FUNCTION_TOKEN){

        if(subprogram_body())

            return TRUE;
    }

    if(SYM_COUR.CODE == TYPE_TOKEN){

        if(type_declaration()){

            result = TRUE;

        }

    }

    if(SYM_COUR.CODE == ID_TOKEN){

        if(object_number_declaration()){

            result = TRUE;

        }

    }

    return result;

}


// 3_1 subprogram_body -> subprogram_specification is basic_declaration* begin sequence_statement end [id];

//4 - subprogram_specification -> procedure id ['(' formal_part ')'] | function id ['(' formal_part ')'] return id


boolean subprogram_body(){

    if(debugSYNT)         printf("subprogram_body\n");

    boolean drap = FALSE;

    boolean result = FALSE;

    char FUNC_NAME[100];

    if(SYM_COUR.CODE == FUNCTION_TOKEN){

        int curr_off;

        nextToken();

        if(SYM_COUR.CODE == ID_TOKEN){

            insertIDFS(TFUNC);

            strcpy(FUNC_NAME, SYM_COUR .NOM);

            curr_off = OFFSET;

            nextToken();

            if(SYM_COUR.CODE == PO_TOKEN){

                nextToken();

                if(formal_part()){

                    nextToken();

                    if(SYM_COUR.CODE == PF_TOKEN){

                        nextToken();

                        if(SYM_COUR.CODE == RETURN_TOKEN){

                            nextToken();

                            if(SYM_COUR.CODE == ID_TOKEN){
                                
                                TAB_IDFS[curr_off] . TIDF = VariableType();

                                drap = TRUE;

                            }
                            else detectError(ID_ERR);

                        }
                        else detectError(RETURN_ERR);

                    }
                    else detectError(PF_ERR);

                }

            }

            else{

                if(SYM_COUR.CODE == RETURN_TOKEN){

                    nextToken();

                    if(SYM_COUR.CODE == ID_TOKEN){

                        TAB_IDFS[curr_off] . TIDF = VariableType();
                        
                        drap = TRUE;

                    }
                    else detectError(ID_ERR);

                }
                else detectError(RETURN_ERR);

            }
        }
        else detectError(ID_ERR);

    }

    else{


        if(SYM_COUR.CODE == PROCEDURE_TOKEN){

            nextToken();

            if(SYM_COUR.CODE == ID_TOKEN){

                insertIDFS(TPROC);

                strcpy(FUNC_NAME, SYM_COUR . NOM);

                TAB_IDFS[OFFSET] . TIDF = var_void;

                nextToken();

                if(SYM_COUR.CODE == PO_TOKEN){

                    nextToken();

                    if(formal_part()){

                        nextToken();

                        if(SYM_COUR.CODE == PF_TOKEN){

                            drap = TRUE;

                        }
                        else detectError(PF_ERR);
                    }

                }

                else{

                    drap = TRUE;

                    follow_token = TRUE;


                }

            }
            else detectError(ID_ERR);
        }

    }



    if(drap){


        nextToken();

        if(SYM_COUR.CODE == IS_TOKEN){

            nextToken();

            while (SYM_COUR.CODE == TYPE_TOKEN || SYM_COUR.CODE == ID_TOKEN || SYM_COUR.CODE == FUNCTION_TOKEN || SYM_COUR.CODE == PROCEDURE_TOKEN){

                if(!basic_declaration()) return FALSE;
                
                nextToken();
            }
            

            PCODE[0].MNE = INT;
            PCODE[0].SUITE = OFFSET_VARIABE;

            if(SYM_COUR.CODE == BEGIN_TOKEN){


                nextToken();

                if(sequence_statement()){

                        nextToken();

                        if(SYM_COUR.CODE == END_TOKEN){
                            
                            nextToken();

                            if(SYM_COUR.CODE == PV_TOKEN){

                                result = TRUE;

                            }
                            else{

                                if(SYM_COUR.CODE == ID_TOKEN){

                                    if(strcasecmp(SYM_COUR.NOM, FUNC_NAME) != 0) //error
                                        detectError(FUNC_NAME_ERR);

                                    nextToken();

                                    if(SYM_COUR.CODE == PV_TOKEN){


                                        return TRUE;
                                    
                                    }
                                    else detectError(ID_ERR);

                                }
                                else detectError(ID_ERR);

                            }

                        }
                        else detectError(END_ERR);

                    }

                }
                else detectError(BEGIN_ERR);

        }
        else detectError(IS_ERR);

    }



    return result;

}



//10 - integer_type_definition -> range expression .. expression | mod expression



boolean integer_type_definition(){

    if(debugSYNT)         printf("integer_type_definition\n");


    boolean result = FALSE;

    if(SYM_COUR.CODE == RANGE_TOKEN){

        nextToken();

        if(expression()){

            nextToken();

            if(SYM_COUR.CODE == PT_TOKEN){

                nextToken();

                if(SYM_COUR.CODE == PT_TOKEN){

                    nextToken();

                    if(expression()){

                        result = TRUE;

                    }

                }
                else detectError(ID_ERR);

            }
            else detectError(DOUBLE_POINT_ERR);

        }

    }

    else if(SYM_COUR.CODE == MOD_TOKEN){

        nextToken();

            if(expression())

                result = TRUE;

    }

    return result;

}





//11 - real_type_definition -> digit expression [range expression .. expression]



boolean real_type_definition(){if(debugSYNT)         printf("real_type_definition\n");

    if(SYM_COUR.CODE == DIGITS_TOKEN){

        nextToken();

        if(expression()){

            nextToken();

            if(SYM_COUR.CODE == RANGE_TOKEN){

                nextToken();

                if(expression()){

                    nextToken();

                    if(SYM_COUR.CODE == PT_TOKEN){

                        nextToken();

                        if(SYM_COUR.CODE == PT_TOKEN){

                            nextToken();

                            if(expression()){

                                return TRUE;

                            }

                        }
                        else detectError(DOUBLE_POINT_ERR);

                    }
                    else detectError(DOUBLE_POINT_ERR);

                }

            }

            else{

                follow_token = TRUE;

                return TRUE;

            }

        }

    }

    return FALSE;

}



//12 - array_type_definition -> array '(' id [range (<> | T_NUMERIC .. T_NUMERIC)] ')' of id



boolean array_type_definition(){
    
    if(debugSYNT)         printf("array_type_definition\n");

    if(SYM_COUR.CODE == ARRAY_TOKEN){

        nextToken();

        if(SYM_COUR.CODE == PO_TOKEN){

            nextToken();

            if(SYM_COUR.CODE == ID_TOKEN){

                nextToken();

                if(SYM_COUR.CODE == RANGE_TOKEN){

                    nextToken();

                    if(SYM_COUR.CODE == DIFF_TOKEN){

                        nextToken();

                    }

                    else if(expression()){

                        nextToken();

                        if(SYM_COUR.CODE == PT_TOKEN){

                            nextToken();

                            if(SYM_COUR.CODE == PT_TOKEN){

                                nextToken();

                                if(expression()){

                                    nextToken();

                                }

                                else

                                    return FALSE;

                            }

                            else{
                                detectError(DOUBLE_POINT_ERR);
                                return FALSE;
                            }

                        }

                        else{
                            detectError(DOUBLE_POINT_ERR);
                            return FALSE;
                        }
                    }

                    else

                        return FALSE;

                }

                if(SYM_COUR.CODE == PF_TOKEN){

                    nextToken();

                    if(SYM_COUR.CODE == OF_TOKEN){

                        nextToken();

                        if(SYM_COUR.CODE == ID_TOKEN)

                            return TRUE;
                        
                        else detectError(ID_ERR);

                    }
                    else detectError(OF_ERR);

                }
                else detectError(PF_ERR);

            }
            else detectError(ID_ERR);

        }
        else detectError(PO_ERR);

    }

    return FALSE;

}



//record_type_definition -> null record; | record component_list end record

boolean record_type_definition(){if(debugSYNT)         printf("record_type_definition\n");

    if(SYM_COUR.CODE == NULL_TOKEN){

        nextToken();

        if(SYM_COUR.CODE == RECORD_TOKEN){

            nextToken();

            if(SYM_COUR.CODE == PV_TOKEN){

                return TRUE;

            }
            else detectError(PV_ERR);

        }
        else detectError(RECORD_ERR);

    }

    else{

        if(SYM_COUR.CODE == RECORD_TOKEN){

            nextToken();

            if(component_list()){

                nextToken();

                if(SYM_COUR.CODE == END_TOKEN){

                    nextToken();

                    if(SYM_COUR.CODE == RECORD_TOKEN){

                        return TRUE;

                    }
                    else detectError(RECORD_ERR);

                }
                else detectError(END_ERR);
            }

        }

    }

    return FALSE;

}

// 14 - component_list -> component_item [component_item]* | null ;

boolean component_list(){
    
    if(debugSYNT)         printf("component_list\n");

    if(component_item()){

        nextToken();

        while(component_item()){

            nextToken();

        }

        follow_token = TRUE;

        return TRUE;

    }

    else{

        if(SYM_COUR.CODE == NULL_TOKEN){

            return TRUE;

        }

    }

    return FALSE;

}



//15 - component_item -> id : id [:= expression] ; 

boolean component_item(){
    
    if(debugSYNT)         printf("component_item\n");

    if(SYM_COUR.CODE == ID_TOKEN){

        nextToken();

        if(SYM_COUR.CODE == DOUBLE_POINT_TOKEN){

            nextToken();

            if(SYM_COUR.CODE == ID_TOKEN){

                nextToken();

                if(SYM_COUR.CODE == AFF_TOKEN){

                    nextToken();

                    if(expression()){

                        nextToken();
                        
                        if(SYM_COUR.CODE == PV_TOKEN)

                            return TRUE;
                        
                        else{
                         
                            detectError(PV_ERR);
                         
                            return FALSE;
                        
                        }
                    }
                }

                else{
                    if(SYM_COUR.CODE == PV_TOKEN)
                        return TRUE;
                    else{
                        detectError(PV_ERR);
                        return FALSE;
                    }
                }

            }
            else detectError(ID_ERR);

        }
        else detectError(DOUBLE_POINT_ERR);

    }

    return FALSE;

}

//SEMANTIQUE

TSYM VariableType(){
    TSYM type;

    if(strcasecmp(SYM_COUR.NOM, "Integer") == 0){
        type = var_integer;
    }
    else if(strcasecmp(SYM_COUR.NOM, "Float") == 0){
        type = var_float;
    }
    else if(strcasecmp(SYM_COUR.NOM, "Boolean") == 0){
        type = var_boolean;
    }
    else if(strcasecmp(SYM_COUR.NOM, "String") == 0){
        type = var_string;
    }
    else if(strcasecmp(SYM_COUR.NOM, "Char") == 0){
        type = var_char;
    }
    else{
        // ERROR TO GENERATE;
    }
    if(debugSEM)
        showTS(); 
    
    return type;
}


//16 - object_number_declaration -> id [,id]* : (
//                                          (id [:= expression] | 
//                                          constant id := expression)
//                                              )       ;
//SYNTAXIQUE
boolean object_number_declaration(){
    
    if(debugSYNT)         printf("object_number_declaration\n");

    int curr_off = OFFSET;

    if(SYM_COUR.CODE == ID_TOKEN){

        insertIDFS(TVAR);

        GENERER2(LDA, TAB_IDFS[OFFSET].ADRESSE);
        
        nextToken();

        while(SYM_COUR.CODE == VIR_TOKEN){

            nextToken();

            if(SYM_COUR.CODE != ID_TOKEN){

                return FALSE;

            }

            insertIDFS(TVAR);

            GENERER2(LDA, TAB_IDFS[OFFSET].ADRESSE);

            nextToken();

        }

        if(SYM_COUR.CODE == DOUBLE_POINT_TOKEN){

            nextToken();

            if(SYM_COUR.CODE == CONSTANT_TOKEN){

                for(int i = curr_off + 1; i <= OFFSET; i++){
                    
                    TAB_IDFS[i] . NIDF = TCONST;
                
                }

                nextToken();

                if(SYM_COUR.CODE == ID_TOKEN){ // VARIABLE TYPE
                    
                    for(int i = curr_off + 1; i <= OFFSET; i++){
                    
                        TAB_IDFS[i] . TIDF  = VariableType();
                
                    }
                    
                    nextToken();

                    if(SYM_COUR.CODE == AFF_TOKEN){

                        nextToken();

                        if(expression()){

                            GENERER1(STO);

                            nextToken();

                            if(SYM_COUR.CODE == PV_TOKEN)
                                
                                return TRUE;

                        }

                    }
                }

            }
            else if(SYM_COUR.CODE == ID_TOKEN){ // variable type

        
                for(int i = curr_off + 1; i <= OFFSET; i++){

                    TAB_IDFS[i] . TIDF  = VariableType();
                
                }

                if(debugSEM)
                    showTS(); 

                nextToken();

                if(SYM_COUR.CODE == AFF_TOKEN){

                    nextToken();

                    if(expression()){

                        GENERER1(STO);

                        nextToken();

                        if(SYM_COUR.CODE == PV_TOKEN)

                            return TRUE;

                    }

                }
                else{
                    if(SYM_COUR.CODE == PV_TOKEN){

                        GENERER2(LDI, 0);
                        GENERER1(STO);

                        return TRUE;
                    }
                }
            }

        }

    }

    return FALSE;

}



// 17 - sequence_statement -> statement {statement}*
//SYNTAXIQUE
boolean sequence_statement(){
    
    if(debugSYNT)         printf("sequence_statement\n");

    if(SYM_COUR.CODE == END_TOKEN){
        return TRUE;
    }

    if(statement()){

        nextToken();

        while(SYM_COUR.CODE == IF_TOKEN ||SYM_COUR.CODE == CASE_TOKEN ||SYM_COUR.CODE == WHILE_TOKEN ||SYM_COUR.CODE == FOR_TOKEN ||SYM_COUR.CODE == LOOP_TOKEN ||SYM_COUR.CODE == DECLARE_TOKEN ||SYM_COUR.CODE == BEGIN_TOKEN ||SYM_COUR.CODE == NULL_TOKEN ||SYM_COUR.CODE == RETURN_TOKEN ||SYM_COUR.CODE == EXIT_TOKEN ||SYM_COUR.CODE == GOTO_TOKEN ||SYM_COUR.CODE == ID_TOKEN ||SYM_COUR.CODE == PRINT_TOKEN ||SYM_COUR.CODE == READ_TOKEN){
            if(!statement())
                return FALSE;
            nextToken();
        }

        follow_token = TRUE;

        return TRUE;

    }

    return FALSE;

}



//18 - statement -> simple_statement | compound_statement
//SYNTAXIQUE
boolean statement(){
    
    if(debugSYNT)         printf("statement\n");

    if(SYM_COUR.CODE == IF_TOKEN || SYM_COUR.CODE == CASE_TOKEN || SYM_COUR.CODE == WHILE_TOKEN ||  SYM_COUR.CODE == FOR_TOKEN ||

        SYM_COUR.CODE == LOOP_TOKEN || SYM_COUR.CODE == DECLARE_TOKEN || SYM_COUR.CODE == BEGIN_TOKEN){
        
        boolean drap = compound_statement();
        return drap;

    }
    return simple_statement();

}



//19 - simple_statement ::= null_statement | procedure_call_or_assign_statement | exit_statement | goto_statement | return_statement
//SYNTAXIQUE
boolean simple_statement(){
    
    if(debugSYNT)         printf("simple_statement\n");

    //null_statement

    if(SYM_COUR.CODE == NULL_TOKEN){

        return TRUE;

    }

    //procedure_call_or_assign_statement

    if(SYM_COUR.CODE == ID_TOKEN){

        return procedure_call_or_assign_statement();

    }
    
    //print

    if(SYM_COUR.CODE == PRINT_TOKEN){
        
        return print();

    }

    //read
    if(SYM_COUR.CODE == READ_TOKEN){
        return read();

    }

    //exit_statement

    if(SYM_COUR.CODE == EXIT_TOKEN){

        return exit_statement();

    }

    //goto_statement

    if(SYM_COUR.CODE == GOTO_TOKEN){

        return goto_statement();

    }

    //return

    if(SYM_COUR.CODE == RETURN_TOKEN){

        return return_statement();

    }

    return FALSE;

}



//20 - null_statement -> null ;
//SYNTAXIQUE
boolean null_statement(){if(debugSYNT)         printf("null_statement\n");

    if(SYM_COUR.CODE == NULL_TOKEN){

        nextToken();

        if(SYM_COUR.CODE == PV_TOKEN)

            return TRUE;
        
        else detectError(PV_ERR);
    }

    return FALSE;

}



//21 - exit_statement -> exit [id] [when expression];
//SYNTAXIQUE
boolean exit_statement(){if(debugSYNT)         printf("exit_statement\n");

    if(SYM_COUR.CODE == EXIT_TOKEN){

        nextToken();

        if(SYM_COUR.CODE == ID_TOKEN){

            nextToken();

            if(SYM_COUR.CODE == WHEN_TOKEN){

                nextToken();

                if(expression()){

                    nextToken();

                    if(SYM_COUR.CODE == PV_TOKEN){

                        return TRUE;

                    }
                    else detectError(PV_ERR);
                }
            }

            else{
                if(SYM_COUR.CODE == PV_TOKEN){

                        return TRUE;

                }
                else detectError(PV_ERR);
            }
        }

        else if(SYM_COUR.CODE == WHEN_TOKEN){

                nextToken();

                if(expression()){

                    nextToken();

                    if(SYM_COUR.CODE == PV_TOKEN){

                        return TRUE;

                    }
                    else detectError(PV_ERR);
                }

            }

        else if(SYM_COUR.CODE == PV_TOKEN){

                        return TRUE;

        }
        else detectError(PV_ERR);

    }

    return FALSE;

}



//22- goto_statement -> goto id;
//SYNTAXIQUE
boolean goto_statement(){
    
    if(debugSYNT)         printf("goto_statement\n");

    if(SYM_COUR.CODE == GOTO_TOKEN){

        nextToken();

        if(SYM_COUR.CODE == ID_TOKEN)

            return TRUE;

    }

    return FALSE;

}



// 23 - procedure_call_or_assign_statement -> id ('(' params ')' | := expression) ;

boolean procedure_call_or_assign_statement(){
    
    if(debugSYNT)         
        printf("procedure_call_or_assign_statement\n");
    

    char currIDF[100];

    strcpy(currIDF, SYM_COUR.NOM);

    if(SYM_COUR.CODE == ID_TOKEN){

        nextToken();

        if(SYM_COUR.CODE == PO_TOKEN){
            
            int indice = verifIDexist(TPROC, currIDF);

            nextToken();

            if(params()){

                nextToken();

                if(strcmp(SYM_COUR.NOM, ")") == 0){

                    nextToken();

                    if(SYM_COUR.CODE == PV_TOKEN)

                        return TRUE;

                    else detectError(PV_ERR);

                }

            }

        }

        else{

            //affectation

            if(SYM_COUR.CODE == AFF_TOKEN){

                int indice = verifIDexist(TVAR, currIDF);

                GENERER2(LDA, TAB_IDFS[indice].ADRESSE);

                nextToken();
                
                if(expression()){

                    GENERER1(STO);

                    nextToken();


                    if(SYM_COUR.CODE == PV_TOKEN){

                        return TRUE;

                    }

                    else detectError(PV_ERR);

                }

            }
            else detectError(PO_ERR);
        }

    }
    else detectError(ID_ERR);

    return FALSE;

}

boolean char_func(){
    
    if(debugSYNT)         printf("char_func\n");
    if(SYM_COUR.CODE == APP_TOKEN){
        nextToken();
        if(SYM_COUR.CODE != APP_TOKEN && strlen(SYM_COUR.NOM) == 1)
            nextToken();
        else{
            return FALSE;
        }
        if(SYM_COUR.CODE == APP_TOKEN)
            return TRUE;
        else detectError(APP_ERR);
        
    }

    return FALSE;
}

boolean string_func(){
    
    if(debugSYNT)         printf(" string_func\n");
        
    if(SYM_COUR.CODE == DOUBLE_QUOTES_TOKEN){

        nextToken();
        
        while(SYM_COUR.CODE != DOUBLE_QUOTES_TOKEN)
        
            nextToken();
        
        if(SYM_COUR.CODE == DOUBLE_QUOTES_TOKEN)
        
            return TRUE;
        
        else detectError(DOUBLE_QUOTES_ERR);
    
    }

    return FALSE;
}



// 24 - params -> (expression | string_func | char_func) {, params}*

boolean params(){
    
    if(debugSYNT)         printf("params\n");

    if(strcmp(SYM_COUR.NOM, ")") == 0){
        follow_token = TRUE;
        return TRUE;
    }
    
    
    if(SYM_COUR.CODE == DOUBLE_QUOTES_TOKEN){
        
        if(string_func()){
        
            nextToken();

            while(SYM_COUR.CODE == VIR_TOKEN){

                nextToken();

                if(! params()){

                    return FALSE;

                }


                nextToken();


            }

            follow_token = TRUE;

            return TRUE;
        }
    }
    if(SYM_COUR.CODE == APP_TOKEN){
        
        if(char_func()){
        
            nextToken();

            while(SYM_COUR.CODE == VIR_TOKEN){

                nextToken();

                if(! params()){

                    return FALSE;

                }

                nextToken();

            }

            follow_token = TRUE;

            return TRUE;
        }
    }
    if(expression()){

        nextToken();

        while(strcmp(SYM_COUR.NOM, ",") == 0){

            nextToken();

            if(! params()){

                return FALSE;

            }

            nextToken();

        }

        follow_token = TRUE;

        return TRUE;

    }

    return FALSE;;

}



//25 - return_statement -> return [expression] ;



boolean return_statement(){
    
    if(debugSYNT)         printf("return_statement\n");

    if(SYM_COUR.CODE == RETURN_TOKEN){

        nextToken();

        if(SYM_COUR.CODE == PV_TOKEN)

            return TRUE;

        if(expression()){

            nextToken();

            if(SYM_COUR.CODE == PV_TOKEN)

                return TRUE;

            else detectError(PV_ERR);

        }

    }

    return FALSE;

}



//26 - compound_statement ::= if_statement | case_statement | loop_statement | block_statement



boolean compound_statement(){
    
    if(debugSYNT)         printf("compound_statement\n");

    if(SYM_COUR.CODE == IF_TOKEN){

        return if_statement();

    }

    else if(SYM_COUR.CODE == CASE_TOKEN){

        return case_statement();

    }

    else if(SYM_COUR.CODE == WHILE_TOKEN || SYM_COUR.CODE == FOR_TOKEN || SYM_COUR.CODE == LOOP_TOKEN){

        return loop_statement();

    }
    
    if(SYM_COUR.CODE == DECLARE_TOKEN || SYM_COUR.CODE == BEGIN_TOKEN ){
        boolean drap = block_statement();
        return drap;
    }

    return FALSE;

}



//27 - if_statement -> if expression then sequence_statement [elsif expression then sequence_statement]* [else sequence_statement] end if;



boolean if_statement(){
    
    if(debugSYNT)         printf("if_statement\n");


    int Indices[100];
    int len = 0;

    if(SYM_COUR.CODE == IF_TOKEN){

        nextToken();

        if(expression()){

            GENERER1(BZE);

            int ind_BZE = PC;
            
            nextToken();

            if(SYM_COUR.CODE == THEN_TOKEN){

                nextToken();

                if(sequence_statement()){

                    GENERER1(BRN);

                    Indices[len++] = PC + 1;

                    PCODE[ind_BZE].SUITE = PC + 1;
                                    
                    nextToken();

                    while(SYM_COUR.CODE == ELSIF_TOKEN){
            
                        nextToken();

                        if(expression()){

                        GENERER1(BZE);
                        
                        int ind_BZE1 = PC;

                            nextToken();

                            if(SYM_COUR.CODE == THEN_TOKEN){

                                nextToken();

                                if(sequence_statement()){

                                    GENERER1(BRN);

                                    Indices[len++] = PC + 1;

                                    PCODE[ind_BZE1].SUITE = PC + 1;

                                    nextToken();
                                
                                }

                                else

                                    return FALSE;

                            }

                            else{
                                detectError(THEN_ERR);
                                return FALSE;
                            }

                        }

                        else

                            return FALSE;

                    }

                    //SYM_COUR contains already the follow token. so, no need to call nextToken

                    if(SYM_COUR.CODE == ELSE_TOKEN){

                        nextToken();

                        if(sequence_statement()){

                            nextToken();

                        }

                        else

                            return FALSE;

                    }

                    if(SYM_COUR.CODE == END_TOKEN){

                        nextToken();

                        if(SYM_COUR.CODE == IF_TOKEN){

                            nextToken();

                            if(SYM_COUR.CODE == PV_TOKEN){
                                
                                for(int i = 0; i < len; i++){

                                    PCODE[Indices[i] - 1] . SUITE = PC + 1;
                                    
                                }
                                return TRUE;

                            }
                            else detectError(PV_ERR);

                        }
                        else detectError(IF_ERR);

                    }
                    else detectError(END_ERR);

                }

            }
            else detectError(THEN_ERR);

        }

    }

    return FALSE;

}





// 28 - case_statement -> case expression is case_statement_alt {case_statement_alt}* end case;



boolean case_statement(){
    
    if(debugSYNT)         printf("case_statement\n");

    first = TRUE;

    if(SYM_COUR.CODE == CASE_TOKEN) {

        nextToken();

        if(expression()){

            last_INDO = last_IND;

            nextToken();

            if(SYM_COUR.CODE == IS_TOKEN){

                nextToken();

                if(case_statement_alt()){

                    nextToken();

                    first = FALSE;

                    while(SYM_COUR.CODE == WHEN_TOKEN){ 

                        case_statement_alt();

                        nextToken();

                    }

                    if(SYM_COUR.CODE == OTHERS_TOKEN){
                        
                        nextToken();

                        if(!sequence_statement())

                            return FALSE;

                        nextToken();
                    }

                    if(SYM_COUR.CODE == END_TOKEN){

                        nextToken();

                        if(SYM_COUR.CODE == CASE_TOKEN){

                            nextToken();

                            if(SYM_COUR.CODE == PV_TOKEN){

                                return TRUE;

                            }
                            else detectError(PV_ERR);

                        }
                        else detectError(CASE_ERR);

                    }
                    else detectError(END_ERR);

                }

            }
            else detectError(IS_ERR);

        }

    }

    return FALSE;

}



// 29 - case_statement_alt -> when Simple_expression => sequence_statement



boolean case_statement_alt(){
    
    if(debugSYNT)         printf("case_statement_alt\n");

    if(SYM_COUR.CODE == WHEN_TOKEN){

        nextToken();
        
        if(SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN || SYM_COUR.CODE == NULL_TOKEN || SYM_COUR.CODE == STRING_TOKEN || SYM_COUR.CODE == ID_TOKEN || SYM_COUR.CODE == NUM_TOKEN || SYM_COUR.CODE == PO_TOKEN){
                
                if(!first){

                    GENERER2(LDA, TAB_IDFS[last_INDO].ADRESSE);
                    
                    GENERER1(LDV);
                }

            if(simple_expression()){


                GENERER1(EQL);

                GENERER1(BZE);
                
                int id = PC;
                
                nextToken();

                if(SYM_COUR.CODE == EGAL_TOKEN){

                    nextToken();

                    if(SYM_COUR.CODE == SUP_TOKEN){

                        nextToken();

                        if(sequence_statement()){

                            PCODE[id].SUITE = PC + 1;

                            return TRUE;

                        }

                    }
                    else detectError(SUP_ERR);

                }
                else detectError(EGAL_ERR);

            // TODO Others

            }

        }



  }

   return FALSE;

}



// 30 -  loop_statement -> [(while expression

//                              |

//                          for id in [reverse] simple_expression .. simple_expression)]

//      loop sequence_statement end loop;



boolean loop_statement(){

    boolean drapFOR = FALSE;
    boolean drap = FALSE;
    
    if(debugSYNT)         printf("loop_statement\n");

    int ind_BZE = 0;

    int LABEL_BRN = 0;

    int index = 0;

    int ind_br = 0;

    int ind_bn = 0;

    if(SYM_COUR.CODE == WHILE_TOKEN){

        LABEL_BRN = PC + 1;

        nextToken();

        if(!expression())

            return FALSE;
        
        GENERER1(BZE);
        
        ind_BZE = PC;

    }

    else if(SYM_COUR.CODE == FOR_TOKEN){

        drapFOR = TRUE;

        nextToken();

        if(SYM_COUR.CODE == ID_TOKEN){

            index = verifIDexist(TVAR, SYM_COUR.NOM);

            nextToken();

            if(SYM_COUR.CODE == IN_TOKEN){

                nextToken();

                if(SYM_COUR.CODE == REVERSE_TOKEN){

                    drap = TRUE;

                    nextToken();

                }

                ind_bn = PC + 1;

                GENERER2(LDA, TAB_IDFS[index].ADRESSE);
                
                GENERER1(LDV);

                if(simple_expression()){

                    if(!drap)
                        GENERER1(GEQ);
                    else
                        GENERER1(LEQ);

                    nextToken();

                    if(SYM_COUR.CODE == PT_TOKEN){

                        nextToken();

                        if(SYM_COUR.CODE == PT_TOKEN){

                            nextToken();

                            GENERER2(LDA, TAB_IDFS[index].ADRESSE);
            
                            GENERER1(LDV);

                            if(!simple_expression())

                                return FALSE;

                            else{

                                if(!drap)
                                
                                    GENERER1(LEQ);
                                
                                else
                                
                                    GENERER1(GEQ);

                                GENERER1(AND);

                                GENERER1(BZE);

                                ind_br = PC + 1;
                            }
                        }

                        else{

                            detectError(PO_ERR);
                            return FALSE;
                    
                        }

                    }

                    else{

                        detectError(PO_ERR);
                        return FALSE;
                    
                    }
                }

                else

                    return FALSE;

            }

            else{

                detectError(IN_ERR);
                return FALSE;
            
            }
        }

        else{

            detectError(ID_ERR);
            return FALSE;

        }

    }

    nextToken();

    if(SYM_COUR.CODE == LOOP_TOKEN){

        nextToken();

        if(sequence_statement()){

            if(!drapFOR){
                
                GENERER2(BRN, LABEL_BRN);

                PCODE[ind_BZE] . SUITE = PC + 1;
            }

            nextToken();

            if(drapFOR){

                GENERER2(LDA, TAB_IDFS[index].ADRESSE);

                GENERER2(LDA, TAB_IDFS[index].ADRESSE);

                GENERER1(LDV);

                GENERER2(LDI, drap?-1:1);

                GENERER1(ADD);

                GENERER1(STO);

                GENERER2(BRN, ind_bn);

                PCODE[ind_br - 1].SUITE = PC + 1;
            }

            if(SYM_COUR.CODE == END_TOKEN){

                nextToken();

                if(SYM_COUR.CODE == LOOP_TOKEN){

                    nextToken();

                    if(SYM_COUR.CODE == PV_TOKEN)

                        return TRUE;
                    
                    else detectError(PV_ERR);

                }
                else detectError(LOOP_ERR);

            }
            else detectError(END_ERR);

        }

    }
    else detectError(LOOP_ERR);

    return FALSE;

}


//31 - block_statement -> [declare (basic_declaration)*]

//                   begin

//                      sequence_statement

//                    end;



boolean block_statement(){
    
    if(debugSYNT)         printf("block_statement\n");


    if(SYM_COUR.CODE == DECLARE_TOKEN){

        nextToken();

        while(SYM_COUR.CODE == TYPE_TOKEN || SYM_COUR.CODE == ID_TOKEN ){

            if(!basic_declaration()) return FALSE;

            nextToken();

        }

    }

    if( SYM_COUR.CODE == BEGIN_TOKEN){


        nextToken();

        if(sequence_statement()){

            nextToken();

            if( SYM_COUR.CODE == END_TOKEN){

                nextToken();


                if( SYM_COUR.CODE == PV_TOKEN){

                    return TRUE;

                }
                else{
                    detectError(PV_ERR);
                    return FALSE;
                }

            }
            else detectError(END_ERR);

        }

    }

    else detectError(BEGIN_ERR);

    return FALSE;

}



// 32 - expression -> relation [(and| or | xor) relation]*

boolean expression(){
    
    if(debugSYNT)         printf("expression\n");

    if( relation()) {

        nextToken();

        while( SYM_COUR.CODE == AND_TOKEN || SYM_COUR.CODE == OR_TOKEN || SYM_COUR.CODE == XOR_TOKEN ){

            Token temp = SYM_COUR;

            nextToken();

            if( !relation()) return FALSE;

            switch((int)temp . CODE){
                case(AND_TOKEN) : {
                    GENERER1(AND);
                    break;
                }
                case(OR_TOKEN) : {
                    GENERER1(OR);
                    break;
                }
                case(XOR_TOKEN) : {
                    GENERER1(XOR);
                    break;
                }
            }

            nextToken();

        }

        follow_token = TRUE;

        return TRUE;

    }

    return FALSE;

}



// 33 - relation -> simple_expression [     ( = | *= | /= | < | <= | > |>= )  simple_expression

//                                      |

                    //                      (not | in) NUM_TOKEN .. NUM_TOKEN

//                                    ]

boolean relation(){
    
    if(debugSYNT)         printf("relation\n");

    if( simple_expression() ){

        nextToken();

        if( SYM_COUR.CODE == EGAL_TOKEN || SYM_COUR.CODE == MULT_AFFEC_TOKEN || SYM_COUR.CODE == DIV_AFFEC_TOKEN 
        || SYM_COUR.CODE == INF_TOKEN || SYM_COUR.CODE == INFEG_TOKEN || SYM_COUR.CODE == SUP_TOKEN || SYM_COUR.CODE == SUPEG_TOKEN ){

            Token temp = SYM_COUR;

            nextToken();
            
            boolean drap = simple_expression();

            switch((int)temp . CODE){
                case(EGAL_TOKEN) : {
                    GENERER1(EQL);
                    break;
                }
                case(MULT_AFFEC_TOKEN) : {
                    GENERER1(MULT_AFFEC);
                    break;
                }
                case(DIV_AFFEC_TOKEN) : {
                    GENERER1(NEQ);
                    break;
                }
                case(INF_TOKEN) : {
                    GENERER1(LSS);
                    break;
                }
                case(INFEG_TOKEN) : {
                    GENERER1(LEQ);
                    break;
                }
                case(SUP_TOKEN) : {
                    GENERER1(GTR);
                    break;
                }
                case(SUPEG_TOKEN) : {
                    GENERER1(GEQ);
                    break;
                }
                
            }

            return drap;

        }

        if ( SYM_COUR.CODE == NOT_TOKEN || SYM_COUR.CODE == IN_TOKEN ) {

            nextToken();

            if( SYM_COUR.CODE == NUM_TOKEN){

                nextToken();

                if( SYM_COUR.CODE == PT_TOKEN){

                    nextToken();

                    if( SYM_COUR.CODE == PT_TOKEN){

                        nextToken();

                        if( SYM_COUR.CODE == NUM_TOKEN){

                            return TRUE;

                        }
                        else{
                            detectError(NUM_ERR);
                            return FALSE;
                        }

                    }
                    else{
                        detectError(DOUBLE_POINT_ERR);
                        return FALSE;
                    }
                }
                else{
                    detectError(DOUBLE_POINT_ERR);
                    return FALSE;
                }

            }
            else{
                detectError(NUM_ERR);
                return FALSE;
            }

        }

        follow_token = TRUE;

        return TRUE;

    }

    return FALSE;

}





// 34 - simple_expression -> [+ | -] term { (+ | - | &) term }*

boolean simple_expression(){
    
    if(debugSYNT)         printf("simple_expression\n");

    if ( SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN ){
        if(SYM_COUR.CODE == MOINS_TOKEN)
            drapMINUS = TRUE;
        nextToken();

    }

    if( term()){

        nextToken();

        while( SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN || SYM_COUR.CODE == EC_TOKEN ){

            Token temp = SYM_COUR;

            nextToken();



            if( !simple_expression()) return FALSE;

            switch((int)temp . CODE){
                case(PLUS_TOKEN) : {
                    GENERER1(ADD);
                    break;
                }
                case(MOINS_TOKEN) : {
                    GENERER1(SUB);
                    break;
                }
                case(EC_TOKEN) : {
                    GENERER1(AND);
                    break;
                }            
            }
            nextToken();

        }   

        follow_token = TRUE;

        return TRUE;

    }

    return FALSE;

}



// 35 - term  -> factor {(* | / | mod | rem | **) factor}*

boolean term(){if(debugSYNT)         printf("term\n");

    if( factor()){

        nextToken();

        while( SYM_COUR.CODE == MULT_TOKEN || SYM_COUR.CODE == DIV_TOKEN || SYM_COUR.CODE == MOD_TOKEN){

            Token temp = SYM_COUR;

            if(SYM_COUR.CODE == MULT_TOKEN){
                nextToken();
                if(SYM_COUR.CODE == MULT_TOKEN){
                    nextToken();
                }
            }
            else
                nextToken();
            
            

            if( !simple_expression()) return FALSE;


            switch((int)temp . CODE){
                case(MULT_TOKEN) : {
                    GENERER1(MUL);
                    break;
                }
                case(DIV_TOKEN) : {
                    GENERER1(DIV);
                    break;
                }
                case(MOD_TOKEN) : {
                    GENERER1(MOD);
                    break;
                }            
            }

            nextToken();

        }

        follow_token = TRUE;

        return TRUE;

    }

    return FALSE;

}

// 36 - factor -> primary 

        // | abs primary

        // |not primary

        // | - primary

        // | + primary


boolean factor(){
    
    if(debugSYNT)         printf("factor\n");

    if( SYM_COUR.CODE == ABS_TOKEN || SYM_COUR.CODE == NOT_TOKEN || SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN){
        nextToken();
    }
        
    return primary();
}



// 37 - primary -> NULL_TOKEN | STRING_TOKEN | id | NUM_TOKEN | FLOAT_TOKEN  | '(' expression ')'
   
boolean primary(){
    
    if(debugSYNT)         
        
        printf("primary\n");

    char currIDF[100];

    if ( SYM_COUR.CODE == NULL_TOKEN || SYM_COUR.CODE == STRING_TOKEN || SYM_COUR.CODE == ID_TOKEN || SYM_COUR.CODE == NUM_TOKEN || SYM_COUR.CODE == TRUE_TOKEN ||  SYM_COUR.CODE == FALSE_TOKEN || SYM_COUR.CODE == FLOAT_TOKEN){
        
        if(SYM_COUR.CODE == ID_TOKEN){
            
            strcpy(currIDF, SYM_COUR.NOM);

            nextToken();
            
            if(SYM_COUR.CODE == APP_TOKEN){

                nextToken();
                
                if(SYM_COUR.CODE == FIRST_TOKEN || SYM_COUR.CODE == LAST_TOKEN){
                    
                    return TRUE;
                
                }
                
                else return FALSE;
            
            }
            else{
                if(SYM_COUR.CODE == PO_TOKEN){

                verifIDexist(TFUNC, currIDF);
            
                nextToken();

                if(params()){

                    nextToken();

                    if(strcmp(SYM_COUR.NOM, ")") == 0){            

                            return TRUE;

                        }
                        else{
                            detectError(PF_ERR);
                            return FALSE;
                        }
                    }
                    else
                        return FALSE;
                }
                else{

                    int indice = verifIDexist(TBOTH, currIDF);

                    last_IND = indice;
                    
                    GENERER2(LDA, TAB_IDFS[indice].ADRESSE);
                    
                    GENERER1(LDV);
                    
                    follow_token = TRUE;
                    
                    return TRUE;
                }
            }
        
        }

        if(SYM_COUR.CODE == NUM_TOKEN || SYM_COUR.CODE == FLOAT_TOKEN){

            GENERER2(LDI, (drapMINUS? -1:1) * atoi(SYM_COUR.NOM));

            drapMINUS = FALSE;

        }

        if(SYM_COUR.CODE == TRUE_TOKEN){
            GENERER2(LDI, 1);
        }
        if(SYM_COUR.CODE == FALSE_TOKEN){
            GENERER2(LDI, 0);
        }

        return TRUE;

    }

    else if( SYM_COUR.CODE == PO_TOKEN ){

        nextToken();

        if ( expression() ){

            nextToken();

            if( SYM_COUR.CODE == PF_TOKEN ){

                return TRUE;

            }

        }

    }

    return FALSE;

}



//pragma ::= pragma identifier [(pragma_argument_association {, pragma_argument_association})];

boolean pragma(){
    if(debugSYNT)         printf("pragma\n");
    if(SYM_COUR.CODE == PRAGMA_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == ID_TOKEN){
            nextToken();
            if(SYM_COUR.CODE == PV_TOKEN)
                return TRUE;
            if(pragma_argument_association()){
                nextToken();
                while(SYM_COUR.CODE == VIR_TOKEN){
                    if(!pragma_argument_association())
                        return FALSE;
                    nextToken();
                }
                if(SYM_COUR.CODE == PV_TOKEN)
                return TRUE;
            }
        }
    }
    return FALSE;
}

// pragma_argument_association ::= [id =>] expression

boolean pragma_argument_association(){
    if(debugSYNT)         printf("pragma_argument_association\n");
    if(SYM_COUR.CODE == ID_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == EGAL_TOKEN){
            nextToken();
            if(SYM_COUR.CODE == SUP_TOKEN){
                nextToken();
                if(expression()){
                    return TRUE;
                }
            }
        }
        else{
            follow_token = TRUE;
            return expression();
        }
    }
    return FALSE;
}

// package_body ::= package package_body_aux
boolean package_body(){
    
    if(debugSYNT)         printf("package_body\n");

    if ( SYM_COUR.CODE == PACKAGE_TOKEN){
        nextToken();
        return package_body_aux();
    }

    return FALSE;
}


// package_body_aux ::= body package_body_adb | package_body_ads
boolean package_body_aux(){
    if(debugSYNT)         printf("package_body_aux\n");
    if( SYM_COUR.CODE == BODY_TOKEN){
        nextToken();
        return package_body_adb();
    } else{
        return package_body_ads();
    }
    return FALSE;
}

// package_body_adb ::= IDF
//             [ refinement_definition ]
//               is
//                 package_implementation
//               end IDF;
boolean package_body_adb(){
    if(debugSYNT)         printf("package_body_adb\n");
    if( SYM_COUR.CODE == ID_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == WITH_TOKEN){
            if (!refinement_definition()) return FALSE;
            nextToken();
        }
        if( SYM_COUR.CODE == IS_TOKEN){
            nextToken();
            if( package_implementation() ){
                nextToken();
                if( SYM_COUR.CODE == END_TOKEN){
                    nextToken();
                    if( SYM_COUR.CODE == ID_TOKEN) {
                        nextToken();
                        if( SYM_COUR.CODE == PV_TOKEN){
                            return TRUE;
                        }
                        else detectError(PV_ERR);
                    }
                    else detectError(ID_ERR);
                }
                else detectError(END_ERR);
            }
        }
        else detectError(IS_ERR);
    }
    detectError(ID_ERR);
    return FALSE;
}


// *  refinement_definition :: with IDF;

boolean refinement_definition(){
        if(debugSYNT)         printf("refinement_definition\n");

    if( SYM_COUR.CODE == WITH_TOKEN){
        nextToken();
        if( SYM_COUR.CODE == ID_TOKEN){
            nextToken();
            if( SYM_COUR.CODE == PV_TOKEN){
                return TRUE;   
            }
            else detectError(PV_ERR);
        }
        else detectError(ID_ERR);
    }
    return FALSE;
}


//  * package_implementation ::=
//               declarative_part
//               begin
//                    sequence_of_statements <=============== attention
boolean package_implementation(){
        if(debugSYNT)         printf("package_implementation\n");
        while (SYM_COUR.CODE == TYPE_TOKEN || SYM_COUR.CODE == ID_TOKEN || SYM_COUR.CODE == FUNCTION_TOKEN || SYM_COUR.CODE == PROCEDURE_TOKEN){
            if(!basic_declaration()) return FALSE;
                
            nextToken();
        }
        if( SYM_COUR.CODE == BEGIN_TOKEN){
            nextToken();
        
            if( sequence_statement()){
                return TRUE;   
            }
        }
        else{
            follow_token = TRUE;
            return TRUE;
        }
        return FALSE;
    }

// * package_body_ads ::= IDF
//             [ refinement_definition ]
//               is
//                 declarative_part
//               end IDF;
boolean package_body_ads(){
    
    if(debugSYNT)         printf("package_body_ads\n");

    if( SYM_COUR.CODE == ID_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == WITH_TOKEN){
            if (!refinement_definition()) return FALSE;
            nextToken();
        }
        if( SYM_COUR.CODE == IS_TOKEN){

            while (SYM_COUR.CODE == TYPE_TOKEN || SYM_COUR.CODE == ID_TOKEN || SYM_COUR.CODE == FUNCTION_TOKEN || SYM_COUR.CODE == PROCEDURE_TOKEN){

                if(!basic_declaration()) return FALSE;
                
                nextToken();
            }
            
            if( SYM_COUR.CODE == END_TOKEN){
                nextToken();
                if( SYM_COUR.CODE == ID_TOKEN) {
                    nextToken();
                    if( SYM_COUR.CODE == PV_TOKEN){
                        return TRUE;
                    }
                    else detectError(PV_ERR);
                }
                else detectError(ID_ERR);
            }
            else detectError(END_ERR);
        }
        else detectError(IS_ERR);
    }
    else detectError(ID_ERR);
    return FALSE;
}

// main_program -> list_with_use_clause [package_body | sub]

boolean main_program(){
    
    if(debugSYNT)         printf("main_program\n");


    boolean result = FALSE;

    while(SYM_COUR.CODE == USE_TOKEN || SYM_COUR.CODE == WITH_TOKEN){

        with_use_clause();

        nextToken();

    }
    if(SYM_COUR.CODE == PACKAGE_TOKEN){
        if(package_body()){
            GENERER1(HLT);
            return TRUE;
        }
    }
    else{
        if(subprogram_body()){
            GENERER1(HLT);
            return TRUE;
        }
    }
    return FALSE;
}


boolean print(){
    if(debugLEX)
        printf("print\n");

    // ECRIRE ::= print ( EXPR { , EXPR } );
    if(PRINT_TOKEN != SYM_COUR.CODE)
        return FALSE;
    nextToken();
    if(PO_TOKEN != SYM_COUR.CODE){
        detectError(PO_ERR);
        return FALSE;
    }
    nextToken();
    if(!expression())
        return FALSE;
    GENERER1(PRN);
    nextToken();
    while(SYM_COUR.CODE == VIR_TOKEN){
        nextToken();
        if(!expression())
        return FALSE;
        GENERER1(PRN);
        nextToken();
    }
    if(PF_TOKEN != SYM_COUR.CODE){
        detectError(PF_ERR);
        return FALSE;
    }
    nextToken();
    if(PV_TOKEN != SYM_COUR.CODE){
        detectError(PV_ERR);
        return FALSE;
    }
    return TRUE;
}

boolean read(){
    if(debugLEX)
        printf("READ\n");
    // LIRE ::= read ( ID { , ID } );
    if(READ_TOKEN != SYM_COUR.CODE)
        return FALSE;
    
    nextToken();
    if(PO_TOKEN != SYM_COUR.CODE){
        detectError(PO_ERR);
        return FALSE;
    }
    
    nextToken();

    if(ID_TOKEN != SYM_COUR.CODE){
        detectError(PO_ERR);
        return FALSE;
    }

    int indice = verifIDexist(TVAR, SYM_COUR.NOM);

    GENERER2(LDA, TAB_IDFS[indice].ADRESSE);

    GENERER1(INN);

    nextToken();

    while(SYM_COUR.CODE == VIR_TOKEN){
        nextToken();
        if(ID_TOKEN != SYM_COUR.CODE){
            detectError(ID_ERR);
            return FALSE;
        }
        int ind = verifIDexist(TVAR, SYM_COUR.NOM);
        GENERER2(LDA, TAB_IDFS[ind].ADRESSE);
        GENERER1(INN);
        nextToken();
    }

    if(PF_TOKEN != SYM_COUR.CODE){
        detectError(PF_ERR);
        return FALSE;
    }
    nextToken();
    if(PV_TOKEN != SYM_COUR.CODE){
        detectError(PV_ERR);
        return FALSE;
    }
    return TRUE;
}


