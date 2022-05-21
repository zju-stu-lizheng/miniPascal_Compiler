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
    c_tmp1 : integer;
    c_tmp2 : integer;
    tmp_value : char;
    zero : char;
    split : char;
    A : char;
    B : char;
    C : char;
    D : char;
    E : char;
    F : char;

    tmp_string : string;



function char2int(a: char):integer;
begin
    if a = '0' then
        char2int := 0;
    if a = '1' then
        char2int := 1;
    if a = '2' then
        char2int := 2;
    if a = '3' then
        char2int := 3;
    if a = '4' then
        char2int := 4;
    if a = '5' then
        char2int := 5;
    if a = '6' then
        char2int := 6;
    if a = '7' then
        char2int := 7;
    if a = '8' then
        char2int := 8;
    if a = '9' then
        char2int := 9;
end;

Begin
    myeof := '~';
    zero := '0';
    split := '|';
    A := 'A';
    B := 'B';
    C := 'C';
    D := 'D';
    E := 'E';
    F := 'F';


    // initial

    num := 0;
    index := 0;
    total_credits := 0;
    passed_credits := 0;
    total_score := 0;
    field := 0;
    credit := 0;
    key := 0;
    i := 0;
    GPA := 0.0;
    value := 0;
    flag := 0;
    j := 0;
    k := 0;

    while True do begin
        Read(ch);
        if ch = '\n' then
            break;
        index := 0;
        tmp_idx := num * 400 + index;
        courses[tmp_idx] := ch;
        index := index + 1;
        Write(courses[tmp_idx] );
        write('tmp_idx = ');
        write(tmp_idx);
        write('\n');

        while True do begin
            Read(ch);
            if ch = '\n' then
                break;
            tmp_idx := num * 400 + index;
            courses[tmp_idx] := ch;
            index := index + 1;
            Write(courses[tmp_idx] );
            write('tmp_idx = ');
            write(tmp_idx);
            write('\n');
        end;

        tmp_idx := num * 400 + index;
        // TODO \0
        courses[tmp_idx] := myeof;

        Write(courses[tmp_idx] );

        is_passed[num] := 0;
        num := num + 1;
    end;


    for i:=0 to (num-1) do begin
        index := 0;
        field := 0;
        credit := 0;
        key := 0;

        tmp_idx := i * 400 + index;
        write('i=');
        write(i);
        write('\n');
        
        while (courses[tmp_idx] <> myeof) do begin
            tmp_value := courses[tmp_idx];
            c_tmp1 := char2int(tmp_value);
            tmp_value := zero; 
            c_tmp2 := char2int(tmp_value);
            key := key * 10 + c_tmp1 - c_tmp2;
            write('key = ');
            write(key);
            write('\n');

            key := 9 - c_tmp2;
            write('key = ');
            write(key);
            write('\n');

            write('\n');
            write('tmp_idx = ');
            Write(tmp_idx);
            Write('\n');
            write('courses[tmp_idx] = ');
            write(courses[tmp_idx]);
            write('\n');
            write('field');
            write(field);
            write('\n');
            
            if (courses[tmp_idx] = split) then begin // not such class
                field := field + 1;
                index := index + 1;
            end;
            if (field = 0) then begin
                tmp_idx := i * 400 + index;
                if ((courses[tmp_idx] <= '9') and (courses[tmp_idx] >= '0')) then begin
                    tmp_value := courses[tmp_idx];
                    c_tmp1 := char2int(tmp_value);
                    tmp_value := zero; 
                    c_tmp2 := char2int(tmp_value);
                    key := key * 10 + c_tmp1 - c_tmp2;
                    write('key = ');
                    write(key);
                    write('\n');
                end;
                index := index + 1;
            end;

            if (field = 1) then begin
                tmp_idx := i * 400 + index;
                tmp_value := courses[tmp_idx];
                c_tmp1 := char2int(tmp_value);
                tmp_value := zero; 
                c_tmp2 := char2int(tmp_value);

                credit := c_tmp1 - c_tmp2;
                total_credits := total_credits + credit;
                map[key] := i;
                index := index + 1;
            end;

            if (field = 2) then begin
                tmp_idx := i * 400 + index;
                if (courses[tmp_idx] <> '|') then begin
                    index := index + 1;
                end;
            end;

            if (field = 3) then begin
                tmp_idx := i * 400 + index;
                if (courses[tmp_idx] <> myeof) then begin
                    if (courses[tmp_idx] = A) then begin
                        attempted_credits := attempted_credits + credit;
                        passed_credits := passed_credits + credit;
                        total_score := total_score + 4 * credit;
                        is_passed[i] := 1;
                    end;
                    if (courses[tmp_idx] = B) then begin
                        attempted_credits := attempted_credits + credit;
                        passed_credits := passed_credits + credit;
                        total_score := total_score + 3 * credit;
                        is_passed[i] := 1;
                    end;
                    if (courses[tmp_idx] = C) then begin
                        attempted_credits := attempted_credits + credit;
                        passed_credits := passed_credits + credit;
                        total_score := total_score + 2 * credit;
                        is_passed[i] := 1;
                    end;
                    if (courses[tmp_idx] = D) then begin
                        attempted_credits := attempted_credits + credit;
                        passed_credits := passed_credits + credit;
                        total_score := total_score + credit;
                        is_passed[i] := 1;
                    end;
                    if (courses[tmp_idx] = F) then begin
                        attempted_credits := attempted_credits + credit;
                    end;
                end;
                index := index + 1;
                tmp_idx := i * 400 + index;
            end;
            tmp_idx := i * 400 + index;
        end;
        tmp_idx := i * 400 + index;
    end;

    // if (attempted_credits <> 0) then begin
    //     GPA := 1.0 * total_credits / attempted_credits;
    // end;
    // remained_credits := total_credits - passed_credits;

    // write('GPA: ');
    // write(GPA);
    // write('\n');

    // write('Hours Attempted: ');
    // write(attempted_credits);
    // write('\n');

    // write('Hours Completed: ');
    // write(passed_credits);
    // write('\n');

    // write('Credits Remaining: ');
    // write(remained_credits);
    // write('\n');
    
    // // tmp_string := 
    // write('\n');
    // write('Possible Courses to Take Next');
    // write('\n');

    // if (remained_credits = 0) then begin
    //     write('  None - Congratulations!');
    // end
    // else begin
    //     value := 0;
    //     flag := 1;
    //     j := 0;

    //     for i:=0 to (num-1) do begin
    //         if (is_passed[i] = 0) then begin
    //             index := 0;
    //             j := 0;
    //             tmp_idx := i * 400 + index;
    //             while (courses[tmp_idx] <> split) do begin
    //                 course_name[j] := courses[tmp_idx];
    //                 j := j + 1;
    //                 index := index + 1;
    //                 tmp_idx := i * 400 + index;
    //             end;

    //             course_name[j] := myeof;
    //             tmp_idx := i * 400 + index;
    //             while (courses[tmp_idx] <> split) do begin
    //                 index := index + 1;
    //                 tmp_idx := i * 400 + index;
    //             end;
    //             index := index + 1;

    //             tmp_idx := i * 400 + index;
    //             if (courses[tmp_idx] = split)then begin
    //                 write('  ');
    //                 for k:=0 to (j-1) do begin
    //                     write(course_name[k]);
    //                 end;
    //                 write('\n');
    //             end
    //             else begin

    //                 flag := 1;
    //                 key := 0;

    //                 tmp_idx := i * 400 + index;
    //                 while (courses[tmp_idx] <> split) do begin
    //                     if ((courses[tmp_idx] <= '9') and (courses[tmp_idx] >= '0')) then begin
    //                         tmp_value := courses[tmp_idx];
    //                         c_tmp1 := char2int(tmp_value);
    //                         tmp_value := zero;
    //                         c_tmp2 := char2int(tmp_value);
    //                         key := key * 10 + c_tmp1 - c_tmp2;
    //                     end;
                        
    //                     tmp_idx := i * 400 + index;
    //                     if (courses[tmp_idx] = ',') then begin
    //                         value := map[key];
    //                         if (is_passed[value] = 0) then begin
    //                             flag := 0;
    //                         end;
    //                         key := 0;
    //                     end;

    //                     tmp_idx := i * 400 + index;
    //                     if (courses[tmp_idx] = ';') then begin
    //                         value := map[key];
    //                         if (is_passed[value] = 0) then begin
    //                             flag := 0;
    //                         end;
    //                         key := 0;
    //                         if (flag = 1) then begin
    //                             break;
    //                         end
    //                         else begin
    //                             flag := 1;
    //                         end;
    //                     end;
    //                     index := index + 1;
    //                 tmp_idx := i * 400 + index;
    //                 end;

    //                 tmp_idx := i * 400 + index;
    //                 if (courses[tmp_idx] = split) then begin
    //                     value := map[key];
    //                     if (is_passed[value] = 0) then begin
    //                         flag := 0;
    //                     end;
    //                 end;

    //                 if (flag = 1) then begin
    //                     write('  ');
    //                     for k:=0 to (j-1) do begin
    //                         write(course_name[k]);
    //                     end;
    //                     write('\n');
    //                 end;
    //                 tmp_idx := i * 400 + index;
    //             end;
    //             tmp_idx := i * 400 + index;
    //         end;
    //         tmp_idx := i * 400 + index;
    //     end;
    //     tmp_idx := i * 400 + index;
    // end;
    tmp_idx := i * 400 + index;
End.
