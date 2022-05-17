; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@constTerm1 = private constant i32 3
@constTerm2 = private constant double 3.140000e+00
@curTerm1 = common global i32 0
@curTerm2 = common global i32 0
@s = common global i32 0
@printf_format = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printf_format.1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main() {
entry:
  store i32 11, i32* @curTerm1, align 4
  %0 = load i32, i32* @curTerm1, align 4
  %cmptmp = icmp eq i32 %0, 11
  br i1 %cmptmp, label %if_then, label %if_else

if_then:                                          ; preds = %entry
  store i32 5, i32* @curTerm2, align 4
  br label %if_continue

if_else:                                          ; preds = %entry
  store i32 0, i32* @s, align 4
  %1 = load i32, i32* @curTerm1, align 4
  %cmptmp4 = icmp eq i32 %1, 12
  br i1 %cmptmp4, label %if_then1, label %if_else2

if_continue:                                      ; preds = %if_continue3, %if_then
  %2 = load i32, i32* @curTerm1, align 4
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %2)
  %3 = load i32, i32* @curTerm2, align 4
  %call_printf5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format.1, i32 0, i32 0), i32 %3)
  ret i32 0

if_then1:                                         ; preds = %if_else
  store i32 6, i32* @curTerm2, align 4
  br label %if_continue3

if_else2:                                         ; preds = %if_else
  store i32 7, i32* @curTerm2, align 4
  br label %if_continue3

if_continue3:                                     ; preds = %if_else2, %if_then1
  br label %if_continue
}

declare i32 @printf(i8*, ...)
