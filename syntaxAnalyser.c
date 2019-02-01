#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"

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

// integer_type_definition -> range T_NUMERIC .. T_NUMERIC | mode expression

// enumeration_type_definition ->'(' (id|char) [ , (id|char)]*  ')'

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

//multiple_id -> .id multiple_id | epsilon
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

//with_use_clause -> (use | with) id multiple_id

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

//list_with_use_clause -> with_use_clause list_with_use_clause | epsilon
//FIRST = (use, with)
//FOLLOW = (procedure, function)

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

//subprogram_specification -> procedure id ['(' formal_part ')'] | function id ['(' formal_part ')'] return id

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
    }
    return result;
}

//type_declaration -> type id is (enumeration_type_definition | integer_type_definition | real_type_definition | array_type_definition);

boolean type_declaration(){
    if(SYM_COUR.CODE == TYPE_TOKEN){
        nextToken();
        if(SYM_COUR.CODE == ID_TOKEN){
            nextToken();
            if(SYM_COUR.CODE == IS_TOKEN){
                nextToken();
                if(SYM_COUR.CODE == PO_TOKEN){
                    if(enumeration_type_definition()){
                        return true;
                    }
                }
                if(SYM_COUR.CODE == RANGE_TOKEN){
                    if(integer_type_definition()){
                        return true;
                    }
                }
                if(SYM_COUR.CODE == DIGITS_TOKEN){
                    if(real_type_definition()){
                        return true;
                    }
                }
                if(SYM_COUR.CODE == ARRAY_TOKEN){
                    if(array_type_definition()){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// -> id : [in | out] id [:= expression]

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

// other_-> , other_| epsilon
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

//formal_part -> other_parameter_specification

boolean formal_part(){
    if(parameter_specification()){
        nextToken();
        if(other_parameter_specification()){
            return true;
        }
    }
    return false;
}


// basic_declaration -> type_declaration | object_number_declaration

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

// list_basic_declaration -> basic_declaration list_basic_declaration | epsilon
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


// subprogram_body -> subprogram_specification is list_basic_declaration begin sequence_statement end [id];

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

//program -> list_with_use_clause subprogram_body

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

//integer_type_definition -> range T_NUMERIC .. T_NUMERIC | mode expression

boolean integer_type_definition(){
    boolean result = FALSE;
    if(SYM_COUR.CODE == RANGE_TOKEN){
        next_token();
        if(SYM_COUR.CODE == NUM_TOKEN){
            next_token();
            if(SYM_COUR.CODE == PT_TOKEN){
                next_token();
                if(SYM_COUR.CODE == PT_TOKEN){
                    next_token();
                    if(SYM_COUR.CODE == NUM_TOKEN){
                        result = TRUE;
                    }
                }
            }
        }
    }
    else if(SYM_COUR.CODE == ID_TOKEN){
        // TODO check if mode is MODE_TOKEN or ID_TOKEN
        next_token();
            if(expression())
                result = TRUE;
    }
    return result;
}


//real_type_definition -> digit T_NUMERIC [range T_NUMERIC .. T_NUMERIC](1-D array) 

boolean real_type_definition(){
    boolean result = FALSE;
    if(SYM_COUR.CODE == DIGITS_TOKEN){
        next_token();
        if(SYM_COUR.CODE == NUM_TOKEN){
            next_token();
            if(SYM_COUR.CODE == RANGE_TOKEN){
                next_token();
                if(SYM_COUR.CODE == NUM_TOKEN){
                    next_token();
                    if(SYM_COUR.CODE == PT_TOKEN){
                        next_token();
                        if(SYM_COUR.CODE == PT_TOKEN){
                            next_token();
                            if(SYM_COUR.CODE == NUM_TOKEN){
                                next_token();
                            }
                            else
                                return result;
                        }
                        else{
                            return result;
                        }
                    }
                    else{
                        return result;
                    }
                }
                else{
                    return result;
                }
            }
            if(SYM_COUR.CODE == PO_TOKEN){
                // TODO semantic check if num_token == 1
                next_token();
                if(SYM_COUR.CODE == NUM_TOKEN){
                    next_token();
                    if(SYM_COUR.CODE == MOINS_TOKEN){
                        next_token();
                        //TODO semantic check if ID_TOKEN == D
                        if(SYM_COUR.CODE == ID_TOKEN){
                            next_token();
                            if(SYM_COUR.CODE == ARRAY_TOKEN){
                                next_token();
                                if(SYM_COUR.CODE == PF_TOKEN){
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

//array_type_definition ->array '(' id [range (<> | T_NUMERIC .. T_NUMERIC)] ')' of id

boolean array_type_definition(){
    boolean result = false;
    if(SYM_COUR.CODE == ARRAY_TOKEN){
        next_token();
        if(SYM_COUR.CODE == PO_TOKEN){
            next_token();
            if(SYM_COUR.CODE == ID_TOKEN){
                next_token();
                if(SYM_COUR.CODE == RANGE_TOKEN){
                    next_token();
                    if(SYM_COUR.CODE == DIFF_TOKEN){
                        next_token();
                    }
                    else if(SYM_COUR.CODE == NUM_TOKEN){
                        next_token();
                        if(SYM_COUR.CODE == PT_TOKEN){
                            next_token();
                            if(SYM_COUR.CODE == PT_TOKEN){
                                next_token();
                                if(SYM_COUR.CODE == NUM_TOKEN){
                                    next_token();
                                }
                                else
                                    return result;
                            }
                            else
                                return result;
                        }
                        else
                            return result;
                    }
                    else
                        return result; 
                }
                if(SYM_COUR.CODE == PF_TOKEN){
                    next_token();
                    if(SYM_COUR.CODE == OF_TOKEN){
                        next_token();
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
    boolean result = FALSE;
    if(SYM_COUR.CODE == NULL_TOKEN){
        next_token();
        if(SYM_COUR.CODE == RECORD_TOKEN){
            next_token();
            if(SYM_COUR.CODE == PV_TOKEN){
                result = true;
            }
        }
    }
    else{
        if(SYM_COUR.CODE == RECORD_TOKEN){
            next_token();
            if(component_list()){
                next_token();
                if(SYM_COUR.CODE == END_TOKEN){
                    next_token();
                    if(SYM_COUR.CODE == RECORD_TOKEN){
                        result = true;
                    }
                }
            }
        }
    }
    return result;
}
// component_list -> component_item [component_item]* | null ;
boolean component_list(){
    boolean result=FALSE;
    if(component_item()){
        do{
            next_token();
        }while(SYM_COUR.CODE == component_item());
        result = TRUE;
    }
    else{
        if(SYM_COUR.CODE == NULL_TOKEN){
            next_token()
            if(SYM_COUR.CODE == PV_TOKEN)
                result = TRUE;
        }
    }
    return result;
}

//component_item -> id : id [:= expression]
boolean component_item(){
    boolean result = FALSE;
    if(SYM_COUR.CODE == ID_TOKEN){
        next_token();
        if(SYM_COUR.CODE == DOUBLE_POINT_TOKEN){
            next_token();
            if(SYM_COUR.CODE == ID_TOKEN){
                next_token();
                if(SYM_COUR.CODE == AFF_TOKEN){
                    next_token();
                    if(expression)
                        result = TRUE;
                }
                else{
                    result = TRUE;
                }
            }
        }
    }
    return result;
}

//object_number_declaration -> id : (constant | id ) := expression
boolean object_number_declaration(){
    boolean result = FALSE;
    if(SYM_COUR.CODE == ID_TOKEN){
        next_token();
        if(SYM_COUR.CODE == DOUBLE_POINT_TOKEN){
            next_token();
            //TODO semanticcheck if ID_TOKEN is CONSTANT_TOKEN
            if(SYM_COUR.CODE == ID_TOKEN ||  SYM_COUR.CODE == CONSTANT_TOKEN){
                next_token();
                if(SYM_COUR.CODE == AFF_TOKEN){
                    next_token();
                    if(expression()){
                        next_token()   
                        if(SYM_COUR.CODE == PV_TOKEN)
                            result = TRUE;
                    }                   
                }
            }
        }
    }
    return result;
}

// sequence_statement -> statement {statement}*
boolean sequence_statement(){
    boolean result = FALSE;
    if(statement()){
        do{
            next_token();
        }while(statement());
        result = TRUE;
    }
    return result;
}

//statement -> simple_statement | compound_statement
boolean statement(){
    return (simple_statement() || compound_statement())

}

//simple_statement ::= null_statement | procedure_call_or_assign_statement | exit_statement | goto_statement | return_statement

boolean simple_statement(){
    return (null_statement() || procedure_call_or_assign_statement() || exit_statement() || goto_statement() || return_statement());
}

//null_statement -> null ;
boolean null_statement(){
    boolean result = FALSE;
    if(SYM_COUR.CODE == NULL_TOKEN){
        next_token();
        if(SYM_COUR.CODE == PV_TOKEN)
            result = TRUE;
    }
    return result;
}

//exit_statement -> exit [id] [when expression];
boolean exit_statement(){
    boolean result = false;;
    if(SYM_COUR.CODE == EXIT_TOKEN){
        next_token();
        if(SYM_COUR.CODE == ID_TOKEN){
            result = TRUE;
        }
        else if(SYM_COUR.CODE == WHEN_TOKEN){
                next_token();
                if(expression())
                    result = true;
                else
                    result = FALSE;
        }
        else
            result = TRUE;
    }
    return result;
}

//goto_statement -> goto id;
boolean goto_statement(){
    if(SYM_COUR.CODE == GOTO_TOKEN){
        next_token();
        if(SYM_COUR.CODE == ID_TOKEN)
            return TRUE;
    }
    return FALSE;
}





