# Spark-Ada-Compiler
Basic spark ada Compiler

spark ada grammar used by this compiler : 


1 - program -> [with_use_clause]* subprogram_body

2 - with_use_clause -> (use | with) id [.id]*

3 - subprogram_body -> subprogram_specification is [basic_declaration]* begin sequence_statement end [id];

4 - subprogram_specification -> procedure id ['(' formal_part ')']
                          | function id ['(' formal_part ')'] return id

5 - formal_part -> parameter_specification [, parameter_specification]*

6 - parameter_specification -> id : [in | out] id [:= expression]




7 - basic_declaration -> type_declaration | object_number_declaration

8 - type_declaration -> type id is
     (enumeration_type_definition | integer_type_definition
      | real_type_definition | array_type_definition);


9 - enumeration_type_definition ->'(' (id|char) [ , (id|char)]*  ')'


10 - integer_type_definition -> range T_NUMERIC .. T_NUMERIC
                          | mode expression

11 - real_type_definition -> digit T_NUMERIC [range T_NUMERIC .. T_NUMERIC]


(1-D array)
12 - array_type_definition ->array '(' id [range (<> | T_NUMERIC .. T_NUMERIC)]  ')' of id


13 - record_type_definition -> null record;
                        | record component_list end record

14 - component_list -> component_item [component_item]*
                | null ;

15 - component_item -> id : id [:= expression]


16 - object_number_declaration -> id : (constant  | id ) := expression;

17 - sequence_statement -> statement {statement}*

18 - statement -> simple_statement | compound_statement

19 - simple_statement ::= null_statement
   | procedure_call_or_assign_statement
   | exit_statement
   | goto_statement
   | return_statement


20 - null_statement -> null ;

21 - exit_statement -> exit [id] [when expression];

22 - goto_statement -> goto id;

23 - procedure_call_or_assign_statement-> id ('(' params ')' | := expression) ;

24 - params -> [id =>] expression {, params}*

25 - return_statement -> return [expression] ;

26 - compound_statement ::= if_statement
                      | case_statement
                      | loop_statement
                      | block_statement

27 - if_statement -> if expression then sequence_statement
                [elsif expression then sequence_statement]*
                [else sequence_statement]
                end if;


28 - case_statement -> case expression is case_statement_alt {case_statement_alt}* end case;

29 - case_statement_alt -> when (simple_expression | others) => sequence_statement

30 - loop_statement -> [(while expression | for id in [reverse] simple_expression .. simple_expression)]
                  loop sequence_statement end loop;

31 - block_statement -> [declare (basic_declaration)*]
                   begin
                      sequence_statement
                    end;

32 - expression -> relation [(and| or | xor) relation]*

33 - relation -> simple_expression [(= | =* | =/ | < | <= | > |>= )  simple_expression
                                | (not | in) T_NUMERIC .. T_NUMERIC
                              ]

34 - simple_expression -> [+ | -] term { (+ | - | &) term }*

35 - term  -> factor {(* | / | mod | rem) factor}*

36 - factor -> primary [** primary]
        | abs primary
        |not primary


37 - primary -> T_NULL | T_STRING | id | T_NUMERIC | '(' expression ')'


