/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PASCAL_Y_HPP_INCLUDED
# define YY_YY_PASCAL_Y_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "parser/pascal.y"

#include <iostream>
#include "ast/AST.hpp"

#line 53 "pascal.y.hpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    KEY_BREAK = 258,
    KEY_EXIT = 259,
    TYPE_INT = 260,
    TYPE_INT_8 = 261,
    TYPE_INT_16 = 262,
    TYPE_INT_32 = 263,
    TYPE_INT_64 = 264,
    TYPE_UNSIGNED_INT_8 = 265,
    TYPE_UNSIGNED_INT_16 = 266,
    TYPE_UNSIGNED_INT_32 = 267,
    TYPE_UNSIGNED_INT_64 = 268,
    TYPE_BOOLEAN = 269,
    TYPE_FLOAT = 270,
    TYPE_FLOAT_16 = 271,
    TYPE_FLOAT_32 = 272,
    TYPE_CHAR = 273,
    TYPE_STRING = 274,
    LITERAL_INT = 275,
    LITERAL_FLOAT = 276,
    LITERAL_CHAR = 277,
    LITERAL_ESC_CHAR = 278,
    LITERAL_STR = 279,
    LITERAL_TRUE = 280,
    LITERAL_FALSE = 281,
    IDENTIFIER = 282,
    SYM_ADD = 283,
    SYM_SUB = 284,
    SYM_MUL = 285,
    SYM_DIV = 286,
    SYM_EQ = 287,
    SYM_LT = 288,
    SYM_GT = 289,
    SYM_LBRAC = 290,
    SYM_RBRAC = 291,
    SYM_PERIOD = 292,
    SYM_COMMA = 293,
    SYM_COLON = 294,
    SYM_SEMICOLON = 295,
    SYM_AT = 296,
    SYM_CARET = 297,
    SYM_LPAREN = 298,
    SYM_RPAREN = 299,
    SYM_NE = 300,
    SYM_LE = 301,
    SYM_GE = 302,
    SYM_ASSIGN = 303,
    SYM_RANGE = 304,
    COMMENT = 305,
    KEY_AND = 306,
    KEY_ARRAY = 307,
    KEY_ASM = 308,
    KEY_BEGIN = 309,
    KEY_CASE = 310,
    KEY_CONST = 311,
    KEY_CONSTRUCTOR = 312,
    KEY_DESTRUCTOR = 313,
    KEY_DIV = 314,
    KEY_DO = 315,
    KEY_DOWNTO = 316,
    KEY_ELSE = 317,
    KEY_END = 318,
    KEY_FILE = 319,
    KEY_FOR = 320,
    KEY_FUNCTION = 321,
    KEY_GOTO = 322,
    KEY_IF = 323,
    KEY_IMPLEMENTATION = 324,
    KEY_IN = 325,
    KEY_INHERITED = 326,
    KEY_INLINE = 327,
    KEY_INTERFACE = 328,
    KEY_LABEL = 329,
    KEY_MOD = 330,
    KEY_NIL = 331,
    KEY_NOT = 332,
    KEY_OBJECT = 333,
    KEY_OF = 334,
    KEY_OPERATOR = 335,
    KEY_OR = 336,
    KEY_PACKED = 337,
    KEY_PROCEDURE = 338,
    KEY_PROGRAM = 339,
    KEY_RECORD = 340,
    KEY_REINTRODUCE = 341,
    KEY_REPEAT = 342,
    KEY_SELF = 343,
    KEY_SET = 344,
    KEY_SHL = 345,
    KEY_SHR = 346,
    KEY_THEN = 347,
    KEY_TO = 348,
    KEY_TYPE = 349,
    KEY_UNIT = 350,
    KEY_UNTIL = 351,
    KEY_USES = 352,
    KEY_VAR = 353,
    KEY_WHILE = 354,
    KEY_WITH = 355,
    KEY_XOR = 356,
    SIGN = 357
  };
#endif
/* Tokens.  */
#define KEY_BREAK 258
#define KEY_EXIT 259
#define TYPE_INT 260
#define TYPE_INT_8 261
#define TYPE_INT_16 262
#define TYPE_INT_32 263
#define TYPE_INT_64 264
#define TYPE_UNSIGNED_INT_8 265
#define TYPE_UNSIGNED_INT_16 266
#define TYPE_UNSIGNED_INT_32 267
#define TYPE_UNSIGNED_INT_64 268
#define TYPE_BOOLEAN 269
#define TYPE_FLOAT 270
#define TYPE_FLOAT_16 271
#define TYPE_FLOAT_32 272
#define TYPE_CHAR 273
#define TYPE_STRING 274
#define LITERAL_INT 275
#define LITERAL_FLOAT 276
#define LITERAL_CHAR 277
#define LITERAL_ESC_CHAR 278
#define LITERAL_STR 279
#define LITERAL_TRUE 280
#define LITERAL_FALSE 281
#define IDENTIFIER 282
#define SYM_ADD 283
#define SYM_SUB 284
#define SYM_MUL 285
#define SYM_DIV 286
#define SYM_EQ 287
#define SYM_LT 288
#define SYM_GT 289
#define SYM_LBRAC 290
#define SYM_RBRAC 291
#define SYM_PERIOD 292
#define SYM_COMMA 293
#define SYM_COLON 294
#define SYM_SEMICOLON 295
#define SYM_AT 296
#define SYM_CARET 297
#define SYM_LPAREN 298
#define SYM_RPAREN 299
#define SYM_NE 300
#define SYM_LE 301
#define SYM_GE 302
#define SYM_ASSIGN 303
#define SYM_RANGE 304
#define COMMENT 305
#define KEY_AND 306
#define KEY_ARRAY 307
#define KEY_ASM 308
#define KEY_BEGIN 309
#define KEY_CASE 310
#define KEY_CONST 311
#define KEY_CONSTRUCTOR 312
#define KEY_DESTRUCTOR 313
#define KEY_DIV 314
#define KEY_DO 315
#define KEY_DOWNTO 316
#define KEY_ELSE 317
#define KEY_END 318
#define KEY_FILE 319
#define KEY_FOR 320
#define KEY_FUNCTION 321
#define KEY_GOTO 322
#define KEY_IF 323
#define KEY_IMPLEMENTATION 324
#define KEY_IN 325
#define KEY_INHERITED 326
#define KEY_INLINE 327
#define KEY_INTERFACE 328
#define KEY_LABEL 329
#define KEY_MOD 330
#define KEY_NIL 331
#define KEY_NOT 332
#define KEY_OBJECT 333
#define KEY_OF 334
#define KEY_OPERATOR 335
#define KEY_OR 336
#define KEY_PACKED 337
#define KEY_PROCEDURE 338
#define KEY_PROGRAM 339
#define KEY_RECORD 340
#define KEY_REINTRODUCE 341
#define KEY_REPEAT 342
#define KEY_SELF 343
#define KEY_SET 344
#define KEY_SHL 345
#define KEY_SHR 346
#define KEY_THEN 347
#define KEY_TO 348
#define KEY_TYPE 349
#define KEY_UNIT 350
#define KEY_UNTIL 351
#define KEY_USES 352
#define KEY_VAR 353
#define KEY_WHILE 354
#define KEY_WITH 355
#define KEY_XOR 356
#define SIGN 357

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "parser/pascal.y"

    int token_type;
    char* str;

    //AST_Value.hpp
    AST_Const_Part* ast_const_part;
    AST_Const_Expression_List* ast_const_expression_list;
    AST_Const_Expression* ast_const_expression;
    AST_Const_Value* ast_const_value;
    AST_Variable_Part* ast_variable_part;
    AST_Variable_Declaration_List* ast_variable_declaration_list;
    AST_Variable_Declaration* ast_variable_declaration;

    //AST_Type.hpp
    AST_Type_Part* ast_type_part;
    AST_Type_Definition* ast_type_definition;
    AST_Type_Declaration_List* ast_type_declaration_list;
    AST_Type* ast_type;
    AST_Type_Declaration* ast_type_declaration;
    AST_Simple_Type_Declaration* ast_simple_type_declaration;
    AST_Array_Type_Declaration* ast_array_type_declaration;
    AST_Record_Type_Declaration* ast_record_type_declaration;    
    AST_Field_Declaration_List* ast_field_declaration_list;
    AST_Field_Declaration* ast_field_declaration;
    AST_Name_List* ast_name_list;
   
    //AST_Expression.hpp 
    AST_Expression* ast_expression;
    AST_Expression_List* ast_expression_list;

    //AST_Program.hpp
    AST_Program* ast_program;
    AST_Program_Head* ast_program_head;
    AST_Routine* ast_routine;
    AST_Routine_Head* ast_routine_head;
    // AST_Declaration_BaseClass* ast_declaration_baseclass;
    AST_Routine_Part* ast_routine_part;
    AST_Routine_Body* ast_routine_body;
    AST_Function_Declaration* ast_function_declaration;
    AST_Function_Head* ast_function_head;
    AST_Procedure_Declaration* ast_procedure_declaration;
    AST_Procedure_Head* ast_procedure_head;
    AST_Parameters* ast_parameters;
    AST_Parameters_Declaration_List* ast_parameters_declaration_list;
    AST_Parameters_Type_List* ast_parameters_type_list;
    AST_Variable_Parameters_List* ast_variable_parameters_list;

    //AST_Statement.hpp
    AST_Compound_Statement* ast_compound_statement;
    AST_Statement_List* ast_statement_list;
    AST_Statement* ast_statement;
    AST_Label* ast_label;
    AST_Non_Label_Statement* ast_non_label_statement;
    AST_Assign_Statement* ast_assign_statement;
    AST_Procedure_Statement* ast_procedure_statement;
    AST_If_Statement* ast_if_statement;
    AST_Else_Clause* ast_else_clause;
    AST_Case_Statement* ast_case_statement;
    AST_Case_Expression_List* ast_case_expression_list;
    AST_Case_Expression* ast_case_expression;
    AST_Repeat_Statement* ast_repeat_statement;
    AST_While_Statement* ast_while_statement;
    AST_For_Statement* ast_for_statement;
    AST_Direction* ast_direction;
    AST_Goto_Statement* ast_goto_statement;

#line 335 "pascal.y.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PASCAL_Y_HPP_INCLUDED  */
