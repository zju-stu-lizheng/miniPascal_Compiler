# 约定CFG

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
[x] const_decl_list 完成


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
[x] type_decl_list 完成

7. var_part -> `var` var_decl_list | $\epsilon$ 
```pascal 
var_part:
    KEY_VAR var_decl_list |
    %empty
;
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

[x] var_decl_list 完成

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
> function_decl / procedure_decl 待完成

9. routine_body -> `begin` stmt_list `end`
```pascal
routine_body:
    KEY_BEGIN stmt_list KEY_END
;
(* 主体程序块 *)
```

> stmt_list 待完成

10. const_decl_list -> const_decl_list `const_name` = const_value ; | `const_name` = const_value ;
```pascal
const_expr_list:
    const_expr_list IDENTIFIER SYM_EQ const_value SYM_SEMICOLON 
    | IDENTIFIER SYM_EQ const_value SYM_SEMICOLON
;
(*
const_value 根据不同的类型有不同的值
 *)
```

11. const_value -> 2 | 3.3 | 'sun' | `false` | `true` 
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

12. type_decl_list -> type_decl_list type_definition | type_definition
```pascal
type_decl_list :
    type_decl_list type_definition 
    | type_definition
;
(* 一系列类型定义组成 *)
```

13. type_definition -> `type_name` = type_decl ;
```pascal
type_definition:
    IDENTIFIER SYM_EQ type_decl SYM_SEMICOLON
;
(*  type_decl是类型的种类
比如，有 simple_type(int ,float 等),array_type,record_type
 *)
```

14. type_decl -> simple_type_decl | array_type_decl | record_type_decl
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

15. simple_type_decl -> 
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

16. easy_type -> TYPE_BOOLEAN | TYPE_CHAR | TYPE_INT | TYPE_FLOAT

17. name_list ->
    name_list ',' IDENTIFIER
    | IDENTIFIER
```pascal
//Example:
monday,tuesday,wednesday,thursday,friday,saturday,sunday
```

18. array_type_decl -> `array` '[' simple_type_decl ']' `of` type_decl
```pascal
//Example:
Array[1..10000] of string
```

19. record_type_decl -> `record` field_decl_list `end`

```pascal
//一个record类型声明
// 内容包括 Record X,Y,Z : Real ;
Type Point = Record X,Y,Z :Real; end ;

//复杂一些的
Type BetterRPoint = Record X,Y,Z : Real;
                    R,theta,phi : Real;
                     end ;
```

20. field_decl_list -> field_decl_list field_decl | field_decl

21. field_decl -> name_list ':' type_decl ';'
```pascal
//name_list为一串逗号分隔的标识符
```

22. var_decl_list -> var_decl_list var_decl | var_decl

23. var_decl -> name_list : type_decl
```pascal
//这里与Type声明几乎一样
Var
curTerm1 :integer;
```

24. function_decl ->
    function_head ';' routine ';' 
```pascal
//routine是程序主体块
```

25. function_head->
    `function` IDENTIFIER parameters ':' simple_type_decl 


26. procedure_decl->
    procedure_head ';' routine ';'

```pascal
//过程是没有返回值的函数
Procedure DoSomething (Para : String);
begin
    Writeln('Got parameter : ',Para);
end;
```

27. procedure_head->
    `procedure` IDENTIFIER parameters

28. parameters -> '(' para_decl_list ')' | $\epsilon$

29. para_decl_list -> para_decl_list ';' para_type_list | para_type_list

30. para_type_list -> 