%option noyywrap yylineno caseless
%{
#include <cstring>
#define YYSTYPE char*
#include "pascal.y.hpp"

using namespace std;
int yycolumn = 1;
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
	yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;

#ifdef DEBUG_LEXER
#define OUR_RETURN(X) cout << (#X) << endl;
#else
#define OUR_RETURN(X) return(X);
#endif
%}

KEY_AND and
KEY_ARRAY array
KEY_ASM asm
KEY_BEGIN begin
KEY_BREAK break
KEY_CASE case
KEY_CONST const
KEY_CONSTRUCTOR constructor
KEY_DESTRUCTOR destructor
KEY_DIV div
KEY_DO do
KEY_DOWNTO downto
KEY_ELSE else
KEY_END end
KEY_EXIT exit
KEY_FILE file
KEY_FOR for
KEY_FUNCTION function
KEY_GOTO goto
KEY_IF if
KEY_IMPLEMENTATION implementation
KEY_IN in
KEY_INHERITED inherited
KEY_INLINE inline
KEY_INTERFACE interface
KEY_LABEL label
KEY_MOD mod
KEY_NIL nil
KEY_NOT not
KEY_OBJECT object
KEY_OF of
KEY_OPERATOR operator
KEY_OR or
KEY_PACKED packed
KEY_PROCEDURE procedure
KEY_PROGRAM program
KEY_RECORD record
KEY_REINTRODUCE reintroduce
KEY_REPEAT repeat
KEY_SELF self
KEY_SET set
KEY_SHL shl
KEY_SHR shr
KEY_THEN then
KEY_TO to
KEY_TYPE type
KEY_UNIT unit
KEY_UNTIL until
KEY_USES uses
KEY_VAR var
KEY_WHILE while
KEY_WITH with
KEY_XOR xor

TYPE_INT integer
TYPE_INT_8 short
TYPE_INT_16 smallint
TYPE_INT_32 longint
TYPE_INT_64 int64
TYPE_UNSIGNED_INT_8 byte
TYPE_UNSIGNED_INT_16 word
TYPE_UNSIGNED_INT_32 longword
TYPE_UNSIGNED_INT_64 qword
TYPE_BOOLEAN boolean
TYPE_FLOAT real
TYPE_FLOAT_16 single
TYPE_FLOAT_32 double
TYPE_CHAR char|character
TYPE_STRING string
/* Values here*/
SIGN "+"|"-"
LITERAL_TRUE true 
LITERAL_FALSE false
LITERAL_INT {SIGN}?[0-9]|[1-9][0-9]+
LITERAL_FLOAT {SIGN}?([0-9]+\.[0-9]+)|{SIGN}?([0-9]+\.[0-9]+e{SIGN}?[0-9]+)|{SIGN}?([0-9]+e{SIGN}?[0-9]+)
LITERAL_CHAR \'.\'
LITERAL_ESC_CHAR '\'#\'
LITERAL_STR \'([^']|{LITERAL_ESC_CHAR})*\'

/* Pascal symbols here: */
SYM_ADD "+"
SYM_SUB "-"
SYM_MUL "*"
SYM_DIV "/"
SYM_EQ "="
SYM_LT "<"
SYM_GT ">"
SYM_LBRAC "["
SYM_RBRAC "]"
SYM_PERIOD "."
SYM_COMMA ","
SYM_COLON ":"
SYM_SEMICOLON ";"
SYM_AT "@"
SYM_CARET "^"
SYM_LPAREN "("
SYM_RPAREN ")"
SYM_NE "<>"
SYM_LE "<="
SYM_GE ">="
SYM_ASSIGN ":="
SYM_RANGE ".."

/* Other tokens */
COMMENT1 "{"[^\}]*"}" 
COMMENT2 //[^\n]*
COMMENT {COMMENT1} | {COMMENT2}
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
%%

{KEY_AND} {
    OUR_RETURN(KEY_AND)
}

{KEY_ARRAY} {
    OUR_RETURN(KEY_ARRAY)
}

{KEY_ASM} {
    OUR_RETURN(KEY_ASM)
}

{KEY_BEGIN} {
    OUR_RETURN(KEY_BEGIN)
}

{KEY_BREAK} {
    OUR_RETURN(KEY_BREAK)
}

{KEY_CASE} {
    OUR_RETURN(KEY_CASE)
}

{KEY_CONST} {
    OUR_RETURN(KEY_CONST)
}

{KEY_CONSTRUCTOR} {
    OUR_RETURN(KEY_CONSTRUCTOR)
}

{KEY_DESTRUCTOR} {
    OUR_RETURN(KEY_DESTRUCTOR)
}

{KEY_DIV} {
    OUR_RETURN(KEY_DIV)
}

{KEY_DO} {
    OUR_RETURN(KEY_DO)
}

{KEY_DOWNTO} {
    OUR_RETURN(KEY_DOWNTO)
}

{KEY_ELSE} {
    OUR_RETURN(KEY_ELSE)
}

{KEY_END} {
    OUR_RETURN(KEY_END)
}

{KEY_EXIT} {
    OUR_RETURN(KEY_EXIT)
}

{KEY_FILE} {
    OUR_RETURN(KEY_FILE)
}

{KEY_FOR} {
    OUR_RETURN(KEY_FOR)
}

{KEY_FUNCTION} {
    OUR_RETURN(KEY_FUNCTION)
}

{KEY_GOTO} {
    OUR_RETURN(KEY_GOTO)
}

{KEY_IF} {
    OUR_RETURN(KEY_IF)
}

{KEY_IMPLEMENTATION} {
    OUR_RETURN(KEY_IMPLEMENTATION)
}

{KEY_IN} {
    OUR_RETURN(KEY_IN)
}

{KEY_INHERITED} {
    OUR_RETURN(KEY_INHERITED)
}

{KEY_INLINE} {
    OUR_RETURN(KEY_INLINE)
}

{KEY_INTERFACE} {
    OUR_RETURN(KEY_INTERFACE)
}

{KEY_LABEL} {
    OUR_RETURN(KEY_LABEL)
}

{KEY_MOD} {
    OUR_RETURN(KEY_MOD)
}

{KEY_NIL} {
    OUR_RETURN(KEY_NIL)
}

{KEY_NOT} {
    OUR_RETURN(KEY_NOT)
}

{KEY_OBJECT} {
    OUR_RETURN(KEY_OBJECT)
}

{KEY_OF} {
    OUR_RETURN(KEY_OF)
}

{KEY_OPERATOR} {
    OUR_RETURN(KEY_OPERATOR)
}

{KEY_OR} {
    OUR_RETURN(KEY_OR)
}

{KEY_PACKED} {
    OUR_RETURN(KEY_PACKED)
}

{KEY_PROCEDURE} {
    OUR_RETURN(KEY_PROCEDURE)
}

{KEY_PROGRAM} {
    OUR_RETURN(KEY_PROGRAM)
}

{KEY_RECORD} {
    OUR_RETURN(KEY_RECORD)
}

{KEY_REINTRODUCE} {
    OUR_RETURN(KEY_REINTRODUCE)
}

{KEY_REPEAT} {
    OUR_RETURN(KEY_REPEAT)
}

{KEY_SELF} {
    OUR_RETURN(KEY_SELF)
}

{KEY_SET} {
    OUR_RETURN(KEY_SET)
}

{KEY_SHL} {
    OUR_RETURN(KEY_SHL)
}

{KEY_SHR} {
    OUR_RETURN(KEY_SHR)
}

{KEY_THEN} {
    OUR_RETURN(KEY_THEN)
}

{KEY_TO} {
    OUR_RETURN(KEY_TO)
}

{KEY_TYPE} {
    OUR_RETURN(KEY_TYPE)
}

{KEY_UNIT} {
    OUR_RETURN(KEY_UNIT)
}

{KEY_UNTIL} {
    OUR_RETURN(KEY_UNTIL)
}

{KEY_USES} {
    OUR_RETURN(KEY_USES)
}

{KEY_VAR} {
    OUR_RETURN(KEY_VAR)
}

{KEY_WHILE} {
    OUR_RETURN(KEY_WHILE)
}

{KEY_WITH} {
    OUR_RETURN(KEY_WITH)
}

{KEY_XOR} {
    OUR_RETURN(KEY_XOR)
}

{TYPE_INT} {
    OUR_RETURN(TYPE_INT)
}

{TYPE_INT_8} {
    OUR_RETURN(TYPE_INT_8)
}

{TYPE_INT_16} {
    OUR_RETURN(TYPE_INT_16)
}

{TYPE_INT_32} {
    OUR_RETURN(TYPE_INT_32)
}

{TYPE_INT_64} {
    OUR_RETURN(TYPE_INT_64)
}

{TYPE_UNSIGNED_INT_8} {
    OUR_RETURN(TYPE_UNSIGNED_INT_8)
}

{TYPE_UNSIGNED_INT_16} {
    OUR_RETURN(TYPE_UNSIGNED_INT_16)
}

{TYPE_UNSIGNED_INT_32} {
    OUR_RETURN(TYPE_UNSIGNED_INT_32)
}

{TYPE_UNSIGNED_INT_64} {
    OUR_RETURN(TYPE_UNSIGNED_INT_64)
}

{TYPE_BOOLEAN} {
    OUR_RETURN(TYPE_BOOLEAN)
}

{TYPE_FLOAT} {
    OUR_RETURN(TYPE_FLOAT)
}

{TYPE_FLOAT_16} {
    OUR_RETURN(TYPE_FLOAT_16)
}

{TYPE_FLOAT_32} {
    OUR_RETURN(TYPE_FLOAT_32)
}

{TYPE_CHAR} {
    OUR_RETURN(TYPE_CHAR)
}

{TYPE_STRING} {
    OUR_RETURN(TYPE_STRING)
}

{LITERAL_INT} {
    yylval = strdup(yytext);
    OUR_RETURN(LITERAL_INT)
}

{LITERAL_FLOAT} {
    yylval = strdup(yytext);
    OUR_RETURN(LITERAL_FLOAT)
}

{LITERAL_CHAR} {
    yylval = strdup(yytext);
    OUR_RETURN(LITERAL_CHAR)
}

{LITERAL_ESC_CHAR} {
    yylval = strdup(yytext);
    OUR_RETURN(LITERAL_ESC_CHAR)
}

{LITERAL_STR} {
    yylval = strdup(yytext);
    OUR_RETURN(LITERAL_STR)
}

{LITERAL_TRUE} {
    yylval = strdup(yytext);
    OUR_RETURN(LITERAL_TRUE)
}

{LITERAL_FALSE} {
    yylval = strdup(yytext);
    OUR_RETURN(LITERAL_FALSE)
}

{IDENTIFIER} {
    yylval = strdup(yytext);
    OUR_RETURN(IDENTIFIER)
}

{SYM_ADD} {
    OUR_RETURN(SYM_ADD)
}

{SYM_SUB} {
    OUR_RETURN(SYM_SUB)
}

{SYM_MUL} {
    OUR_RETURN(SYM_MUL)
}

{SYM_DIV} {
    OUR_RETURN(SYM_DIV)
}

{SYM_EQ} {
    OUR_RETURN(SYM_EQ)
}

{SYM_LT} {
    OUR_RETURN(SYM_LT)
}

{SYM_GT} {
    OUR_RETURN(SYM_GT)
}

{SYM_LBRAC} {
    OUR_RETURN(SYM_LBRAC)
}

{SYM_RBRAC} {
    OUR_RETURN(SYM_RBRAC)
}

{SYM_PERIOD} {
    OUR_RETURN(SYM_PERIOD)
}

{SYM_COMMA} {
    OUR_RETURN(SYM_COMMA)
}

{SYM_COLON} {
    OUR_RETURN(SYM_COLON)
}

{SYM_SEMICOLON} {
    OUR_RETURN(SYM_SEMICOLON)
}

{SYM_AT} {
    OUR_RETURN(SYM_AT)
}

{SYM_CARET} {
    OUR_RETURN(SYM_CARET)
}

{SYM_LPAREN} {
    OUR_RETURN(SYM_LPAREN)
}

{SYM_RPAREN} {
    OUR_RETURN(SYM_RPAREN)
}

{SYM_NE} {
    OUR_RETURN(SYM_NE)
}

{SYM_LE} {
    OUR_RETURN(SYM_LE)
}

{SYM_GE} {
    OUR_RETURN(SYM_GE)
}

{SYM_ASSIGN} {
    OUR_RETURN(SYM_ASSIGN)
}

{SYM_RANGE} {
    OUR_RETURN(SYM_RANGE)
}


{COMMENT} {
    cout << (#X) << endl;
}

\n|(\r\n) {
    yycolumn = 1;
}
" "|\t {}

. {
    printf("Unknown Character %d\n", (int) yytext[0]);
    return yytext[0];
}
%%

void yyerror(const char *s) {
    fprintf(stderr, "LexError: %s (at Line %d, Column%d)\n", s, yylloc.first_line, yylloc.first_column);
}

#ifdef DEBUG_LEXER

int main() {
    yylex();
    return 0;
}

#endif