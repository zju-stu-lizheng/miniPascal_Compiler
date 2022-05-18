; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@array_a = common global [626 x i32] zeroinitializer
@array_b = common global [626 x i32] zeroinitializer
@array_c = common global [626 x i32] zeroinitializer
@m_a = common global i32 0
@n_a = common global i32 0
@s_a = common global i32 0
@m_b = common global i32 0
@n_b = common global i32 0
@s_b = common global i32 0
@s_c = common global i32 0
@i = common global i32 0
@j = common global i32 0
@k = common global i32 0
@tmp_a = common global i32 0
@tmp_b = common global i32 0
@tmp_c = common global i32 0
@scanf_format = private unnamed_addr constant [11 x i8] c"%d%d%*[^\0A]\00", align 1
@scanf_newline = private unnamed_addr constant [4 x i8] c"%*c\00", align 1
@scanf_format.1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@scanf_format.2 = private unnamed_addr constant [11 x i8] c"%d%d%*[^\0A]\00", align 1
@scanf_newline.3 = private unnamed_addr constant [4 x i8] c"%*c\00", align 1
@scanf_format.4 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@0 = private unnamed_addr constant [256 x i8] c"Incompatible Dimensions\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", align 1
@printf_format = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@printf_format.5 = private unnamed_addr constant [5 x i8] c"%d%c\00", align 1
@printf_format.6 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define i32 @main() {
entry:
  %"load identifier value" = load i32, i32* @m_a, align 4
  %"load identifier value1" = load i32, i32* @n_a, align 4
  %call_scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @scanf_format, i32 0, i32 0), i32* @m_a, i32* @n_a)
  %call_scanf2 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @scanf_newline, i32 0, i32 0))
  %"load identifier value3" = load i32, i32* @m_a, align 4
  %"load identifier value4" = load i32, i32* @n_a, align 4
  %multmp = mul i32 %"load identifier value3", %"load identifier value4"
  store i32 %multmp, i32* @s_a, align 4
  br label %for_start

for_start:                                        ; preds = %entry
  store i32 0, i32* @i, align 4
  %"load identifier value5" = load i32, i32* @s_a, align 4
  %subtmp = sub i32 %"load identifier value5", 1
  %cmptmp = icmp sgt i32 0, %subtmp
  br i1 %cmptmp, label %for_end, label %for_handle

for_handle:                                       ; preds = %for_condition, %for_start
  %"load identifier value6" = load i32, i32* @i, align 4
  %subtmp7 = sub i32 %"load identifier value6", 0
  %ArrayCall = getelementptr [626 x i32], [626 x i32]* @array_a, i32 0, i32 %subtmp7
  %"load array value" = load i32, i32* %ArrayCall, align 4
  %call_scanf8 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @scanf_format.1, i32 0, i32 0), i32* %ArrayCall)
  br label %for_condition

for_condition:                                    ; preds = %for_handle
  %"load identifier value9" = load i32, i32* @i, align 4
  %tmpadd = add i32 %"load identifier value9", 1
  store i32 %tmpadd, i32* @i, align 4
  %"load identifier value10" = load i32, i32* @i, align 4
  %"load identifier value11" = load i32, i32* @s_a, align 4
  %subtmp12 = sub i32 %"load identifier value11", 1
  %cmptmp13 = icmp sgt i32 %"load identifier value10", %subtmp12
  br i1 %cmptmp13, label %for_end, label %for_handle
  br label %for_end

for_end:                                          ; preds = %for_condition, %for_condition, %for_start
  %"load identifier value14" = load i32, i32* @m_b, align 4
  %"load identifier value15" = load i32, i32* @n_b, align 4
  %call_scanf16 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @scanf_format.2, i32 0, i32 0), i32* @m_b, i32* @n_b)
  %call_scanf17 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @scanf_newline.3, i32 0, i32 0))
  %"load identifier value18" = load i32, i32* @m_b, align 4
  %"load identifier value19" = load i32, i32* @n_b, align 4
  %multmp20 = mul i32 %"load identifier value18", %"load identifier value19"
  store i32 %multmp20, i32* @s_b, align 4
  br label %for_start21

for_start21:                                      ; preds = %for_end
  store i32 0, i32* @i, align 4
  %"load identifier value25" = load i32, i32* @s_b, align 4
  %subtmp26 = sub i32 %"load identifier value25", 1
  %cmptmp27 = icmp sgt i32 0, %subtmp26
  br i1 %cmptmp27, label %for_end24, label %for_handle22

for_handle22:                                     ; preds = %for_condition23, %for_start21
  %"load identifier value28" = load i32, i32* @i, align 4
  %subtmp29 = sub i32 %"load identifier value28", 0
  %ArrayCall30 = getelementptr [626 x i32], [626 x i32]* @array_b, i32 0, i32 %subtmp29
  %"load array value31" = load i32, i32* %ArrayCall30, align 4
  %call_scanf32 = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @scanf_format.4, i32 0, i32 0), i32* %ArrayCall30)
  br label %for_condition23

for_condition23:                                  ; preds = %for_handle22
  %"load identifier value33" = load i32, i32* @i, align 4
  %tmpadd34 = add i32 %"load identifier value33", 1
  store i32 %tmpadd34, i32* @i, align 4
  %"load identifier value35" = load i32, i32* @i, align 4
  %"load identifier value36" = load i32, i32* @s_b, align 4
  %subtmp37 = sub i32 %"load identifier value36", 1
  %cmptmp38 = icmp sgt i32 %"load identifier value35", %subtmp37
  br i1 %cmptmp38, label %for_end24, label %for_handle22
  br label %for_end24

for_end24:                                        ; preds = %for_condition23, %for_condition23, %for_start21
  %"load identifier value39" = load i32, i32* @n_a, align 4
  %"load identifier value40" = load i32, i32* @m_b, align 4
  %cmptmp41 = icmp ne i32 %"load identifier value39", %"load identifier value40"
  br i1 %cmptmp41, label %if_then, label %if_else

if_then:                                          ; preds = %for_end24
  %"load const string" = load [256 x i8], [256 x i8]* @0, align 1
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), [256 x i8]* @0)
  br label %if_continue

if_else:                                          ; preds = %for_end24
  br label %for_start42

if_continue:                                      ; preds = %for_end119, %if_then
  ret i32 0

for_start42:                                      ; preds = %if_else
  store i32 0, i32* @i, align 4
  %"load identifier value46" = load i32, i32* @m_a, align 4
  %subtmp47 = sub i32 %"load identifier value46", 1
  %cmptmp48 = icmp sgt i32 0, %subtmp47
  br i1 %cmptmp48, label %for_end45, label %for_handle43

for_handle43:                                     ; preds = %for_condition44, %for_start42
  br label %for_start49

for_condition44:                                  ; preds = %for_end52
  %"load identifier value107" = load i32, i32* @i, align 4
  %tmpadd108 = add i32 %"load identifier value107", 1
  store i32 %tmpadd108, i32* @i, align 4
  %"load identifier value109" = load i32, i32* @i, align 4
  %"load identifier value110" = load i32, i32* @m_a, align 4
  %subtmp111 = sub i32 %"load identifier value110", 1
  %cmptmp112 = icmp sgt i32 %"load identifier value109", %subtmp111
  br i1 %cmptmp112, label %for_end45, label %for_handle43
  br label %for_end45

for_end45:                                        ; preds = %for_condition44, %for_condition44, %for_start42
  %"load identifier value113" = load i32, i32* @m_a, align 4
  %"load identifier value114" = load i32, i32* @n_b, align 4
  %multmp115 = mul i32 %"load identifier value113", %"load identifier value114"
  store i32 %multmp115, i32* @s_c, align 4
  br label %for_start116

for_start49:                                      ; preds = %for_handle43
  store i32 0, i32* @j, align 4
  %"load identifier value53" = load i32, i32* @n_b, align 4
  %subtmp54 = sub i32 %"load identifier value53", 1
  %cmptmp55 = icmp sgt i32 0, %subtmp54
  br i1 %cmptmp55, label %for_end52, label %for_handle50

for_handle50:                                     ; preds = %for_condition51, %for_start49
  br label %for_start56

for_condition51:                                  ; preds = %for_end59
  %"load identifier value101" = load i32, i32* @j, align 4
  %tmpadd102 = add i32 %"load identifier value101", 1
  store i32 %tmpadd102, i32* @j, align 4
  %"load identifier value103" = load i32, i32* @j, align 4
  %"load identifier value104" = load i32, i32* @n_b, align 4
  %subtmp105 = sub i32 %"load identifier value104", 1
  %cmptmp106 = icmp sgt i32 %"load identifier value103", %subtmp105
  br i1 %cmptmp106, label %for_end52, label %for_handle50
  br label %for_end52

for_end52:                                        ; preds = %for_condition51, %for_condition51, %for_start49
  br label %for_condition44

for_start56:                                      ; preds = %for_handle50
  store i32 0, i32* @k, align 4
  %"load identifier value60" = load i32, i32* @m_b, align 4
  %subtmp61 = sub i32 %"load identifier value60", 1
  %cmptmp62 = icmp sgt i32 0, %subtmp61
  br i1 %cmptmp62, label %for_end59, label %for_handle57

for_handle57:                                     ; preds = %for_condition58, %for_start56
  %"load identifier value63" = load i32, i32* @i, align 4
  %"load identifier value64" = load i32, i32* @n_b, align 4
  %multmp65 = mul i32 %"load identifier value63", %"load identifier value64"
  %"load identifier value66" = load i32, i32* @j, align 4
  %addtmp = add i32 %multmp65, %"load identifier value66"
  store i32 %addtmp, i32* @tmp_c, align 4
  %"load identifier value67" = load i32, i32* @k, align 4
  %"load identifier value68" = load i32, i32* @n_b, align 4
  %multmp69 = mul i32 %"load identifier value67", %"load identifier value68"
  %"load identifier value70" = load i32, i32* @j, align 4
  %addtmp71 = add i32 %multmp69, %"load identifier value70"
  store i32 %addtmp71, i32* @tmp_b, align 4
  %"load identifier value72" = load i32, i32* @i, align 4
  %"load identifier value73" = load i32, i32* @m_b, align 4
  %multmp74 = mul i32 %"load identifier value72", %"load identifier value73"
  %"load identifier value75" = load i32, i32* @k, align 4
  %addtmp76 = add i32 %multmp74, %"load identifier value75"
  store i32 %addtmp76, i32* @tmp_a, align 4
  %"load identifier value77" = load i32, i32* @tmp_c, align 4
  %subtmp78 = sub i32 %"load identifier value77", 0
  %ArrayCall79 = getelementptr [626 x i32], [626 x i32]* @array_c, i32 0, i32 %subtmp78
  %"load array value80" = load i32, i32* %ArrayCall79, align 4
  %"load identifier value81" = load i32, i32* @tmp_c, align 4
  %subtmp82 = sub i32 %"load identifier value81", 0
  %ArrayCall83 = getelementptr [626 x i32], [626 x i32]* @array_c, i32 0, i32 %subtmp82
  %"load array value84" = load i32, i32* %ArrayCall83, align 4
  %"load identifier value85" = load i32, i32* @tmp_b, align 4
  %subtmp86 = sub i32 %"load identifier value85", 0
  %ArrayCall87 = getelementptr [626 x i32], [626 x i32]* @array_b, i32 0, i32 %subtmp86
  %"load array value88" = load i32, i32* %ArrayCall87, align 4
  %"load identifier value89" = load i32, i32* @tmp_a, align 4
  %subtmp90 = sub i32 %"load identifier value89", 0
  %ArrayCall91 = getelementptr [626 x i32], [626 x i32]* @array_a, i32 0, i32 %subtmp90
  %"load array value92" = load i32, i32* %ArrayCall91, align 4
  %multmp93 = mul i32 %"load array value88", %"load array value92"
  %addtmp94 = add i32 %"load array value84", %multmp93
  store i32 %addtmp94, i32* %ArrayCall79, align 4
  br label %for_condition58

for_condition58:                                  ; preds = %for_handle57
  %"load identifier value95" = load i32, i32* @k, align 4
  %tmpadd96 = add i32 %"load identifier value95", 1
  store i32 %tmpadd96, i32* @k, align 4
  %"load identifier value97" = load i32, i32* @k, align 4
  %"load identifier value98" = load i32, i32* @m_b, align 4
  %subtmp99 = sub i32 %"load identifier value98", 1
  %cmptmp100 = icmp sgt i32 %"load identifier value97", %subtmp99
  br i1 %cmptmp100, label %for_end59, label %for_handle57
  br label %for_end59

for_end59:                                        ; preds = %for_condition58, %for_condition58, %for_start56
  br label %for_condition51

for_start116:                                     ; preds = %for_end45
  store i32 0, i32* @i, align 4
  %"load identifier value120" = load i32, i32* @m_a, align 4
  %subtmp121 = sub i32 %"load identifier value120", 1
  %cmptmp122 = icmp sgt i32 0, %subtmp121
  br i1 %cmptmp122, label %for_end119, label %for_handle117

for_handle117:                                    ; preds = %for_condition118, %for_start116
  br label %for_start123

for_condition118:                                 ; preds = %for_end126
  %"load identifier value147" = load i32, i32* @i, align 4
  %tmpadd148 = add i32 %"load identifier value147", 1
  store i32 %tmpadd148, i32* @i, align 4
  %"load identifier value149" = load i32, i32* @i, align 4
  %"load identifier value150" = load i32, i32* @m_a, align 4
  %subtmp151 = sub i32 %"load identifier value150", 1
  %cmptmp152 = icmp sgt i32 %"load identifier value149", %subtmp151
  br i1 %cmptmp152, label %for_end119, label %for_handle117
  br label %for_end119

for_end119:                                       ; preds = %for_condition118, %for_condition118, %for_start116
  br label %if_continue

for_start123:                                     ; preds = %for_handle117
  store i32 0, i32* @j, align 4
  %"load identifier value127" = load i32, i32* @n_b, align 4
  %subtmp128 = sub i32 %"load identifier value127", 1
  %cmptmp129 = icmp sgt i32 0, %subtmp128
  br i1 %cmptmp129, label %for_end126, label %for_handle124

for_handle124:                                    ; preds = %for_condition125, %for_start123
  %"load identifier value130" = load i32, i32* @i, align 4
  %"load identifier value131" = load i32, i32* @n_b, align 4
  %multmp132 = mul i32 %"load identifier value130", %"load identifier value131"
  %"load identifier value133" = load i32, i32* @j, align 4
  %addtmp134 = add i32 %multmp132, %"load identifier value133"
  store i32 %addtmp134, i32* @k, align 4
  %"load identifier value135" = load i32, i32* @k, align 4
  %subtmp136 = sub i32 %"load identifier value135", 0
  %ArrayCall137 = getelementptr [626 x i32], [626 x i32]* @array_c, i32 0, i32 %subtmp136
  %"load array value138" = load i32, i32* %ArrayCall137, align 4
  %call_printf139 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @printf_format.5, i32 0, i32 0), i32 %"load array value138", i8 32)
  br label %for_condition125

for_condition125:                                 ; preds = %for_handle124
  %"load identifier value140" = load i32, i32* @j, align 4
  %tmpadd141 = add i32 %"load identifier value140", 1
  store i32 %tmpadd141, i32* @j, align 4
  %"load identifier value142" = load i32, i32* @j, align 4
  %"load identifier value143" = load i32, i32* @n_b, align 4
  %subtmp144 = sub i32 %"load identifier value143", 1
  %cmptmp145 = icmp sgt i32 %"load identifier value142", %subtmp144
  br i1 %cmptmp145, label %for_end126, label %for_handle124
  br label %for_end126

for_end126:                                       ; preds = %for_condition125, %for_condition125, %for_start123
  %call_printf146 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @printf_format.6, i32 0, i32 0))
  br label %for_condition118
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
