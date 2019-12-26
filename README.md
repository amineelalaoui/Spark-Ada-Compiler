# Spark-Ada-Compiler
Basic spark ada Compiler

## Authors : 
* [Mohamed Amine EL ALAOUI](https://www.linkedin.com/in/med-amine-elalaoui/)
* [Abderrahman MEFTAHI](https://www.linkedin.com/in/abderrahman-meftahi-428090150/)
* [Abderrazak LAATAATA](https://github.com/alienv1)
* [Driss KHALIL](https://www.linkedin.com/in/driss-khalil-b3aab4151/)

 

## spark ada grammar used by this compiler : 


* program -> [with_use_clause]* subprogram_body

* with_use_clause -> (use | with) id [.id]*

* subprogram_body -> subprogram_specification is [basic_declaration]* begin sequence_statement end [id];

* subprogram_specification -> procedure id ['(' formal_part ')']
                          | function id ['(' formal_part ')'] return id

* formal_part -> parameter_specification [, parameter_specification]*

* parameter_specification -> id : [in | out] id [:= expression]




* basic_declaration -> type_declaration | object_number_declaration

* type_declaration -> type id is
     (enumeration_type_definition | integer_type_definition
      | real_type_definition | array_type_definition);


* enumeration_type_definition ->'(' (id|char) [ , (id|char)]*  ')'


* integer_type_definition -> range T_NUMERIC .. T_NUMERIC
                          | mode expression

* real_type_definition -> digit T_NUMERIC [range T_NUMERIC .. T_NUMERIC]


(1-D array)
* array_type_definition ->array '(' id [range (<> | T_NUMERIC .. T_NUMERIC)]  ')' of id


* record_type_definition -> null record;
                        | record component_list end record

* component_list -> component_item [component_item]*
                | null ;

* component_item -> id : id [:= expression]


* object_number_declaration -> id : (constant  | id ) := expression;

* sequence_statement -> statement {statement}*

* statement -> simple_statement | compound_statement

* simple_statement ::= null_statement
   | procedure_call_or_assign_statement
   | exit_statement
   | goto_statement
   | return_statement


* null_statement -> null ;

* exit_statement -> exit [id] [when expression];

* goto_statement -> goto id;

* procedure_call_or_assign_statement-> id ('(' params ')' | := expression) ;

* params -> [id =>] expression {, params}*

* return_statement -> return [expression] ;

* compound_statement ::= if_statement
                      | case_statement
                      | loop_statement
                      | block_statement

* if_statement -> if expression then sequence_statement
                [elsif expression then sequence_statement]*
                [else sequence_statement]
                end if;


* case_statement -> case expression is case_statement_alt {case_statement_alt}* end case;

* case_statement_alt -> when (simple_expression | others) => sequence_statement

* loop_statement -> [(while expression | for id in [reverse] simple_expression .. simple_expression)]
                  loop sequence_statement end loop;

* block_statement -> [declare (basic_declaration)*]
                   begin
                      sequence_statement
                    end;

* expression -> relation [(and| or | xor) relation]*

* relation -> simple_expression [(= | =* | =/ | < | <= | > |>= )  simple_expression
                                | (not | in) T_NUMERIC .. T_NUMERIC
                              ]

* simple_expression -> [+ | -] term { (+ | - | &) term }*

* term  -> factor {(* | / | mod | rem) factor}*

* factor -> primary [** primary]
        | abs primary
        |not primary


* primary -> T_NULL | T_STRING | id | T_NUMERIC | '(' expression ')'


