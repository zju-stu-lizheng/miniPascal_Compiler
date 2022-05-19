; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@Book1 = common global { [256 x i8], i32, i32, i32, i32 } zeroinitializer
@Book2 = common global { [256 x i8], i32, i32, i32, i32 } zeroinitializer
@0 = private unnamed_addr constant [256 x i8] c"AI\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", align 1
@printf_format = private unnamed_addr constant [3 x i8] c"%s\00", align 1

define i32 @main() {
entry:
  %"load record type" = load [256 x i8], [256 x i8]* getelementptr inbounds ({ [256 x i8], i32, i32, i32, i32 }, { [256 x i8], i32, i32, i32, i32 }* @Book1, i32 0, i32 0), align 1
  %"load const string" = load [256 x i8], [256 x i8]* @0, align 1
  store [256 x i8] %"load const string", [256 x i8]* getelementptr inbounds ({ [256 x i8], i32, i32, i32, i32 }, { [256 x i8], i32, i32, i32, i32 }* @Book1, i32 0, i32 0), align 1
  %"load record type1" = load [256 x i8], [256 x i8]* getelementptr inbounds ({ [256 x i8], i32, i32, i32, i32 }, { [256 x i8], i32, i32, i32, i32 }* @Book1, i32 0, i32 0), align 1
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @printf_format, i32 0, i32 0), [256 x i8]* getelementptr inbounds ({ [256 x i8], i32, i32, i32, i32 }, { [256 x i8], i32, i32, i32, i32 }* @Book1, i32 0, i32 0))
  ret i32 0
}

declare i32 @printf(i8*, ...)
