; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@courses = common global [40000 x i8] zeroinitializer
@map = common global [100 x i32] zeroinitializer
@is_passed = common global [100 x i32] zeroinitializer
@course_name = common global [5 x i8] zeroinitializer
@ch = common global i8 0
@num = common global i32 0
@index = common global i32 0
@total_credits = common global i32 0
@attempted_credits = common global i32 0
@passed_credits = common global i32 0
@remained_credits = common global i32 0
@total_score = common global i32 0
@field = common global i32 0
@credit = common global i32 0
@key = common global i32 0
@i = common global i32 0
@GPA = common global double 0.000000e+00
@value = common global i32 0
@flag = common global i32 0
@j = common global i32 0
@k = common global i32 0
@tmp_idx = common global i32 0
@scanf_format = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@printf_format = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@printf_format.1 = private unnamed_addr constant [3 x i8] c"%c\00", align 1

define i32 @main() {
entry:
  br label %while_condition

while_condition:                                  ; preds = %if_continue, %entry
  br i1 true, label %while_body, label %while_end

while_body:                                       ; preds = %while_condition
  %"load identifier value" = load i8, i8* @ch, align 1
  %call_scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @scanf_format, i32 0, i32 0), i8* @ch)
  %"load identifier value1" = load i8, i8* @ch, align 1
  %cmptmp = icmp eq i8 %"load identifier value1", 10
  br i1 %cmptmp, label %if_then, label %if_else

while_end:                                        ; preds = %if_then, %while_condition
  ret i32 0

if_then:                                          ; preds = %while_body
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @printf_format, i32 0, i32 0), i32 3)
  br label %while_end

if_else:                                          ; preds = %while_body
  br label %if_continue

if_continue:                                      ; preds = %if_else, %break_continue
  store i32 0, i32* @index, align 4
  %"load identifier value2" = load i32, i32* @num, align 4
  %multmp = mul i32 %"load identifier value2", 100
  %"load identifier value3" = load i32, i32* @index, align 4
  %addtmp = add i32 %multmp, %"load identifier value3"
  store i32 %addtmp, i32* @tmp_idx, align 4
  %"load identifier value4" = load i32, i32* @tmp_idx, align 4
  %subtmp = sub i32 %"load identifier value4", 0
  %ArrayCall = getelementptr [40000 x i8], [40000 x i8]* @courses, i32 0, i32 %subtmp
  %"load array value" = load i8, i8* %ArrayCall, align 1
  %"load identifier value5" = load i8, i8* @ch, align 1
  store i8 %"load identifier value5", i8* %ArrayCall, align 1
  %"load identifier value6" = load i32, i32* @index, align 4
  %addtmp7 = add i32 %"load identifier value6", 1
  store i32 %addtmp7, i32* @index, align 4
  %"load identifier value8" = load i8, i8* @ch, align 1
  %call_printf9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @printf_format.1, i32 0, i32 0), i8 %"load identifier value8")
  br label %while_condition

break_continue:                                   ; No predecessors!
  br label %if_continue
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
