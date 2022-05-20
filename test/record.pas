
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

    myeof: char;

Begin
    myeof := '~';

    while True do begin
        Read(ch);
        if ch = '\n' then
            break;
        index := 0;
        tmp_idx := num * 100 + index;
        courses[tmp_idx] := ch;
        index := index + 1;
        Write(ch);

        while True do begin
            Read(ch);
            if ch = '\n' then
                break;
            tmp_idx := num * 100 + index;
            courses[tmp_idx] := ch;
            index := index + 1;
        end;

        tmp_idx := num * 100 + index;
        // TODO \0
        courses[tmp_idx] := myeof;
        is_passed[num] := 0;
        num := num + 1;
    end;

    for i:=0 to num do begin
        index := 0;
        field := 0;
        credit := 0;
        key := 0;

        tmp_idx := i * 100 + index;
        
        while (courses[tmp_idx] <> myeof) do begin
            if (courses[tmp_idx] = '|') then begin // not such class
                field := field + 1;
                index := index + 1;
                credit := 0;
                key := 0;

                tmp_idx := i * 100 + index;

                while (courses[tmp_idx] <> myeof) do begin
                    if (courses[tmp_idx] = '|') then begin
                        field := field + 1;
                        index := index + 1;
                    end;

                    if (field = 0) then begin
                        tmp_idx := i * 100 + index;
                        if ((courses[tmp_idx] <= '9') and (courses[tmp_idx] >= '0)) then begin
                            key := key * 10 + courses[tmp_idx] - '0';
                        end
                        index := index + 1;
                    end;

                    if (field = 1) then begin
                        tmp_idx := i * 100 + index;
                        credit := courses[tmp_idx] - '0';
                        total_credits := total_credits + credit;
                        map[key] := i;
                        index := index + 1;
                    end;

                    if (field = 2) then begin
                        tmp_idx := i * 100 + index;
                        if (courses[tmp_idx] <> '|') then begin
                            index := index + 1;
                        end;
                    end

                    if (field = 3) then begin
                        tmp_idx := i * 100 + index;
                        if (courses[tmp_idx] <> myeof) then begin
                            if (courses[tmp_idx] = 'A') then begin
                                attempted_credits := attempted_credits + credit;
                                passed_credits := passed_credits + credit;
                                total_score := total_score + 4 * credit;
                                is_passed[i] := 1;
                            end;
                            if (courses[tmp_idx] = 'B') then begin
                                attempted_credits := attempted_credits + credit;
                                passed_credits := passed_credits + credit;
                                total_score := total_score + 3 * credit;
                                is_passed[i] := 1;
                            end;
                            if (courses[tmp_idx] = 'C') then begin
                                attempted_credits := attempted_credits + credit;
                                passed_credits := passed_credits + credit;
                                total_score := total_score + 2 * credit;
                                is_passed[i] := 1;
                            end;
                            if (courses[tmp_idx] = 'D') then begin
                                attempted_credits := attempted_credits + credit;
                                passed_credits := passed_credits + credit;
                                total_score := total_score + credit;
                                is_passed[i] := 1;
                            end;
                            if (courses[tmp_idx] = 'F') then begin
                                attempted_credits := attempted_credits + credit;
                            end;
                        end;
                        index := index + 1;
                    end
                end;
            end;

            if (attempted_credits <> 0) then begin
                GPA := 1.0 * total_credits / attempted_credits;
            end;
            remained_credits := total_credits - passed_credits;

            //TODO: output bit number
            write("GPA");


        end;
    end;
End.
