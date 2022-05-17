; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@r = common global [100 x i32] zeroinitializer
@printf_format = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  %0 = load [100 x i32], [100 x i32]* @r, align 4
  %1 = load i32, i32* getelementptr inbounds ([100 x i32], [100 x i32]* @r, i32 0, i32 9), align 4
  store double 1.000000e+00, i32* getelementptr inbounds ([100 x i32], [100 x i32]* @r, i32 0, i32 9), align 8
  %2 = load [100 x i32], [100 x i32]* @r, align 4
  %3 = load i32, i32* getelementptr inbounds ([100 x i32], [100 x i32]* @r, i32 0, i32 9), align 4
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %3)
  ret i32 0
}

declare i32 @printf(i8*, ...)
