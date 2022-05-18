; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@array_a = common global [626 x i32] zeroinitializer
@i = common global i32 0
@sum = common global i32 0
@printf_format = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  br label %while_condition

while_condition:                                  ; preds = %while_body, %entry
  %"load identifier value" = load i32, i32* @i, align 4
  %cmptmp = icmp slt i32 %"load identifier value", 10
  br i1 %cmptmp, label %while_body, label %while_end

while_body:                                       ; preds = %while_condition
  %"load identifier value1" = load i32, i32* @sum, align 4
  %"load identifier value2" = load i32, i32* @i, align 4
  %addtmp = add i32 %"load identifier value1", %"load identifier value2"
  store i32 %addtmp, i32* @sum, align 4
  %"load identifier value3" = load i32, i32* @i, align 4
  %addtmp4 = add i32 %"load identifier value3", 1
  store i32 %addtmp4, i32* @i, align 4
  br label %while_condition

while_end:                                        ; preds = %while_condition
  %"load identifier value5" = load i32, i32* @sum, align 4
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %"load identifier value5")
  ret i32 0
}

declare i32 @printf(i8*, ...)
