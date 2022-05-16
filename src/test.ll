; ModuleID = 'pascal_module'
source_filename = "pascal_module"

@constTerm1 = common constant i32 3
@constTerm2 = common constant double 3.140000e+00
@curTerm1 = common global i32 0
@curTerm2 = common global i32 0

define i32 @main() {
entry:
  %0 = load i32, i32* @constTerm1, align 4
  store i32 %0, i32* @curTerm1, align 4
  store i32 11, i32* @curTerm1, align 4
  %1 = load i32, i32* @curTerm1, align 4
  %cmptmp = icmp eq i32 %1, 11
  br i1 %cmptmp, label %if_then, label %if_else

if_then:                                          ; preds = %entry
  store i32 5, i32* @curTerm2, align 4
  br label %if_continue

if_else:                                          ; preds = %entry
  %2 = load i32, i32* @curTerm1, align 4
  %cmptmp4 = icmp eq i32 %2, 12
  br i1 %cmptmp4, label %if_then1, label %if_else2

if_continue:                                      ; preds = %if_else2, %if_then

if_then1:                                         ; preds = %if_else
  store i32 6, i32* @curTerm2, align 4
  br label %if_continue3

if_else2:                                         ; preds = %if_else
  store i32 7, i32* @curTerm2, align 4
  br label %if_continue3
  br label %if_continue
  ret i32 0

if_continue3:                                     ; preds = %if_else2, %if_then1
}
