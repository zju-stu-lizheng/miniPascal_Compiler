# 约定CFG

## %type的含义

3.7.4 [Nonterminal Symbols](https://www.gnu.org/software/bison/manual/bison.html#Type-Decl)


When you use %union to specify multiple value types, you must declare the value type of each nonterminal symbol for which values are used. This is done with a %type declaration, like this:


%type <type> nonterminal…


Here nonterminal is the name of a nonterminal symbol, and type is the name given in the %union to the alternative that you want (see The Union Declaration). You can give any number of nonterminal symbols in the same %type declaration, if they have the same value type. Use spaces to separate the symbol names.


## 起始符为`program`

1. program -> pro_head routine .
```pascal
program: 
    pro_head routine SYM_PERIOD 
;
{routine 是程序的本体:包括变量/类型定义，函数/过程定义，主程序块}
```

2. pro_head -> `program` `pro_name` ;
```pascal
pro_head:
    KEY_PROGRAM IDENTIFIER SYM_SEMICOLON
;
```

3. routine -> routine_head routine_body
```pascal
routine:
    routine_head  routine_body
;
//routine_head:程序的变量/类型定义,函数/过程定义
//routine_body:主程序块，可以理解成begin{...}end整个语句块
```

4. routine_head -> const_part type_part var_part routine_part
```pascal
routine_head:
    const_part type_part var_part routine_part
;
{const_part:常量声明
type_part:类型声明
var_part:变量声明
routine_part:函数/过程声明}
```

5. const_part -> `const` const_decl_list | $\epsilon$
```pascal
const_part:
    KEY_CONST const_expr_list | %empty 
;
(*常量声明的格式 
Const
e = 2.7182818; { Real type constant. }
a = 2; { Ordinal (Integer) type constant. }
c = '4'; { Character type constant. }
s = 'This is a constant string'; {String type constant.}
sc = chr(32)
ls = SizeOf(Longint);
P = Nil;
Ss = [1,2];
*)
```
- [x] const_decl_list 完成


6. type_part -> `type` type_decl_list | $\epsilon$
```pascal 
type_part:
    KEY_TYPE type_decl_list 
    | %empty
;
(* 
Type
Longint = $80000000..$7fffffff;
Integer = -32768..32767;
shortint = -128..127;
byte = 0..255;
Word = 0..65535;

Type
Direction = ( North, East, South, West );
*)
```
- [x] type_decl_list 完成

7. var_part -> `var` var_decl_list | $\epsilon$
```pascal 
var_part:
    KEY_VAR var_decl_list |
    %empty
;
(* 
Var
curterm1 : integer;
curterm2 : integer; cvar;
curterm3 : integer; cvar; external;
curterm4 : integer; external name 'curterm3';
curterm5 : integer; external 'libc' name 'curterm9';
curterm6 : integer absolute curterm1;
curterm7 : integer; cvar; export;
curterm8 : integer; cvar; public;
curterm9 : integer; export name 'me';
curterm10 : integer; public name 'ma';
curterm11 : integer = 1 ;
*)
```

- [x] var_decl_list 完成

8. routine_part -> routine_part function_decl 
    | routine_part procedure_decl 
    | function_decl 
    | procedure_decl
    | $\epsilon$
```pascal
routine_part:
    routine_part function_decl 
    | routine_part procedure_decl 
    | function_decl 
    | procedure_decl
    | %empty
;
(*函数和过程定义*)
```
- [x] function_decl / procedure_decl 完成

9. routine_body -> compound_stmt
10. compound_stmt -> `begin` stmt_list `end`
```pascal
compound_stmt:
    KEY_BEGIN stmt_list KEY_END
;
(* 主体程序块 *)
```

- [x] stmt_list 待完成

11. const_decl_list -> const_decl_list `const_name` = const_value ; | `const_name` = const_value ;

```pascal
const_expr_list:
    const_expr_list IDENTIFIER SYM_EQ const_value SYM_SEMICOLON 
    | IDENTIFIER SYM_EQ const_value SYM_SEMICOLON
;
(*
const_value 根据不同的类型有不同的值
 *)
```

12. const_value -> 2 | 3.3 | 'sun' | `false` | `true` 

```pascal
const_value:
    LITERAL_INT 
    | LITERAL_FLOAT
    | LITERAL_CHAR
    | LITERAL_STR 
    | LITERAL_FALSE
    | LITERAL_TRUE
;
```

13. type_decl_list -> type_decl_list type_definition | type_definition

```pascal
type_decl_list :
    type_decl_list type_definition 
    | type_definition
;
(* 一系列类型定义组成 *)
```

14. type_definition -> `type_name` = type_decl ;

```pascal
type_definition:
    IDENTIFIER SYM_EQ type_decl SYM_SEMICOLON
;
(*  type_decl是类型的种类
比如，有 simple_type(int ,float 等),array_type,record_type
 *)
```

15. type_decl -> simple_type_decl | array_type_decl | record_type_decl

```pascal
type_decl:
    simple_type_decl 
    | array_type_decl 
    | record_type_decl
;
(*  type_decl是类型的种类
比如，有 simple_type(int ,float 等),array_type,record_type
 *)
```

16. simple_type_decl -> 
    easy_type
    | `type_name`
    | '(' name_list ')'
    |  const_value  ..  const_value
    |  IDENTIFIER  ..  IDENTIFIER

```pascal
simple_type_decl: 
    easy_type
    | IDENTIFIER
    | SYM_LPAREN name_list SYM_RPAREN
    |  const_value  SYM_RANGE  const_value
    |  IDENTIFIER  SYM_RANGE  IDENTIFIER
;
// easy_type : 包括布尔类型，字符类型，整数类型和实数类型
// `type_name` : 类型别名(reference)
// '(' name_list ')' : Subrange 类似枚举
(* Type Days = (monday,tuesday,wednesday,thursday,friday,saturday,sunday) *)
// IDENTIFIER  ..  IDENTIFIER
(* WeekEnd = Saturday .. Sunday *)
// const_value  ..  const_value
(* Type Integer = -32768..32767 *)

```

17. easy_type -> TYPE_BOOLEAN | TYPE_CHAR | TYPE_INT | TYPE_FLOAT

18. name_list ->
    name_list ',' IDENTIFIER
    | IDENTIFIER

```pascal
//Example:
monday,tuesday,wednesday,thursday,friday,saturday,sunday
```

19. array_type_decl -> `array` '[' simple_type_decl ']' `of` type_decl

```pascal
//Example:
Array[1..10000] of string
```

20. record_type_decl -> `record` field_decl_list `end`

```pascal
//一个record类型声明
// 内容包括 Record X,Y,Z : Real ;
Type Point = Record X,Y,Z :Real; end ;

//复杂一些的
Type BetterRPoint = Record X,Y,Z : Real;
                    R,theta,phi : Real;
                     end ;
```

21. field_decl_list -> field_decl_list field_decl | field_decl

22. field_decl -> name_list ':' type_decl ';'

```pascal
//name_list为一串逗号分隔的标识符
```

23. var_decl_list -> var_decl_list var_decl | var_decl

24. var_decl -> name_list ':' type_decl ';'

```pascal
//这里与Type声明几乎一样
Var
curTerm1 :integer;
```

25. function_decl ->
    function_head ';' routine ';' 

```pascal
//routine是程序主体块
```

26. function_head->
    `function` IDENTIFIER parameters ':' simple_type_decl 

27. procedure_decl->
    procedure_head ';' routine ';'

```pascal
//过程是没有返回值的函数
Procedure DoSomething (Para : String);
begin
    Writeln('Got parameter : ',Para);
end;
```

28. procedure_head->
    `procedure` IDENTIFIER parameters
29. parameters -> '(' para_decl_list ')' | $\epsilon$
30. para_decl_list -> para_decl_list ';' para_type_list | para_type_list
31. para_type_list -> var_para_list ':' simple_type_decl | val_para_list ':' simple_type_decl

```pascal
// 使用var:该过程获取一个指向已传递的变量的指针，并使用此指针来访问该变量的值。
Procedure DoA(Var A : Integer);
begin
A:=2;
Writeln('A is ',A);
end;
// 当参数被声明为值参数时，该过程将获得调用语句所传递的参数的副本。
Const
MyConst = 20;
Procedure MyRealFunc(I : Integer );
begin
Writeln('Function received : ',I);
end;
```

32. var_para_list -> `var` name_list


33. val_para_list -> name_list


34. stmt_list ->
    stmt_list stmt SYM_SEMICOLON
    | 

```pascal
//主体语句块，一系列语句组成 见ref Ch13.Statements
```

35. stmt -> label ':' non_label_stmt | non_label_stmt

```pascal
//考虑可以有label
A label can be an identifier or an integer digit.
```

![image-20220510141519347](https://gitee.com/zjg_lz/pic-go/raw/master/static/image-20220510141519347.png)

36. label -> LITERAL_INT | IDENTIFIER
37. non_label_stmt -> assign_stmt

  | proc_stmt

  | compound_stmt

  | if_stmt

  | case_stmt

  | repeat_stmt

  | while_stmt

  | for_stmt

  | goto_stmt

```pascal
//排除label的语句类型
1. 赋值语句
2. 过程语句 : 例如 WriteLn('Pascal is an easy language !'); 表示对一个过程/函数的调用
3. 复杂语句块 : 包含 begin...end
4. 条件判断语句块 : 包含 if case
5. 循环语句块 : 包括 repeat while for
6. Go-to语句块
```



38. assign_stmt -> IDENTIFIER ':=' expression |

​			IDENTIFIER '[' expression ']' ':=' expression |

​			IDENTIFIER '.' IDENTIFIER ':=' expression

```pascal
//赋值语句,考虑 := 暂时不管 += , -= , *= , /=
1. simple_type 
2. array_type
3. record_type
//expression 是一个表达式,比如算术表达式，布尔表达式
```



39. proc_stmt -> IDENTIFIER |

  IDENTIFIER '(' expression_list ')'

40. if_stmt -> `if` expression `then` stmt else_clause
41. else_clause -> `else` stmt | $\epsilon$
42. case_stmt -> `case` expression `of` case_expr_list `end`
43. case_expr_list -> case_expr_list case_expr | case_expr
44. case_expr -> const_value ':' stmt ';' 

```pascal
//case的每一条记录，是一个常数匹配
Var i : integer;
...
Case i of
3 : DoSomething;
5 : DoSomethingElse;
end;
```

45. repeat_stmt -> `repeat` stmt_list `until` expression

```pascal
//repeat 循环例子
repeat
X := X/2
until x<10e-3;
```

46. while_stmt -> `while` expression `do` stmt
47. for_stmt -> `for` IDENTIFIER `:=` expression direction expression `do` stmt
48. direction -> `to` | `downto`

```pascal
//使用to
For Day := Monday to Friday do Work;
//使用downto
For I := 100 downto 1 do
WriteLn ('Counting down : ',i);
```

49. goto_stmt -> `goto` label

50. expression_list -> expression_list ',' expression | expression

51. expression -> expression '>=' expr

    | expression '>' expr

    | expression '<=' expr

    | expression '<' expr

    | expression '=' expr

    | expression '<>' expr

    | expr

52. expr -> expr '+' term

    | expr '-' term

    | expr `or` term

    | term

53. term -> term '*' factor

    | term '/' factor

    | term `div` factor

    | term `mod` factor

    | term `and` factor

    | factor

54. factor -> IDENTIFIER 

    | IDENTIFIER '(' expression_list ')'

    | const_value

    | '(' expression ')'

    | `not` factor

    | `-` factor

    | IDENTIFIER '[' expression ']'

    | IDENTIFIER '.' IDENTIFIER

