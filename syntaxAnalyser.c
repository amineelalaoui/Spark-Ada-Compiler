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
boolean list_basic_declaration();
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

int main(int argc, char* argv[]){
  /**  if (!argv[1]) {
        printf("fichier n'exste pas\n");
        exit(EXIT_FAILURE);
    }*/
    fl = fopen("TESTCASE/for.ada", "r");
    nextToken();
    if(list_with_use_clause()){
        printf("YEEES\n");
    }
    else
        printf("NOOO\n");
    fclose(fl);
    return 0;
}


// integer_type_definition -> range T_NUMERIC .. T_NUMERIC | mod expression

// 9 - enumeration_type_definition ->'(' (id|char) [ , (id|char)]*  ')'

boolean enumeration_type_definition(){
    if(SYM_COUR.CODE == PO_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == ID_TOKEN){
            nextToken();
            while(SYM_COUR.CODE == VIR_TOKEN){
                nextToken();
                if(SYM_COUR.CODE != ID_TOKEN)
                    return false;
                nextToken();
            }
            if(SYM_COUR.CODE == PF_TOKEN)
                return true;
        }
    }
    return false;
}

//2_2 - multiple_id -> .id multiple_id | epsilon
//FIRST = (.);
//FOLLOW = USE ID PROCEDURE FUNCTION

boolean multiple_id(){
    boolean result = FALSE;
    if (SYM_COUR.CODE == USE_TOKEN ||
        SYM_COUR.CODE == WITH_TOKEN ||
        SYM_COUR.CODE == PROCEDURE_TOKEN ||
        SYM_COUR.CODE == FUNCTION_TOKEN){
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
    }
    return result;
}

//2_1 with_use_clause -> (use | with) id multiple_id

boolean with_use_clause(){
    boolean result = FALSE;
    if(SYM_COUR.CODE == USE_TOKEN ||
        SYM_COUR.CODE == WITH_TOKEN){
		nextToken();
		if(SYM_COUR.CODE == ID_TOKEN){
            nextToken();
            if(multiple_id()){
                result = TRUE;
            }
        }
    }

	return result;
}

//1_2 - list_with_use_clause -> with_use_clause list_with_use_clause | epsilon
//FIRST = (use, with)
//FOLLOW = (procedure, function)
//VV
boolean list_with_use_clause(){
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


//4 - subprogram_specification -> procedure id ['(' formal_part ')'] | function id ['(' formal_part ')'] return id

boolean subprogram_specification(){
    boolean result = false;
    if(SYM_COUR.CODE == FUNCTION_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == ID_TOKEN){
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
                                result = true;
                            }
                        }
                    }
                }
            }
            else{
                if(SYM_COUR.CODE == RETURN_TOKEN){
                    nextToken();
                    if(SYM_COUR.CODE == ID_TOKEN){
                        result = true;
                    }
                }
            }
        }
    }
    else{
        if(SYM_COUR.CODE == PROCEDURE_TOKEN){
            nextToken();
            if(SYM_COUR.CODE == ID_TOKEN){
                nextToken();
                if(SYM_COUR.CODE == PO_TOKEN){
                    nextToken();
                    if(formal_part()){
                        nextToken();
                        if(SYM_COUR.CODE == PF_TOKEN){
                            result = true;
                        }
                    }
                }
                else{
                    result = true;
                    follow_token = true;
                }
            }
        }
    }
    return result;
}

//8 - type_declaration -> type id is (enumeration_type_definition | integer_type_definition | real_type_definition | array_type_definition);

boolean type_declaration(){
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
                            return true;
                        else
                            return false;
                    }
                }
                if(SYM_COUR.CODE == RANGE_TOKEN){
                    if(integer_type_definition()){
                        nextToken();
                        if(SYM_COUR.CODE == PV_TOKEN)
                            return true;
                        else
                            return false;
                    }
                }
                if(SYM_COUR.CODE == DIGITS_TOKEN){
                    if(real_type_definition()){
                        nextToken();
                        if(SYM_COUR.CODE == PV_TOKEN)
                            return true;
                        else
                            return false;
                    }
                }
                if(SYM_COUR.CODE == ARRAY_TOKEN){
                    if(array_type_definition()){
                        nextToken();
                        if(SYM_COUR.CODE == PV_TOKEN)
                            return true;
                        else
                            return false;
                    }
                }
            }
        }
    }
    return false;
}

// 6 - parameter_specification -> id : [in | out] id [:= expression]

boolean parameter_specification(){
    if(SYM_COUR.CODE == ID_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == DOUBLE_POINT_TOKEN){
            nextToken();
            if(SYM_COUR.CODE == IN_TOKEN || SYM_COUR.CODE == OUT_TOKEN){
                nextToken();
            }
            if(SYM_COUR.CODE == ID_TOKEN){
                nextToken();
                if(SYM_COUR.CODE == VIR_TOKEN || SYM_COUR.CODE == PF_TOKEN){
                    follow_token = true;
                    return true;
                }
                if(SYM_COUR.CODE == DOUBLE_POINT_TOKEN){
                    nextToken();
                    if(SYM_COUR.CODE == EGAL_TOKEN){
                        nextToken();
                        if(expression())
                            return true;
                    }
                }
            }
        }
    }
    return false;
}
// 5_2 other_parameter_specification -> , parameter_specification other_parameter_specification | epsilon
//FOLLOW )

boolean other_parameter_specification(){
    if(SYM_COUR.CODE == PF_TOKEN){
        follow_token = true;
        return true;
    }
    if(SYM_COUR.CODE == VIR_TOKEN){
        nextToken();
        if(parameter_specification()){
            nextToken();
            if(other_parameter_specification())
                return true;
        }
    }

}

//5_1 - formal_part -> parameter_specification other_parameter_specification

boolean formal_part(){
    if(parameter_specification()){
        nextToken();
        if(other_parameter_specification()){
            return true;
        }
    }
    return false;
}


// 8 - basic_declaration -> type_declaration | object_number_declaration

boolean basic_declaration(){
    boolean result = false;
    if(SYM_COUR.CODE == TYPE_TOKEN){
        if(type_declaration()){
            result = true;
        }
    }
    if(SYM_COUR.CODE == ID_TOKEN){
        if(object_number_declaration()){
            result = true;
        }
    }
    return result;
}

// 3_2 list_basic_declaration -> basic_declaration list_basic_declaration | epsilon
//FIRST = type, id
//FOLLOW = begin

boolean list_basic_declaration(){
    boolean result = FALSE;
    if (SYM_COUR.CODE == BEGIN_TOKEN){
        follow_token = TRUE;
        result = TRUE;
    }
    else if(basic_declaration()){
        nextToken();
        if(list_basic_declaration()){
            result = TRUE;
        }
    }
    return result;
}


// 3_1 subprogram_body -> subprogram_specification is list_basic_declaration begin sequence_statement end [id];

boolean subprogram_body(){
    boolean result = false;
    if(subprogram_specification()){
        nextToken();
        if(SYM_COUR.CODE == IS_TOKEN){
            nextToken();
            if(list_basic_declaration()){
                nextToken();
                if(SYM_COUR.CODE == BEGIN_TOKEN){
                    nextToken();
                    if(sequence_statement()){
                        nextToken();
                        if(SYM_COUR.CODE == END_TOKEN){
                            nextToken();
                            if(SYM_COUR.CODE == PV_TOKEN)
                                result = true;
                            else{
                                if(SYM_COUR.CODE == ID_TOKEN){
                                    nextToken();
                                    if(SYM_COUR.CODE == PV_TOKEN)
                                        result = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}

//1_1 - program -> list_with_use_clause subprogram_body 
// VV
boolean program(){
    boolean result = FALSE;
    if(list_with_use_clause()){
		nextToken();
		if(subprogram_body()){
			result=TRUE;
		}
    }

	return result;
}

//10 - integer_type_definition -> range expression .. expression | mod expression

boolean integer_type_definition(){
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
            }
        }
    }
    else if(SYM_COUR.CODE == MODE_TOKEN){
        nextToken();
            if(expression())
                result = TRUE;
    }
    return result;
}


//11 - real_type_definition -> digit expression [range expression .. expression]

boolean real_type_definition(){
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
                                return true;
                            }
                        }
                    }
                }
            }
            else{
                follow_token = true;
                return true;
            }
        }
    }
    return false;
}

//12 - array_type_definition -> array '(' id [range (<> | T_NUMERIC .. T_NUMERIC)] ')' of id

boolean array_type_definition(){
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
                                    return false;
                            }
                            else
                                return false;
                        }
                        else
                            return false;
                    }
                    else
                        return false; 
                }
                if(SYM_COUR.CODE == PF_TOKEN){
                    nextToken();
                    if(SYM_COUR.CODE == OF_TOKEN){
                        nextToken();
                        if(SYM_COUR.CODE == ID_TOKEN)
                            result = true;
                    }
                }
            }
        }
    }
    return result;
}

//record_type_definition -> null record; | record component_list end record
boolean record_type_definition(){
    if(SYM_COUR.CODE == NULL_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == RECORD_TOKEN){
            nextToken();
            if(SYM_COUR.CODE == PV_TOKEN){
                return true;
            }
        }
    }
    else{
        if(SYM_COUR.CODE == RECORD_TOKEN){
            nextToken();
            if(component_list()){
                nextToken();
                if(SYM_COUR.CODE == END_TOKEN){
                    nextToken();
                    if(SYM_COUR.CODE == RECORD_TOKEN){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
// 14 - component_list -> component_item [component_item]* | null ;
boolean component_list(){
    if(component_item()){
        nextToken();
        while(component_item()){
            nextToken();
        }
        follow_token = true;
        return true;
    }
    else{
        if(SYM_COUR.CODE == NULL_TOKEN){
            return true;
        }
    }
    return false;
}

//15 - component_item -> id : id [:= expression]
boolean component_item(){
    if(SYM_COUR.CODE == ID_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == DOUBLE_POINT_TOKEN){
            nextToken();
            if(SYM_COUR.CODE == ID_TOKEN){
                nextToken();
                if(SYM_COUR.CODE == AFF_TOKEN){
                    nextToken();
                    if(expression)
                        return true;
                }
                else{
                    follow_token = true;
                    return true;
                }
            }
        }
    }
    return false;
}

//16 - object_number_declaration -> id [,id]* : constant := expression;
boolean object_number_declaration(){
    if(SYM_COUR.CODE == ID_TOKEN){
        nextToken();
        while(SYM_COUR.CODE == VIR_TOKEN){
            nextToken();
            if(!SYM_COUR.CODE == VIR_TOKEN){
                return false;
            }
            nextToken();
        }
        if(SYM_COUR.CODE == DOUBLE_POINT_TOKEN){
            nextToken();
            if(SYM_COUR.CODE == CONSTANT_TOKEN){
                nextToken();
                if(SYM_COUR.CODE == AFF_TOKEN){
                    nextToken();
                    if(expression()){
                        nextToken()   
                        if(SYM_COUR.CODE == PV_TOKEN)
                            return true;
                    }                   
                }
            }
        }
    }
    return false;
}

// 17 - sequence_statement -> statement {statement}*
boolean sequence_statement(){
    if(statement()){
        nextToken();
        while(statement()){
            nextToken();
        }
        follow_token = TRUE;
        return true;
    }
    return false;
}

//18 - statement -> simple_statement | compound_statement
boolean statement(){
    if(SYM_COUR.CODE == IF_TOKEN || SYM_COUR.CODE == CASE_TOKEN || SYM_COUR.CODE == WHILE_TOKEN ||
        SYM_COUR.CODE == LOOP_TOKEN || SYM_COUR.CODE == DECLARE_TOKEN || SYM_COUR.CODE == BEGIN_TOKEN){
        return compound_statement();       
    }
    return simple_statement();
}

//19 - simple_statement ::= null_statement | procedure_call_or_assign_statement | exit_statement | goto_statement | return_statement

boolean simple_statement(){
    //null_statement
    if(SYM_COUR.CODE == NULL_TOKEN){
        return true;
    }
    //procedure_call_or_assign_statement
    if(SYM_COUR.CODE == ID_TOKEN){
        return procedure_call_or_assign_statement();
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
    return false;
}

//20 - null_statement -> null ;
boolean null_statement(){
    if(SYM_COUR.CODE == NULL_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == PV_TOKEN)
            return TRUE;
    }
    return FALSE;
}

//21 - exit_statement -> exit [id] [when expression];
boolean exit_statement(){
    if(SYM_COUR.CODE == EXIT_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == ID_TOKEN){
            nextToken();
            if(SYM_COUR.CODE == WHEN_TOKEN){
                nextToken();
                if(expression()){
                    nextToken();
                    if(SYM_COUR.CODE == PV_TOKEN){
                        return true;
                    }
                }
            }
            else{
                if(SYM_COUR.CODE == PV_TOKEN){
                        return true;
                }
            }
        }
        else if(SYM_COUR.CODE == WHEN_TOKEN){
                nextToken();
                if(expression()){
                    nextToken();
                    if(SYM_COUR.CODE == PV_TOKEN){
                        return true;
                    }
                }
            }
        else if(SYM_COUR.CODE == PV_TOKEN){
                        return true;
        }
    }
    return false;
}

//22- goto_statement -> goto id;
boolean goto_statement(){
    if(SYM_COUR.CODE == GOTO_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == ID_TOKEN)
            return TRUE;
    }
    return FALSE;
}

// 23 - procedure_call_or_assign_statement -> id ('(' params ')' | := expression) ;
boolean procedure_call_or_assign_statement(){
    if(SYM_COUR.CODE == ID_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == PO_TOKEN){
            nextToken();
            if(params()){
                nextToken();
                if(SYM_COUR.CODE == PF_TOKEN){
                    nextToken();
                    if(SYM_COUR.CODE == PV_TOKEN)
                        return true;
                }
            }
        }
        else{
            //affectation
            if(SYM_COUR.CODE == AFF_TOKEN){
                nextToken();
                if(expression()){
                    nextToken();
                    if(SYM_COUR.CODE == PV_TOKEN){
                        return true;
                    }
                }
            }
        } 
    }
    return false;
}

// 24 - params -> [id =>] expression {, params}*
boolean params(){
    if(SYM_COUR.CODE == ID_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == EGAL_TOKEN ){
            nextToken();
            if(SYM_COUR.CODE == SUP_TOKEN ){
                nextToken();
            }
            else return false;
        }
        else follow_token = true;
    }
    if(expression()){
        nextToken();
        while(SYM_COUR.CODE == VIR_TOKEN){
            nextToken();
            if(! params()){
                return false;
            }
            nextToken();
        }
        follow_token = true;
        return true;
    }
    return false;;
}

//25 - return_statement -> return [expression] ;

boolean return_statement(){
    if(SYM_COUR.CODE == RETURN_TOKEN){
        next_token();
        if(SYM_COUR.CODE == PV_TOKEN)
            return true;
        if(expression()){
            next_token();
            if(SYM_COUR.CODE == PV_TOKEN)
                return true;
        }
    }
    return false;
}

//26 - compound_statement ::= if_statement | case_statement | loop_statement | block_statement

boolean compound_statement(){
    if(SYM_COUR.CODE == IF_TOKEN){
        return if_statement();
    }
    else if(SYM_COUR.CODE == CASE_TOKEN){
        return case_statement();
    }
    else if(SYM_COUR.CODE == WHILE_TOKEN || SYM_COUR.CODE == FOR_TOKEN || SYM_COUR.CODE == LOOP_TOKEN){
        return loop_statement();
    }
    else if(SYM_COUR.CODE == DECLARE_TOKEN || SYM_COUR.CODE == BEGIN_TOKEN ){
        return block_statement();
    }
    return false;
}

//27 - if_statement -> if expression then sequence_statement [elsif expression then sequence_statement]* [else sequence_statement] end if;

boolean if_statement(){
    if(SYM_COUR.CODE == IF_TOKEN){
        nextToken();
        if(expression()){
            nextToken();
            if(SYM_COUR.CODE == THEN_TOKEN){
                nextToken();
                if(sequence_statement()){
                    nextToken();
                    while(SYM_COUR.CODE == ELSIF_TOKEN){
                        nextToken();
                        if(expression()){
                            nextToken();
                            if(SYM_COUR.CODE == THEN_TOKEN){
                                nextToken();
                                if(sequence_statement())
                                    nextToken();
                                else
                                    return false;
                            }
                            else
                                return false;
                        }
                        else
                            return false;
                    }
                    //SYM_COUR contains already the follow token. so, no need to call nextToken
                    if(SYM_COUR.CODE == ELSE_TOKEN){
                        nextToken();
                        if(sequence_statement()){
                            nextToken();
                        }
                        else
                            return false;
                    }
                    if(SYM_COUR.CODE == END_TOKEN){
                        nextToken();
                        if(SYM_COUR.CODE == IF_TOKEN){
                            nextToken();
                            if(SYM_COUR.CODE == PV_TOKEN)
                                return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


//31 - block_statement -> [declare (basic_declaration)*]
//                   begin
//                      sequence_statement
//                    end;

boolean block_statement(){
    if(SYM_COUR.CODE == DECLARE_TOKEN){
        nextToken();
        while(SYM_COUR.CODE == TYPE_TOKEN || SYM_COUR.CODE == ID_TOKEN ){
            basic_declaration();
            nextToken();
        }
    }
    if( SYM_COUR.CODE == BEGIN_TOKEN){
        nextToken();
        sequence_statement();
        nextToken();
        if( SYM_COUR.CODE == END_TOKEN){
            return true;
        }
    }
    return false;
}

// 32 - expression -> relation [(and| or | xor) relation]*
boolean expression(){
    if( relation()) {
        nextToken();
        while( SYM_COUR.CODE == AND_TOKEN || SYM_COUR.CODE == OR_TOKEN || SYM_COUR.CODE == XOR_TOKEN ){
            nextToken();
            if( !relation()) return false;
        }
        follow_token = true;
        return true;
    }
    return false;
}

// 33 - relation -> simple_expression [(= | =* | =/ | < | <= | > |>= )  simple_expression
//                                 | (not | in) NUM_TOKEN .. NUM_TOKEN
//                               ]
boolean relation(){
    if( simple_expression() ){
        nextToken();
        if( SYM_COUR.CODE == EGAL_TOKEN || SYM_COUR.CODE == AFFEC_MULT_TOKEN || SYM_COUR.CODE == AFFEC_DIV_TOKEN || SYM_COUR.CODE == INF_TOKEN || SYM_COUR.CODE == INFEG_TOKEN || SYM_COUR.CODE == SUP_TOKEN || SYM_COUR.CODE == SUPEG_TOKEN ){
            nextToken();
            return simple_expression();
        }
        else if ( SYM_COUR.CODE == NOT_TOKEN || SYM_COUR.CODE == IN_TOKEN ) {
            nextToken();
            if( SYM_COUR.CODE == NUM_TOKEN){
                nextToken();
                if( SYM_COUR.CODE == PT_TOKEN){
                    nextToken();
                    if( SYM_COUR.CODE == PT_TOKEN){
                        nextToken();
                        if( SYM_COUR.CODE == NUM_TOKEN){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


// 34 - simple_expression -> [+ | -] term { (+ | - | &) term }*
boolean simple_expression{
    if ( SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN ){
        nextToken();
    }
    if( term()){
        nextToken();
        while( SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN || SYM_COUR.CODE == EC_TOKEN ){
            nextToken();
            if( !term()) return false;
        }
        follow_token = true;
        return true;
    }
    return false;
}

// 35 - term  -> factor {(* | / | mod | rem) factor}*
boolean term(){
    if( factor()){
        nextToken();
        while( SYM_COUR.CODE == MULT_TOKEN || SYM_COUR.CODE == DIV_TOKEN || SYM_COUR.CODE == MOD_TOKEN ){
            nextToken();
            if( !factor()) return false;
        }
        follow_token = true;
        return true;
    }
    return false;
}
// 36 - factor -> primary [** primary]
        // | abs primary
        // |not primary
boolean factor(){
    if( SYM_COUR.CODE == ABS_TOKEN || SYM_COUR.CODE == NOT_TOKEN){
        nextToken();
        return primary();
    }
    else {
        if ( primary()){
            nextToken();
            if( SYM_COUR.CODE == MULT_TOKEN ){
                nextToken();
                if( SYM_COUR.CODE == MULT_TOKEN ){
                    return primary();
                }
            }
            else{
                follow_token = true;
                return true;
            }
        }
    }
    return false;
}

// 37 - primary -> NULL_TOKEN | STRING_TOKEN | id | NUM_TOKEN | FLOAT_TOKEN  | '(' expression ')'
boolean primary(){
    if ( SYM_COUR.CODE == NULL_TOKEN || SYM_COUR.CODE == STRING_TOKEN || SYM_COUR.CODE == ID_TOKEN || SYM_COUR.CODE == NUM_TOKEN || SYM_COUR.CODE == FLOAT_TOKEN){
        return true;
    }
    else if( SYM_COUR.CODE == PO_TOKEN ){
        nextToken();
        if ( expression() ){
            nextToken();
            if( SYM_COUR.CODE == PF_TOKEN ){
                return true;
            }
        }
    }
    return false;
}
