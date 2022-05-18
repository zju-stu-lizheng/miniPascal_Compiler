; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@r = common global [100 x double] zeroinitializer
@s = common global double 0.000000e+00
@printf_format = private unnamed_addr constant [5 x i8] c"%lf\0A\00", align 1

define i32 @main() {
entry:
  store double 2.200000e+00, double* @s, align 8
  %0 = load double, double* getelementptr inbounds ([100 x double], [100 x double]* @r, i32 0, i32 1), align 8
  store double 4.200000e+00, double* getelementptr inbounds ([100 x double], [100 x double]* @r, i32 0, i32 1), align 8
  %1 = load double, double* getelementptr inbounds ([100 x double], [100 x double]* @r, i32 0, i32 1), align 8
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @printf_format, i32 0, i32 0), double %1)
  ret i32 0
}

declare i32 @printf(i8*, ...)
