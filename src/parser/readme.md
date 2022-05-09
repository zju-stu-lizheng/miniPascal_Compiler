# 约定CFG

## 起始符为`program`

1. program -> pro_head routine .
```pascal
program: 
    pro_head routine SYM_PERIOD 
;
{routine 是程序的主体:包括变量/类型定义，函数/过程定义}
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
{routine_head:程序的变量/类型定义
routine_body:函数/过程定义}
```