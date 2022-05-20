
Program advisor;

Var 
    courses :   array[0 .. 39999] of char;
    map: array[0..99] of integer;
    is_passed: array[0..99] of integer;
    course_name: array[0..4] of char;

    // main variable
    ch: char;
    num: integer;
    index: integer;
    total_credits: integer;
    attempted_credits: integer;
    passed_credits: integer;
    remained_credits: integer;
    total_score: integer;
    field: integer;
    credit: integer;
    key: integer;
    i: integer;
    GPA: real;
    value: integer;
    flag: integer;
    j: integer;
    k: integer;
    tmp_idx: integer;    

Begin
    while True do begin
        Read(ch);
        if ch = '\n' then
            Write(3);
            break;
        index := 0;
        tmp_idx := num * 100 + index;
        courses[tmp_idx] := ch;
        index := index + 1;
        Write(ch);
    end;
End.
