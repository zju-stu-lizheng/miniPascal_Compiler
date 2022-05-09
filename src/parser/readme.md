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

5. const_part -> `Const` const_decl_list | $\epsilon$ 
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
> const_decl_list 待完成
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
> type_decl_list 待完成

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

> var_decl_list 待完成

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