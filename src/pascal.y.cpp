/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "parser/pascal.y"

#define MAX_LITERAL_LEN 256
#define SET_LOCATION(dest) (dest)->SetLocation(yylloc.first_column,yylloc.first_line)
extern int yylex(void);
// 在此声明，消除yacc生成代码时的警告
extern int yyparse(void); 
void yyerror(const char *str);
using namespace std;

#line 80 "pascal.y.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 128 "pascal.y.cpp"

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

#line 410 "pascal.y.cpp"

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



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   332

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  103
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  244

#define YYUNDEFTOK  2
#define YYMAXUTOK   357


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   170,   170,   178,   185,   193,   200,   204,   210,   214,
     220,   224,   230,   236,   242,   247,   252,   258,   265,   272,
     277,   285,   292,   296,   300,   304,   308,   312,   319,   324,
     332,   339,   343,   347,   354,   358,   362,   366,   370,   377,
     381,   385,   389,   396,   401,   409,   416,   423,   428,   435,
     442,   447,   455,   462,   469,   476,   483,   490,   494,   501,
     506,   513,   517,   524,   531,   536,   543,   548,   556,   560,
     567,   571,   575,   579,   583,   587,   591,   595,   599,   606,
     610,   614,   623,   627,   635,   642,   646,   652,   659,   664,
     672,   676,   683,   690,   697,   704,   709,   717,   724,   729,
     737,   741,   745,   749,   753,   757,   761,   768,   772,   776,
     780,   787,   791,   795,   799,   803,   807,   814,   818,   822,
     826,   830,   834,   838,   842
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "KEY_BREAK", "KEY_EXIT", "TYPE_INT",
  "TYPE_INT_8", "TYPE_INT_16", "TYPE_INT_32", "TYPE_INT_64",
  "TYPE_UNSIGNED_INT_8", "TYPE_UNSIGNED_INT_16", "TYPE_UNSIGNED_INT_32",
  "TYPE_UNSIGNED_INT_64", "TYPE_BOOLEAN", "TYPE_FLOAT", "TYPE_FLOAT_16",
  "TYPE_FLOAT_32", "TYPE_CHAR", "TYPE_STRING", "LITERAL_INT",
  "LITERAL_FLOAT", "LITERAL_CHAR", "LITERAL_ESC_CHAR", "LITERAL_STR",
  "LITERAL_TRUE", "LITERAL_FALSE", "IDENTIFIER", "SYM_ADD", "SYM_SUB",
  "SYM_MUL", "SYM_DIV", "SYM_EQ", "SYM_LT", "SYM_GT", "SYM_LBRAC",
  "SYM_RBRAC", "SYM_PERIOD", "SYM_COMMA", "SYM_COLON", "SYM_SEMICOLON",
  "SYM_AT", "SYM_CARET", "SYM_LPAREN", "SYM_RPAREN", "SYM_NE", "SYM_LE",
  "SYM_GE", "SYM_ASSIGN", "SYM_RANGE", "COMMENT", "KEY_AND", "KEY_ARRAY",
  "KEY_ASM", "KEY_BEGIN", "KEY_CASE", "KEY_CONST", "KEY_CONSTRUCTOR",
  "KEY_DESTRUCTOR", "KEY_DIV", "KEY_DO", "KEY_DOWNTO", "KEY_ELSE",
  "KEY_END", "KEY_FILE", "KEY_FOR", "KEY_FUNCTION", "KEY_GOTO", "KEY_IF",
  "KEY_IMPLEMENTATION", "KEY_IN", "KEY_INHERITED", "KEY_INLINE",
  "KEY_INTERFACE", "KEY_LABEL", "KEY_MOD", "KEY_NIL", "KEY_NOT",
  "KEY_OBJECT", "KEY_OF", "KEY_OPERATOR", "KEY_OR", "KEY_PACKED",
  "KEY_PROCEDURE", "KEY_PROGRAM", "KEY_RECORD", "KEY_REINTRODUCE",
  "KEY_REPEAT", "KEY_SELF", "KEY_SET", "KEY_SHL", "KEY_SHR", "KEY_THEN",
  "KEY_TO", "KEY_TYPE", "KEY_UNIT", "KEY_UNTIL", "KEY_USES", "KEY_VAR",
  "KEY_WHILE", "KEY_WITH", "KEY_XOR", "SIGN", "$accept", "program",
  "pro_head", "routine", "routine_head", "const_part", "type_part",
  "var_part", "routine_part", "routine_body", "compound_stmt",
  "const_expr_list", "const_expr", "const_value", "type_decl_list",
  "type_definition", "type_decl", "simple_type_decl", "easy_type",
  "name_list", "array_type_decl", "record_type_decl", "field_decl_list",
  "field_decl", "var_decl_list", "var_decl", "function_decl",
  "function_head", "procedure_decl", "procedure_head", "parameters",
  "para_decl_list", "para_type_list", "var_para_list", "stmt_list", "stmt",
  "label", "non_label_stmt", "assign_stmt", "proc_stmt", "if_stmt",
  "else_clause", "case_stmt", "case_expr_list", "case_expr", "repeat_stmt",
  "while_stmt", "for_stmt", "direction", "goto_stmt", "expression_list",
  "expression", "expr", "term", "factor", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357
};
# endif

#define YYPACT_NINF (-152)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-70)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -81,   -13,    21,     9,    39,  -152,    55,    58,    62,    25,
    -152,    85,    55,  -152,  -152,  -152,  -152,  -152,    95,    27,
      23,  -152,    47,    94,    95,  -152,   102,   -48,  -152,  -152,
    -152,  -152,  -152,  -152,   -28,    23,    23,    23,  -152,   227,
      -5,   145,  -152,  -152,   270,    23,  -152,   112,    -8,    23,
    -152,    23,  -152,   107,   114,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,    12,  -152,  -152,     3,   102,  -152,
     115,   124,   -48,  -152,   127,  -152,   134,    23,   131,    23,
    -152,   231,  -152,    23,    23,    23,  -152,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,    23,   135,
      23,    23,   146,   106,  -152,  -152,   103,    31,   208,  -152,
     118,  -152,  -152,  -152,  -152,   128,   102,   147,   102,   132,
     144,  -152,  -152,  -152,  -152,   160,    12,  -152,   151,   151,
    -152,  -152,     9,     9,   247,  -152,   -16,   257,  -152,    -5,
      -5,    -5,    -5,    -5,    -5,   145,   145,   145,  -152,  -152,
    -152,  -152,  -152,   252,   141,     2,   257,   290,    23,   101,
      23,   101,   122,  -152,   170,    15,   209,    50,    -7,  -152,
     299,  -152,  -152,   159,   -21,   176,  -152,   169,   178,  -152,
      23,  -152,   168,    23,  -152,   180,   182,   186,  -152,    59,
     164,   257,  -152,  -152,  -152,   192,    12,  -152,  -152,  -152,
    -152,   102,    70,    40,  -152,   183,   209,  -152,  -152,   257,
      23,   257,   101,   101,  -152,  -152,  -152,  -152,    23,   101,
    -152,   153,   197,   200,   209,   -21,  -152,   209,  -152,   257,
     199,   206,   211,  -152,    12,  -152,  -152,  -152,  -152,  -152,
    -152,   101,  -152,  -152
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     7,     0,     1,     0,     0,     0,     9,
       3,     0,     6,    20,     2,    65,     4,    17,     0,    11,
       0,    19,     0,     0,     8,    29,     0,    16,    22,    23,
      24,    25,    27,    26,   117,     0,     0,     0,   119,     0,
     106,   110,   116,    68,    82,     0,    18,     0,     0,     0,
      65,     0,    72,     0,     0,    67,    70,    71,    73,    74,
      75,    76,    77,    78,     0,    28,    44,     0,    10,    51,
       0,     0,     5,    14,     0,    15,     0,     0,     0,     0,
     122,     0,   121,     0,     0,     0,    21,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    69,    97,     0,     0,     0,    64,
       0,    41,    39,    42,    40,    35,     0,     0,     0,     0,
       0,    31,    34,    32,    33,     0,     0,    50,    58,    58,
      12,    13,     7,     7,     0,   124,     0,    99,   120,   104,
     103,   101,   105,   102,   100,   107,   108,   109,   111,   112,
     115,   113,   114,     0,     0,     0,    79,     0,     0,     0,
       0,     0,    82,    66,     0,     0,     0,     0,     0,    48,
       0,    30,    43,     0,     0,     0,    56,     0,     0,   123,
       0,   118,     0,     0,    83,     0,     0,     0,    89,     0,
      86,    92,    93,    38,    36,     0,     0,    46,    47,    37,
      52,     0,     0,     0,    60,     0,     0,    53,    55,    98,
       0,    81,     0,     0,    87,    88,    96,    95,     0,     0,
      84,     0,     0,    63,     0,     0,    57,     0,    54,    80,
       0,     0,     0,    85,     0,    49,    62,    59,    61,    91,
      90,     0,    45,    94
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -152,  -152,  -152,    -1,  -152,  -152,  -152,  -152,  -152,  -152,
     239,  -152,   236,   -63,  -152,   226,  -121,   -83,  -152,  -114,
    -152,  -152,  -152,    83,  -152,   194,   198,  -152,   210,  -152,
     137,  -152,    44,  -152,   237,  -151,   248,   185,  -152,  -152,
    -152,  -152,  -152,  -152,   113,  -152,  -152,  -152,  -152,  -152,
     201,   -20,   243,   111,   -24
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,     8,     9,    19,    27,    72,    16,
      52,    12,    13,    38,    24,    25,   120,   121,   122,    67,
     123,   124,   168,   169,    68,    69,    73,    74,    75,    76,
     175,   203,   204,   205,    22,    53,    54,    55,    56,    57,
      58,   220,    59,   187,   188,    60,    61,    62,   218,    63,
     136,   137,    40,    41,    42
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,   119,   165,     1,   167,   173,    66,    77,   190,    78,
     192,    80,    43,    82,     4,    79,    81,   111,    70,   104,
      66,     5,   180,    90,    91,   102,   112,   113,   181,   106,
     114,   108,    28,    29,    30,    71,    31,    32,    33,   115,
     180,   125,   126,    28,    29,    30,   184,    31,    32,    33,
      34,    43,    35,   125,   167,   116,   197,   134,    44,   194,
     202,   230,   231,   119,   117,     6,    36,    43,   233,   148,
     149,   150,   151,   152,    44,   222,    92,   201,   153,    10,
     225,   156,    11,   195,   226,    15,    45,   223,   125,   196,
     243,    83,    84,    85,   186,    14,    47,   118,    48,    49,
      37,    15,    45,   119,    87,    88,    89,   199,   125,   224,
      46,   202,    47,   242,    48,    49,    15,    20,    50,    18,
     216,    43,    23,   228,   186,    26,    64,   160,    44,    66,
      51,   177,   178,   119,    50,    83,    84,    85,   189,   103,
     191,   236,   128,   119,   238,   162,    51,   109,    87,    88,
      89,   129,   217,   110,   158,    15,    45,    98,   135,    99,
     209,   119,   154,   211,   119,   100,    47,   132,    48,    49,
     101,   119,    15,    45,   133,    93,    94,   164,    83,    84,
      85,   170,   166,    47,   171,    48,    49,   172,    50,   183,
     229,    87,    88,    89,   174,   159,    95,   193,   232,   200,
      51,   145,   146,   147,    96,    50,    28,    29,    30,   207,
      31,    32,    33,   185,   111,   206,   210,    51,   208,   212,
      97,   213,   227,   112,   113,   157,   219,   114,   221,    28,
      29,    30,   234,    31,    32,    33,   115,   235,   125,   239,
      83,    84,    85,    83,    84,    85,   240,    17,    21,   214,
      65,   198,   116,    87,    88,    89,    87,    88,    89,    83,
      84,    85,   127,    83,    84,    85,   176,    86,   161,   237,
     130,   241,    87,    88,    89,   138,    87,    88,    89,    83,
      84,    85,   131,   179,    83,    84,    85,   107,   182,    83,
      84,    85,    87,    88,    89,   163,   105,    87,    88,    89,
     215,   155,    87,    88,    89,    98,     0,    99,     0,   -69,
      28,    29,    30,   100,    31,    32,    33,   185,   101,    28,
      29,    30,     0,    31,    32,    33,   139,   140,   141,     0,
     142,   143,   144
};

static const yytype_int16 yycheck[] =
{
      20,    64,   116,    84,   118,   126,    27,    35,   159,    37,
     161,    35,    20,    37,    27,    43,    36,     5,    66,    27,
      27,     0,    38,    28,    29,    45,    14,    15,    44,    49,
      18,    51,    20,    21,    22,    83,    24,    25,    26,    27,
      38,    38,    39,    20,    21,    22,    44,    24,    25,    26,
      27,    20,    29,    38,   168,    43,    63,    77,    27,    44,
     174,   212,   213,   126,    52,    56,    43,    20,   219,    93,
      94,    95,    96,    97,    27,   196,    81,    98,    98,    40,
      40,   101,    27,   166,    44,    54,    55,   201,    38,    39,
     241,    32,    33,    34,   157,    37,    65,    85,    67,    68,
      77,    54,    55,   166,    45,    46,    47,   170,    38,    39,
      63,   225,    65,   234,    67,    68,    54,    32,    87,    94,
      61,    20,    27,   206,   187,    98,    32,    96,    27,    27,
      99,   132,   133,   196,    87,    32,    33,    34,   158,    27,
     160,   224,    27,   206,   227,    27,    99,    40,    45,    46,
      47,    27,    93,    39,    48,    54,    55,    35,    27,    37,
     180,   224,    27,   183,   227,    43,    65,    40,    67,    68,
      48,   234,    54,    55,    40,    30,    31,    49,    32,    33,
      34,    49,    35,    65,    40,    67,    68,    27,    87,    48,
     210,    45,    46,    47,    43,    92,    51,    27,   218,    40,
      99,    90,    91,    92,    59,    87,    20,    21,    22,    40,
      24,    25,    26,    27,     5,    39,    48,    99,    40,    39,
      75,    39,    39,    14,    15,    79,    62,    18,    36,    20,
      21,    22,    79,    24,    25,    26,    27,    40,    38,    40,
      32,    33,    34,    32,    33,    34,    40,     8,    12,    63,
      24,   168,    43,    45,    46,    47,    45,    46,    47,    32,
      33,    34,    68,    32,    33,    34,   129,    40,    60,   225,
      72,    60,    45,    46,    47,    44,    45,    46,    47,    32,
      33,    34,    72,    36,    32,    33,    34,    50,    36,    32,
      33,    34,    45,    46,    47,   110,    48,    45,    46,    47,
     187,   100,    45,    46,    47,    35,    -1,    37,    -1,    39,
      20,    21,    22,    43,    24,    25,    26,    27,    48,    20,
      21,    22,    -1,    24,    25,    26,    83,    84,    85,    -1,
      87,    88,    89
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    84,   104,   105,    27,     0,    56,   106,   107,   108,
      40,    27,   114,   115,    37,    54,   112,   113,    94,   109,
      32,   115,   137,    27,   117,   118,    98,   110,    20,    21,
      22,    24,    25,    26,    27,    29,    43,    77,   116,   154,
     155,   156,   157,    20,    27,    55,    63,    65,    67,    68,
      87,    99,   113,   138,   139,   140,   141,   142,   143,   145,
     148,   149,   150,   152,    32,   118,    27,   122,   127,   128,
      66,    83,   111,   129,   130,   131,   132,    35,    37,    43,
     157,   154,   157,    32,    33,    34,    40,    45,    46,    47,
      28,    29,    81,    30,    31,    51,    59,    75,    35,    37,
      43,    48,   154,    27,    27,   139,   154,   137,   154,    40,
      39,     5,    14,    15,    18,    27,    43,    52,    85,   116,
     119,   120,   121,   123,   124,    38,    39,   128,    27,    27,
     129,   131,    40,    40,   154,    27,   153,   154,    44,   155,
     155,   155,   155,   155,   155,   156,   156,   156,   157,   157,
     157,   157,   157,   154,    27,   153,   154,    79,    48,    92,
      96,    60,    27,   140,    49,   122,    35,   122,   125,   126,
      49,    40,    27,   119,    43,   133,   133,   106,   106,    36,
      38,    44,    36,    48,    44,    27,   116,   146,   147,   154,
     138,   154,   138,    27,    44,   120,    39,    63,   126,   116,
      40,    98,   122,   134,   135,   136,    39,    40,    40,   154,
      48,   154,    39,    39,    63,   147,    61,    93,   151,    62,
     144,    36,   119,   122,    39,    40,    44,    39,   120,   154,
     138,   138,   154,   138,    79,    40,   120,   135,   120,    40,
      40,    60,   119,   138
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   103,   104,   105,   106,   107,   108,   108,   109,   109,
     110,   110,   111,   111,   111,   111,   111,   112,   113,   114,
     114,   115,   116,   116,   116,   116,   116,   116,   117,   117,
     118,   119,   119,   119,   120,   120,   120,   120,   120,   121,
     121,   121,   121,   122,   122,   123,   124,   125,   125,   126,
     127,   127,   128,   129,   130,   131,   132,   133,   133,   134,
     134,   135,   135,   136,   137,   137,   138,   138,   139,   139,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   141,
     141,   141,   142,   142,   143,   144,   144,   145,   146,   146,
     147,   147,   148,   149,   150,   151,   151,   152,   153,   153,
     154,   154,   154,   154,   154,   154,   154,   155,   155,   155,
     155,   156,   156,   156,   156,   156,   156,   157,   157,   157,
     157,   157,   157,   157,   157
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     3,     2,     4,     2,     0,     2,     0,
       2,     0,     2,     2,     1,     1,     0,     1,     3,     2,
       1,     4,     1,     1,     1,     1,     1,     1,     2,     1,
       4,     1,     1,     1,     1,     1,     3,     3,     3,     1,
       1,     1,     1,     3,     1,     6,     3,     2,     1,     4,
       2,     1,     4,     4,     5,     4,     3,     3,     0,     3,
       1,     3,     3,     2,     3,     0,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       6,     5,     1,     4,     5,     2,     0,     5,     2,     1,
       4,     4,     4,     4,     8,     1,     1,     2,     3,     1,
       3,     3,     3,     3,     3,     3,     1,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     1,     1,     4,     1,
       3,     2,     2,     4,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 170 "parser/pascal.y"
                                {
        //root of the ast, a global variable;
        ast_root = new AST_Program((yyvsp[-2].ast_program_head),(yyvsp[-1].ast_routine));
        SET_LOCATION(ast_root);
    }
#line 1923 "pascal.y.cpp"
    break;

  case 3:
#line 178 "parser/pascal.y"
                                        {
        (yyval.ast_program_head) = new AST_Program_Head((yyvsp[-1].str));
        SET_LOCATION((yyval.ast_program_head));
    }
#line 1932 "pascal.y.cpp"
    break;

  case 4:
#line 185 "parser/pascal.y"
                             {
        // function_decl and procedure_decl
        (yyval.ast_routine) = new AST_Routine((yyvsp[-1].ast_routine_head),(yyvsp[0].ast_routine_body));
        SET_LOCATION((yyval.ast_routine));
    }
#line 1942 "pascal.y.cpp"
    break;

  case 5:
#line 193 "parser/pascal.y"
                                              {
        (yyval.ast_routine_head) = new AST_Routine_Head((yyvsp[-3].ast_const_part),(yyvsp[-2].ast_type_part),(yyvsp[-1].ast_variable_part),(yyvsp[0].ast_routine_part));
        SET_LOCATION((yyval.ast_routine_head));
    }
#line 1951 "pascal.y.cpp"
    break;

  case 6:
#line 200 "parser/pascal.y"
                              {
        (yyval.ast_const_part) = new AST_Const_Part((yyvsp[0].ast_const_expression_list));
        SET_LOCATION((yyval.ast_const_part));
    }
#line 1960 "pascal.y.cpp"
    break;

  case 7:
#line 204 "parser/pascal.y"
      {
        (yyval.ast_const_part) = nullptr;
    }
#line 1968 "pascal.y.cpp"
    break;

  case 8:
#line 210 "parser/pascal.y"
                            {
        (yyval.ast_type_part) = new AST_Type_Part((yyvsp[0].ast_type_declaration_list));
        SET_LOCATION((yyval.ast_type_part));
    }
#line 1977 "pascal.y.cpp"
    break;

  case 9:
#line 214 "parser/pascal.y"
      {
        (yyval.ast_type_part) = nullptr;
    }
#line 1985 "pascal.y.cpp"
    break;

  case 10:
#line 220 "parser/pascal.y"
                          {
        (yyval.ast_variable_part) = new AST_Variable_Part((yyvsp[0].ast_variable_declaration_list));
        SET_LOCATION((yyval.ast_variable_part));
    }
#line 1994 "pascal.y.cpp"
    break;

  case 11:
#line 224 "parser/pascal.y"
      {
        (yyval.ast_variable_part) = nullptr;
    }
#line 2002 "pascal.y.cpp"
    break;

  case 12:
#line 230 "parser/pascal.y"
                               {
        AST_Declaration_BaseClass* tmp1 = new AST_Declaration_BaseClass((yyvsp[0].ast_function_declaration));
        ((yyvsp[-1].ast_routine_part)) -> Add_Declaration(tmp1);
        (yyval.ast_routine_part) = (yyvsp[-1].ast_routine_part);
        SET_LOCATION((yyval.ast_routine_part));
    }
#line 2013 "pascal.y.cpp"
    break;

  case 13:
#line 236 "parser/pascal.y"
                                  {
        AST_Declaration_BaseClass* tmp2 = new AST_Declaration_BaseClass((yyvsp[0].ast_procedure_declaration));
        ((yyvsp[-1].ast_routine_part)) -> Add_Declaration(tmp2);
        (yyval.ast_routine_part) = (yyvsp[-1].ast_routine_part);
        SET_LOCATION((yyval.ast_routine_part));
    }
#line 2024 "pascal.y.cpp"
    break;

  case 14:
#line 242 "parser/pascal.y"
                    {
        AST_Declaration_BaseClass* tmp3 = new AST_Declaration_BaseClass((yyvsp[0].ast_function_declaration));
        (yyval.ast_routine_part) = new AST_Routine_Part(tmp3);
        SET_LOCATION((yyval.ast_routine_part));
    }
#line 2034 "pascal.y.cpp"
    break;

  case 15:
#line 247 "parser/pascal.y"
                     {
        AST_Declaration_BaseClass* tmp4 = new AST_Declaration_BaseClass((yyvsp[0].ast_procedure_declaration));
        (yyval.ast_routine_part) = new AST_Routine_Part(tmp4);
        SET_LOCATION((yyval.ast_routine_part));
    }
#line 2044 "pascal.y.cpp"
    break;

  case 16:
#line 252 "parser/pascal.y"
      {
        (yyval.ast_routine_part) = nullptr;
    }
#line 2052 "pascal.y.cpp"
    break;

  case 17:
#line 258 "parser/pascal.y"
                  {
        (yyval.ast_routine_body) = new AST_Routine_Body((yyvsp[0].ast_compound_statement));
        SET_LOCATION((yyval.ast_routine_body));
    }
#line 2061 "pascal.y.cpp"
    break;

  case 18:
#line 265 "parser/pascal.y"
                               {
        (yyval.ast_compound_statement) = new AST_Compound_Statement((yyvsp[-1].ast_statement_list));
        SET_LOCATION((yyval.ast_compound_statement));
    }
#line 2070 "pascal.y.cpp"
    break;

  case 19:
#line 272 "parser/pascal.y"
                               {
        ((yyvsp[-1].ast_const_expression_list))->Add_Const_Expression((yyvsp[0].ast_const_expression));
        (yyval.ast_const_expression_list) = (yyvsp[-1].ast_const_expression_list);
        SET_LOCATION((yyval.ast_const_expression_list));
    }
#line 2080 "pascal.y.cpp"
    break;

  case 20:
#line 277 "parser/pascal.y"
                 {
        (yyval.ast_const_expression_list) = new AST_Const_Expression_List();
        ((yyval.ast_const_expression_list))->Add_Const_Expression((yyvsp[0].ast_const_expression));
        SET_LOCATION((yyval.ast_const_expression_list));
    }
#line 2090 "pascal.y.cpp"
    break;

  case 21:
#line 285 "parser/pascal.y"
                                               {
        (yyval.ast_const_expression) = new AST_Const_Expression((yyvsp[-3].str),(yyvsp[-1].ast_expression));
        SET_LOCATION((yyval.ast_const_expression));
    }
#line 2099 "pascal.y.cpp"
    break;

  case 22:
#line 292 "parser/pascal.y"
                {
        (yyval.ast_const_value) = new AST_Const_Value((yyvsp[0].str),AST_Const_Value::Value_Type::INT);
        SET_LOCATION((yyval.ast_const_value));
    }
#line 2108 "pascal.y.cpp"
    break;

  case 23:
#line 296 "parser/pascal.y"
                    {
        (yyval.ast_const_value) = new AST_Const_Value((yyvsp[0].str),AST_Const_Value::Value_Type::FLOAT);
        SET_LOCATION((yyval.ast_const_value));
    }
#line 2117 "pascal.y.cpp"
    break;

  case 24:
#line 300 "parser/pascal.y"
                   {
        (yyval.ast_const_value) = new AST_Const_Value((yyvsp[0].str),AST_Const_Value::Value_Type::CHAR);
        SET_LOCATION((yyval.ast_const_value));
    }
#line 2126 "pascal.y.cpp"
    break;

  case 25:
#line 304 "parser/pascal.y"
                  {
        (yyval.ast_const_value) = new AST_Const_Value((yyvsp[0].str),AST_Const_Value::Value_Type::STRING);
        SET_LOCATION((yyval.ast_const_value));
    }
#line 2135 "pascal.y.cpp"
    break;

  case 26:
#line 308 "parser/pascal.y"
                    {
        (yyval.ast_const_value) = new AST_Const_Value((yyvsp[0].str),AST_Const_Value::Value_Type::FALSE);
        SET_LOCATION((yyval.ast_const_value));
    }
#line 2144 "pascal.y.cpp"
    break;

  case 27:
#line 312 "parser/pascal.y"
                   {
        (yyval.ast_const_value) = new AST_Const_Value((yyvsp[0].str),AST_Const_Value::Value_Type::TRUE);
        SET_LOCATION((yyval.ast_const_value));
    }
#line 2153 "pascal.y.cpp"
    break;

  case 28:
#line 319 "parser/pascal.y"
                                   {
        ((yyvsp[-1].ast_type_declaration_list)) -> Add_Type_Definition((yyvsp[0].ast_type_definition));
        (yyval.ast_type_declaration_list) = (yyvsp[-1].ast_type_declaration_list);
        SET_LOCATION((yyval.ast_type_declaration_list));
    }
#line 2163 "pascal.y.cpp"
    break;

  case 29:
#line 324 "parser/pascal.y"
                      {
        (yyval.ast_type_declaration_list) = new AST_Type_Declaration_List();
        ((yyval.ast_type_declaration_list)) -> Add_Type_Definition((yyvsp[0].ast_type_definition));
        SET_LOCATION((yyval.ast_type_declaration_list));
    }
#line 2173 "pascal.y.cpp"
    break;

  case 30:
#line 332 "parser/pascal.y"
                                              {
        (yyval.ast_type_definition) = new AST_Type_Definition((yyvsp[-3].str),(yyvsp[-1].ast_type_declaration));
        SET_LOCATION((yyval.ast_type_definition));
    }
#line 2182 "pascal.y.cpp"
    break;

  case 31:
#line 339 "parser/pascal.y"
                     {
        (yyval.ast_type_declaration) = (yyvsp[0].ast_simple_type_declaration);
        SET_LOCATION((yyval.ast_type_declaration));
    }
#line 2191 "pascal.y.cpp"
    break;

  case 32:
#line 343 "parser/pascal.y"
                       {
        (yyval.ast_type_declaration) = (yyvsp[0].ast_array_type_declaration);
        SET_LOCATION((yyval.ast_type_declaration));
    }
#line 2200 "pascal.y.cpp"
    break;

  case 33:
#line 347 "parser/pascal.y"
                       {
        (yyval.ast_type_declaration) = (yyvsp[0].ast_record_type_declaration);
        SET_LOCATION((yyval.ast_type_declaration));
    }
#line 2209 "pascal.y.cpp"
    break;

  case 34:
#line 354 "parser/pascal.y"
              {
        (yyval.ast_simple_type_declaration) = new AST_Simple_Type_Declaration((yyvsp[0].ast_type));
        SET_LOCATION((yyval.ast_simple_type_declaration));
    }
#line 2218 "pascal.y.cpp"
    break;

  case 35:
#line 358 "parser/pascal.y"
                 {
        (yyval.ast_simple_type_declaration) = new AST_Simple_Type_Declaration((yyvsp[0].str));
        SET_LOCATION((yyval.ast_simple_type_declaration));
    }
#line 2227 "pascal.y.cpp"
    break;

  case 36:
#line 362 "parser/pascal.y"
                                      {
        (yyval.ast_simple_type_declaration) = new AST_Simple_Type_Declaration((yyvsp[-1].ast_name_list));
        SET_LOCATION((yyval.ast_simple_type_declaration));
    }
#line 2236 "pascal.y.cpp"
    break;

  case 37:
#line 366 "parser/pascal.y"
                                           {
        (yyval.ast_simple_type_declaration) = new AST_Simple_Type_Declaration((yyvsp[-2].ast_const_value),(yyvsp[0].ast_const_value));
        SET_LOCATION((yyval.ast_simple_type_declaration));
    }
#line 2245 "pascal.y.cpp"
    break;

  case 38:
#line 370 "parser/pascal.y"
                                         {
        (yyval.ast_simple_type_declaration) = new AST_Simple_Type_Declaration((yyvsp[-2].str),(yyvsp[0].str));
        SET_LOCATION((yyval.ast_simple_type_declaration));
    }
#line 2254 "pascal.y.cpp"
    break;

  case 39:
#line 377 "parser/pascal.y"
                 {
        (yyval.ast_type) = new AST_Type(AST_Type::Type_Name::BOOLEAN);
        SET_LOCATION((yyval.ast_type));
    }
#line 2263 "pascal.y.cpp"
    break;

  case 40:
#line 381 "parser/pascal.y"
                 {
        (yyval.ast_type) = new AST_Type(AST_Type::Type_Name::CHAR);
        SET_LOCATION((yyval.ast_type));
    }
#line 2272 "pascal.y.cpp"
    break;

  case 41:
#line 385 "parser/pascal.y"
               {
        (yyval.ast_type) = new AST_Type(AST_Type::Type_Name::INT);
        SET_LOCATION((yyval.ast_type));
    }
#line 2281 "pascal.y.cpp"
    break;

  case 42:
#line 389 "parser/pascal.y"
                 {
        (yyval.ast_type) = new AST_Type(AST_Type::Type_Name::FLOAT);
        SET_LOCATION((yyval.ast_type));
    }
#line 2290 "pascal.y.cpp"
    break;

  case 43:
#line 396 "parser/pascal.y"
                                   {
        ((yyvsp[-2].ast_name_list)) -> Add_Identifier((yyvsp[0].str));
        (yyval.ast_name_list) = (yyvsp[-2].ast_name_list);
        SET_LOCATION((yyval.ast_name_list));
    }
#line 2300 "pascal.y.cpp"
    break;

  case 44:
#line 401 "parser/pascal.y"
                 {
        (yyval.ast_name_list) = new AST_Name_List();
        ((yyval.ast_name_list)) -> Add_Identifier((yyvsp[0].str));
        SET_LOCATION((yyval.ast_name_list));
    }
#line 2310 "pascal.y.cpp"
    break;

  case 45:
#line 409 "parser/pascal.y"
                                                                    {
        (yyval.ast_array_type_declaration) = new AST_Array_Type_Declaration((yyvsp[-3].ast_simple_type_declaration),(yyvsp[0].ast_type_declaration));
        SET_LOCATION((yyval.ast_array_type_declaration));
    }
#line 2319 "pascal.y.cpp"
    break;

  case 46:
#line 416 "parser/pascal.y"
                                       {
        (yyval.ast_record_type_declaration) = new AST_Record_Type_Declaration((yyvsp[-1].ast_field_declaration_list));
        SET_LOCATION((yyval.ast_record_type_declaration));
    }
#line 2328 "pascal.y.cpp"
    break;

  case 47:
#line 423 "parser/pascal.y"
                               {
        ((yyvsp[-1].ast_field_declaration_list)) -> Add_Field_Declaration((yyvsp[0].ast_field_declaration));
        (yyval.ast_field_declaration_list) = (yyvsp[-1].ast_field_declaration_list);
        SET_LOCATION((yyval.ast_field_declaration_list));
    }
#line 2338 "pascal.y.cpp"
    break;

  case 48:
#line 428 "parser/pascal.y"
                 {
        (yyval.ast_field_declaration_list) = new AST_Field_Declaration_List((yyvsp[0].ast_field_declaration));
        SET_LOCATION((yyval.ast_field_declaration_list));
    }
#line 2347 "pascal.y.cpp"
    break;

  case 49:
#line 435 "parser/pascal.y"
                                                {
        (yyval.ast_field_declaration) = new AST_Field_Declaration((yyvsp[-3].ast_name_list),(yyvsp[-1].ast_type_declaration));
        SET_LOCATION((yyval.ast_field_declaration));
    }
#line 2356 "pascal.y.cpp"
    break;

  case 50:
#line 442 "parser/pascal.y"
                           {
        ((yyvsp[-1].ast_variable_declaration_list)) -> Add_Variable_Declaration((yyvsp[0].ast_variable_declaration));
        (yyval.ast_variable_declaration_list) = (yyvsp[-1].ast_variable_declaration_list);
        SET_LOCATION((yyval.ast_variable_declaration_list));
    }
#line 2366 "pascal.y.cpp"
    break;

  case 51:
#line 447 "parser/pascal.y"
               {
        (yyval.ast_variable_declaration_list) = new AST_Variable_Declaration_List();
        ((yyval.ast_variable_declaration_list)) -> Add_Variable_Declaration((yyvsp[0].ast_variable_declaration));
        SET_LOCATION((yyval.ast_variable_declaration_list));
    }
#line 2376 "pascal.y.cpp"
    break;

  case 52:
#line 455 "parser/pascal.y"
                                                {
        (yyval.ast_variable_declaration) = new AST_Variable_Declaration((yyvsp[-3].ast_name_list),(yyvsp[-1].ast_type_declaration));
        SET_LOCATION((yyval.ast_variable_declaration));
    }
#line 2385 "pascal.y.cpp"
    break;

  case 53:
#line 462 "parser/pascal.y"
                                                      {
        (yyval.ast_function_declaration) = new AST_Function_Declaration((yyvsp[-3].ast_function_head), (yyvsp[-1].ast_routine));
        SET_LOCATION((yyval.ast_function_declaration));
    }
#line 2394 "pascal.y.cpp"
    break;

  case 54:
#line 469 "parser/pascal.y"
                                                                  {
        (yyval.ast_function_head) = new AST_Function_Head((yyvsp[-3].str), (yyvsp[-2].ast_parameters), (yyvsp[0].ast_simple_type_declaration));
        SET_LOCATION((yyval.ast_function_head));
    }
#line 2403 "pascal.y.cpp"
    break;

  case 55:
#line 476 "parser/pascal.y"
                                                       {
        (yyval.ast_procedure_declaration) = new AST_Procedure_Declaration((yyvsp[-3].ast_procedure_head), (yyvsp[-1].ast_routine));
        SET_LOCATION((yyval.ast_procedure_declaration));
    }
#line 2412 "pascal.y.cpp"
    break;

  case 56:
#line 483 "parser/pascal.y"
                                        {
        (yyval.ast_procedure_head) = new AST_Procedure_Head((yyvsp[-1].str), (yyvsp[0].ast_parameters));
        SET_LOCATION((yyval.ast_procedure_head));
    }
#line 2421 "pascal.y.cpp"
    break;

  case 57:
#line 490 "parser/pascal.y"
                                         {
        (yyval.ast_parameters) = new AST_Parameters((yyvsp[-1].ast_parameters_declaration_list));
        SET_LOCATION((yyval.ast_parameters));
    }
#line 2430 "pascal.y.cpp"
    break;

  case 58:
#line 494 "parser/pascal.y"
      {
        (yyval.ast_parameters) = new AST_Parameters();
        SET_LOCATION((yyval.ast_parameters));
    }
#line 2439 "pascal.y.cpp"
    break;

  case 59:
#line 501 "parser/pascal.y"
                                                {
        ((yyvsp[-2].ast_parameters_declaration_list)) -> Add_Parameters_Type_List((yyvsp[0].ast_parameters_type_list));
        (yyval.ast_parameters_declaration_list) = (yyvsp[-2].ast_parameters_declaration_list);
        SET_LOCATION((yyval.ast_parameters_declaration_list));
    }
#line 2449 "pascal.y.cpp"
    break;

  case 60:
#line 506 "parser/pascal.y"
                     {
        (yyval.ast_parameters_declaration_list) = new AST_Parameters_Declaration_List((yyvsp[0].ast_parameters_type_list));
        SET_LOCATION((yyval.ast_parameters_declaration_list));
    }
#line 2458 "pascal.y.cpp"
    break;

  case 61:
#line 513 "parser/pascal.y"
                                             {
        (yyval.ast_parameters_type_list) = new AST_Parameters_Type_List((yyvsp[-2].ast_variable_parameters_list),(yyvsp[0].ast_simple_type_declaration));
        SET_LOCATION((yyval.ast_parameters_type_list));
    }
#line 2467 "pascal.y.cpp"
    break;

  case 62:
#line 517 "parser/pascal.y"
                                           {
        (yyval.ast_parameters_type_list) = new AST_Parameters_Type_List((yyvsp[-2].ast_name_list),(yyvsp[0].ast_simple_type_declaration));
        SET_LOCATION((yyval.ast_parameters_type_list));
    }
#line 2476 "pascal.y.cpp"
    break;

  case 63:
#line 524 "parser/pascal.y"
                      {
        (yyval.ast_variable_parameters_list) = new AST_Variable_Parameters_List((yyvsp[0].ast_name_list));
        SET_LOCATION((yyval.ast_variable_parameters_list));
    }
#line 2485 "pascal.y.cpp"
    break;

  case 64:
#line 531 "parser/pascal.y"
                                 {
        ((yyvsp[-2].ast_statement_list)) -> Add_Statement((yyvsp[-1].ast_statement));
        (yyval.ast_statement_list) = (yyvsp[-2].ast_statement_list);
        SET_LOCATION((yyval.ast_statement_list));
    }
#line 2495 "pascal.y.cpp"
    break;

  case 65:
#line 536 "parser/pascal.y"
      {
        (yyval.ast_statement_list) = new AST_Statement_List();
        SET_LOCATION((yyval.ast_statement_list));
    }
#line 2504 "pascal.y.cpp"
    break;

  case 66:
#line 543 "parser/pascal.y"
                                   {
        (yyval.ast_statement) = new AST_Statement();
        ((yyval.ast_statement)) -> Add_Label_and_Non_Label_Statement((yyvsp[-2].ast_label),(yyvsp[0].ast_non_label_statement));
        SET_LOCATION((yyval.ast_statement));
    }
#line 2514 "pascal.y.cpp"
    break;

  case 67:
#line 548 "parser/pascal.y"
                     {
        (yyval.ast_statement) = new AST_Statement();
        ((yyval.ast_statement)) -> Add_Non_Label_Statement((yyvsp[0].ast_non_label_statement));
        SET_LOCATION((yyval.ast_statement));
    }
#line 2524 "pascal.y.cpp"
    break;

  case 68:
#line 556 "parser/pascal.y"
                {
        (yyval.ast_label) = new AST_Label((yyvsp[0].str));
        SET_LOCATION((yyval.ast_label));
    }
#line 2533 "pascal.y.cpp"
    break;

  case 69:
#line 560 "parser/pascal.y"
                 {
        (yyval.ast_label) = new AST_Label((yyvsp[0].str));
        SET_LOCATION((yyval.ast_label));
    }
#line 2542 "pascal.y.cpp"
    break;

  case 70:
#line 567 "parser/pascal.y"
                {
        (yyval.ast_non_label_statement) = new AST_Non_Label_Statement((yyvsp[0].ast_assign_statement));
        SET_LOCATION((yyval.ast_non_label_statement));
    }
#line 2551 "pascal.y.cpp"
    break;

  case 71:
#line 571 "parser/pascal.y"
                {
        (yyval.ast_non_label_statement) = new AST_Non_Label_Statement((yyvsp[0].ast_procedure_statement));
        SET_LOCATION((yyval.ast_non_label_statement));
    }
#line 2560 "pascal.y.cpp"
    break;

  case 72:
#line 575 "parser/pascal.y"
                    {
        (yyval.ast_non_label_statement) = new AST_Non_Label_Statement((yyvsp[0].ast_compound_statement));
        SET_LOCATION((yyval.ast_non_label_statement));
    }
#line 2569 "pascal.y.cpp"
    break;

  case 73:
#line 579 "parser/pascal.y"
              {
        (yyval.ast_non_label_statement) = new AST_Non_Label_Statement((yyvsp[0].ast_if_statement));
        SET_LOCATION((yyval.ast_non_label_statement));
    }
#line 2578 "pascal.y.cpp"
    break;

  case 74:
#line 583 "parser/pascal.y"
                {
        (yyval.ast_non_label_statement) = new AST_Non_Label_Statement((yyvsp[0].ast_case_statement));
        SET_LOCATION((yyval.ast_non_label_statement));
    }
#line 2587 "pascal.y.cpp"
    break;

  case 75:
#line 587 "parser/pascal.y"
                  {
        (yyval.ast_non_label_statement) = new AST_Non_Label_Statement((yyvsp[0].ast_repeat_statement));
        SET_LOCATION((yyval.ast_non_label_statement));
    }
#line 2596 "pascal.y.cpp"
    break;

  case 76:
#line 591 "parser/pascal.y"
                 {
        (yyval.ast_non_label_statement) = new AST_Non_Label_Statement((yyvsp[0].ast_while_statement));
        SET_LOCATION((yyval.ast_non_label_statement));
    }
#line 2605 "pascal.y.cpp"
    break;

  case 77:
#line 595 "parser/pascal.y"
               {
        (yyval.ast_non_label_statement) = new AST_Non_Label_Statement((yyvsp[0].ast_for_statement));
        SET_LOCATION((yyval.ast_non_label_statement));
    }
#line 2614 "pascal.y.cpp"
    break;

  case 78:
#line 599 "parser/pascal.y"
                {
        (yyval.ast_non_label_statement) = new AST_Non_Label_Statement((yyvsp[0].ast_goto_statement));
        SET_LOCATION((yyval.ast_non_label_statement));
    }
#line 2623 "pascal.y.cpp"
    break;

  case 79:
#line 606 "parser/pascal.y"
                                     {
        (yyval.ast_assign_statement) = new AST_Assign_Statement((yyvsp[-2].str), (yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_assign_statement));
    }
#line 2632 "pascal.y.cpp"
    break;

  case 80:
#line 610 "parser/pascal.y"
                                                                      {
        (yyval.ast_assign_statement) = new AST_Assign_Statement((yyvsp[-5].str), (yyvsp[-3].ast_expression), (yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_assign_statement));
    }
#line 2641 "pascal.y.cpp"
    break;

  case 81:
#line 614 "parser/pascal.y"
                                                             {
        (yyval.ast_assign_statement) = new AST_Assign_Statement((yyvsp[-4].str), (yyvsp[-2].str), (yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_assign_statement));
    }
#line 2650 "pascal.y.cpp"
    break;

  case 82:
#line 623 "parser/pascal.y"
               {
        (yyval.ast_procedure_statement) = new AST_Procedure_Statement((yyvsp[0].str));
        SET_LOCATION((yyval.ast_procedure_statement));
    }
#line 2659 "pascal.y.cpp"
    break;

  case 83:
#line 627 "parser/pascal.y"
                                                       {
        (yyval.ast_procedure_statement) = new AST_Procedure_Statement((yyvsp[-3].str),(yyvsp[-1].ast_expression_list));
        SET_LOCATION((yyval.ast_procedure_statement));
    }
#line 2668 "pascal.y.cpp"
    break;

  case 84:
#line 635 "parser/pascal.y"
                                                {
        (yyval.ast_if_statement) = new AST_If_Statement((yyvsp[-3].ast_expression),(yyvsp[-1].ast_statement),(yyvsp[0].ast_else_clause));
        SET_LOCATION((yyval.ast_if_statement));
    }
#line 2677 "pascal.y.cpp"
    break;

  case 85:
#line 642 "parser/pascal.y"
                  {
        (yyval.ast_else_clause) = new AST_Else_Clause((yyvsp[0].ast_statement));
        SET_LOCATION((yyval.ast_else_clause));
    }
#line 2686 "pascal.y.cpp"
    break;

  case 86:
#line 646 "parser/pascal.y"
      {
        (yyval.ast_else_clause) = nullptr;
    }
#line 2694 "pascal.y.cpp"
    break;

  case 87:
#line 652 "parser/pascal.y"
                                                      {
        (yyval.ast_case_statement) = new AST_Case_Statement((yyvsp[-3].ast_expression),(yyvsp[-1].ast_case_expression_list));
        SET_LOCATION((yyval.ast_case_statement));
    }
#line 2703 "pascal.y.cpp"
    break;

  case 88:
#line 659 "parser/pascal.y"
                             {
        ((yyvsp[-1].ast_case_expression_list))->Add_Case_Expression((yyvsp[0].ast_case_expression));
        (yyval.ast_case_expression_list) = (yyvsp[-1].ast_case_expression_list);
        SET_LOCATION((yyval.ast_case_expression_list));
    }
#line 2713 "pascal.y.cpp"
    break;

  case 89:
#line 664 "parser/pascal.y"
                {
        (yyval.ast_case_expression_list) = new AST_Case_Expression_List();
        ((yyval.ast_case_expression_list))->Add_Case_Expression((yyvsp[0].ast_case_expression));
        SET_LOCATION((yyval.ast_case_expression_list));
    }
#line 2723 "pascal.y.cpp"
    break;

  case 90:
#line 672 "parser/pascal.y"
                                             {
        (yyval.ast_case_expression) = new AST_Case_Expression((yyvsp[-3].ast_const_value),(yyvsp[-1].ast_statement));
        SET_LOCATION((yyval.ast_case_expression));
    }
#line 2732 "pascal.y.cpp"
    break;

  case 91:
#line 676 "parser/pascal.y"
                                              {
        (yyval.ast_case_expression) = new AST_Case_Expression((yyvsp[-3].str),(yyvsp[-1].ast_statement));
        SET_LOCATION((yyval.ast_case_expression));
    }
#line 2741 "pascal.y.cpp"
    break;

  case 92:
#line 683 "parser/pascal.y"
                                              {
        (yyval.ast_repeat_statement) = new AST_Repeat_Statement((yyvsp[-2].ast_statement_list),(yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_repeat_statement));
    }
#line 2750 "pascal.y.cpp"
    break;

  case 93:
#line 690 "parser/pascal.y"
                                     {
        (yyval.ast_while_statement) = new AST_While_Statement((yyvsp[-2].ast_expression),(yyvsp[0].ast_statement));
        SET_LOCATION((yyval.ast_while_statement));
    }
#line 2759 "pascal.y.cpp"
    break;

  case 94:
#line 697 "parser/pascal.y"
                                                                              {
        (yyval.ast_for_statement) = new AST_For_Statement((yyvsp[-6].str), (yyvsp[-4].ast_expression), (yyvsp[-3].ast_direction), (yyvsp[-2].ast_expression), (yyvsp[0].ast_statement));
        SET_LOCATION((yyval.ast_for_statement));
    }
#line 2768 "pascal.y.cpp"
    break;

  case 95:
#line 704 "parser/pascal.y"
           {
        (yyval.ast_direction) = new AST_Direction();
        ((yyval.ast_direction)) -> Set_To();
        SET_LOCATION((yyval.ast_direction));
    }
#line 2778 "pascal.y.cpp"
    break;

  case 96:
#line 709 "parser/pascal.y"
                 {
        (yyval.ast_direction) = new AST_Direction();
        ((yyval.ast_direction)) -> Set_Down_To();
        SET_LOCATION((yyval.ast_direction));
    }
#line 2788 "pascal.y.cpp"
    break;

  case 97:
#line 717 "parser/pascal.y"
                   {
        (yyval.ast_goto_statement) = new AST_Goto_Statement((yyvsp[0].ast_label));
        SET_LOCATION((yyval.ast_goto_statement));
    }
#line 2797 "pascal.y.cpp"
    break;

  case 98:
#line 724 "parser/pascal.y"
                                        {
        (yyval.ast_expression_list) = (yyvsp[-2].ast_expression_list);
        (yyval.ast_expression_list) -> Add_Expression((yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression_list));
    }
#line 2807 "pascal.y.cpp"
    break;

  case 99:
#line 729 "parser/pascal.y"
                 {
        (yyval.ast_expression_list) = new AST_Expression_List();
        (yyval.ast_expression_list) -> Add_Expression((yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression_list));
    }
#line 2817 "pascal.y.cpp"
    break;

  case 100:
#line 737 "parser/pascal.y"
                          {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::GE, (yyvsp[-2].ast_expression), (yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2826 "pascal.y.cpp"
    break;

  case 101:
#line 741 "parser/pascal.y"
                             {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::GT, (yyvsp[-2].ast_expression), (yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2835 "pascal.y.cpp"
    break;

  case 102:
#line 745 "parser/pascal.y"
                             {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::LE, (yyvsp[-2].ast_expression), (yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2844 "pascal.y.cpp"
    break;

  case 103:
#line 749 "parser/pascal.y"
                             {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::LT, (yyvsp[-2].ast_expression), (yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2853 "pascal.y.cpp"
    break;

  case 104:
#line 753 "parser/pascal.y"
                             {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::EQUAL, (yyvsp[-2].ast_expression), (yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2862 "pascal.y.cpp"
    break;

  case 105:
#line 757 "parser/pascal.y"
                            {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::UNEQUAL, (yyvsp[-2].ast_expression), (yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2871 "pascal.y.cpp"
    break;

  case 106:
#line 761 "parser/pascal.y"
          {
        (yyval.ast_expression) = (yyvsp[0].ast_expression);
        SET_LOCATION((yyval.ast_expression));
    }
#line 2880 "pascal.y.cpp"
    break;

  case 107:
#line 768 "parser/pascal.y"
                      {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::PLUS,(yyvsp[-2].ast_expression),(yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2889 "pascal.y.cpp"
    break;

  case 108:
#line 772 "parser/pascal.y"
                        {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::MINUS,(yyvsp[-2].ast_expression),(yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2898 "pascal.y.cpp"
    break;

  case 109:
#line 776 "parser/pascal.y"
                       {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::OR,(yyvsp[-2].ast_expression),(yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2907 "pascal.y.cpp"
    break;

  case 110:
#line 780 "parser/pascal.y"
           {
        (yyval.ast_expression) = (yyvsp[0].ast_expression);
        SET_LOCATION((yyval.ast_expression));
    }
#line 2916 "pascal.y.cpp"
    break;

  case 111:
#line 787 "parser/pascal.y"
                        {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::MUL,(yyvsp[-2].ast_expression),(yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2925 "pascal.y.cpp"
    break;

  case 112:
#line 791 "parser/pascal.y"
                          {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::DIV,(yyvsp[-2].ast_expression),(yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2934 "pascal.y.cpp"
    break;

  case 113:
#line 795 "parser/pascal.y"
                           {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::DIV,(yyvsp[-2].ast_expression),(yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2943 "pascal.y.cpp"
    break;

  case 114:
#line 799 "parser/pascal.y"
                            {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::MOD,(yyvsp[-2].ast_expression),(yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2952 "pascal.y.cpp"
    break;

  case 115:
#line 803 "parser/pascal.y"
                          {
        (yyval.ast_expression) = new AST_Binary_Expression(AST_Binary_Expression::Operation::AND,(yyvsp[-2].ast_expression),(yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2961 "pascal.y.cpp"
    break;

  case 116:
#line 807 "parser/pascal.y"
             {
        (yyval.ast_expression) = (yyvsp[0].ast_expression);
        SET_LOCATION((yyval.ast_expression));
    }
#line 2970 "pascal.y.cpp"
    break;

  case 117:
#line 814 "parser/pascal.y"
              {
        (yyval.ast_expression) = new AST_Identifier_Expression((yyvsp[0].str));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2979 "pascal.y.cpp"
    break;

  case 118:
#line 818 "parser/pascal.y"
                                                       {
        (yyval.ast_expression) = new AST_Function_Call((yyvsp[-3].str),(yyvsp[-1].ast_expression_list));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2988 "pascal.y.cpp"
    break;

  case 119:
#line 822 "parser/pascal.y"
                 {
        (yyval.ast_expression) = new AST_Const_Value_Expression((yyvsp[0].ast_const_value));
        SET_LOCATION((yyval.ast_expression));
    }
#line 2997 "pascal.y.cpp"
    break;

  case 120:
#line 826 "parser/pascal.y"
                                      {
        (yyval.ast_expression) = (yyvsp[-1].ast_expression);
        SET_LOCATION((yyval.ast_expression));
    }
#line 3006 "pascal.y.cpp"
    break;

  case 121:
#line 830 "parser/pascal.y"
                    {
        (yyval.ast_expression) = new AST_Unary_Expression(AST_Unary_Expression::Operation::NOT,(yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 3015 "pascal.y.cpp"
    break;

  case 122:
#line 834 "parser/pascal.y"
                    {
        (yyval.ast_expression) = new AST_Unary_Expression(AST_Unary_Expression::Operation::SUB,(yyvsp[0].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 3024 "pascal.y.cpp"
    break;

  case 123:
#line 838 "parser/pascal.y"
                                               {
        (yyval.ast_expression) = new AST_Array_Expression((yyvsp[-3].str),(yyvsp[-1].ast_expression));
        SET_LOCATION((yyval.ast_expression));
    }
#line 3033 "pascal.y.cpp"
    break;

  case 124:
#line 842 "parser/pascal.y"
                                      {
        (yyval.ast_expression) = new AST_Property_Expression((yyvsp[-2].str),(yyvsp[0].str));
        SET_LOCATION((yyval.ast_expression));
    }
#line 3042 "pascal.y.cpp"
    break;


#line 3046 "pascal.y.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 848 "parser/pascal.y"
