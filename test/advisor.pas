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
    tmp_int : Integer;
    zero : char;
    split : char;
    A : char;
    B : char;
    C : char;
    D : char;
    E : char;
    F : char;

    tmp_string : string;

    intzero: Integer;
    intnine : Integer;



function char2int(a: char):integer;
begin
    if a = '0' then begin
        char2int := 0;
    end else if a = '1' then begin
        char2int := 1;
    end else if a = '2' then begin
        char2int := 2;
    end else if a = '3' then begin
        char2int := 3;
    end else if a = '4' then begin
        char2int := 4;
    end else if a = '5' then begin
        char2int := 5;
    end else if a = '6' then begin
        char2int := 6;
    end else if a = '7' then begin
        char2int := 7;
    end else if a = '8' then begin
        char2int := 8;
    end else if a = '9' then begin
        char2int := 9;
    end else begin
        char2int := -1;
    end;
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
    intzero := 0;
    intnine := 9;


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
        // Write(courses[tmp_idx] );
        // write('tmp_idx = ');
        // write(tmp_idx);
        // write('\n');

        while True do begin
            Read(ch);
            if ch = '\n' then
                break;
            tmp_idx := num * 400 + index;
            courses[tmp_idx] := ch;
            index := index + 1;
            // Write(courses[tmp_idx] );
            // write('tmp_idx = ');
            // write(tmp_idx);
            // write('\n');
        end;

        tmp_idx := num * 400 + index;
        // TODO \0
        courses[tmp_idx] := myeof;

        // Write(courses[tmp_idx] );

        is_passed[num] := 0;
        num := num + 1;
    end;

    

    // debug the input
    // for i:=0 to (num-1) do begin
    //     Write('input ');
    //     writeln(i);
    //     index := 0;
    //     while True do begin
    //         tmp_idx := i * 400 + index;
    //         tmp_value := courses[tmp_idx];
    //         write(tmp_value);
    //         if (tmp_value = myeof) then begin
    //             write('\n');
    //             break;
    //         end; 
    //         index := index + 1;   
    //     end;

    // end;

    // read(ch);

    // before is ok!

    for i:=0 to (num-1) do begin
        index := 0;
        field := 0;
        credit := 0;
        key := 0;

        tmp_idx := i * 400 + index;
        
        tmp_value := courses[tmp_idx] ;

        while (tmp_value <> myeof) do begin

            // write('i=');
            // write(i);
            // write('\n');

            

            // write('\n');
            // write('tmp_idx = ');
            // Write(tmp_idx);
            // Write('\n');

            // write('tmp_value = ');
            // Write(tmp_value);
            // Write('\n');

            // write('courses[tmp_idx] = ');
            // write(courses[tmp_idx]);
            // write('\n');
            // write('field = ');
            // write(field);
            // write('\n');

            // write('my index = ');
            // write(index);
            // write('\n');

            // if field = 4 then begin
            //     break;
            // end;

            tmp_idx := i * 400 + index;
            tmp_value := courses[tmp_idx] ;

            if (tmp_value = split) then begin // not such class
                field := field + 1;
                index := index + 1;
            end;

            if (field = 0) then begin
                tmp_idx := i * 400 + index;
                tmp_int := courses[tmp_idx];
                tmp_int := char2int(tmp_value);

                if (( tmp_int <= intnine) and (tmp_int >= intzero)) then begin
                    tmp_value := courses[tmp_idx];
                    c_tmp1 := char2int(tmp_value);
                    tmp_value := zero; 
                    c_tmp2 := char2int(tmp_value);
                    key := key * 10 + c_tmp1 - c_tmp2;
                    // write('key = ');
                    // write(key);
                    // write('\n');
                end;
                index := index + 1;
            end else if (field = 1) then begin
                tmp_idx := i * 400 + index;
                tmp_value := courses[tmp_idx];
                c_tmp1 := char2int(tmp_value);
                tmp_value := zero; 
                c_tmp2 := char2int(tmp_value);

                credit := c_tmp1 - c_tmp2;
                total_credits := total_credits + credit;
                // write('total_credits = ');
                // writeln(total_credits);

                map[key] := i;
                index := index + 1;
            end else if (field = 2) then begin
                tmp_idx := i * 400 + index;
                tmp_value := courses[tmp_idx];
                if ( courses[tmp_idx] <> '|') then begin
                    index := index + 1;
                end;
            end else if (field = 3) then begin
                tmp_idx := i * 400 + index;
                tmp_value := courses[tmp_idx];

                if (tmp_value <> myeof) then begin
                    if (tmp_value = 'A') then begin
                        attempted_credits := attempted_credits + credit;
                        passed_credits := passed_credits + credit;
                        total_score := total_score + 4 * credit;
                        is_passed[i] := 1;
                    end;
                    if (tmp_value = 'B') then begin
                        attempted_credits := attempted_credits + credit;
                        passed_credits := passed_credits + credit;
                        total_score := total_score + 3 * credit;
                        is_passed[i] := 1;
                    end;
                    if (tmp_value = 'C') then begin
                        attempted_credits := attempted_credits + credit;
                        passed_credits := passed_credits + credit;
                        total_score := total_score + 2 * credit;
                        is_passed[i] := 1;
                    end;
                    if (tmp_value  = 'D') then begin
                        attempted_credits := attempted_credits + credit;
                        passed_credits := passed_credits + credit;
                        total_score := total_score + credit;
                        is_passed[i] := 1;
                    end;
                    if (tmp_value = 'F') then begin
                        attempted_credits := attempted_credits + credit;
                    end;
                    index := index + 1;//cannot out of this!!!
                end;
                tmp_idx := i * 400 + index;
                tmp_value := courses[tmp_idx] ;
            end;
            tmp_idx := i * 400 + index;
            tmp_value := courses[tmp_idx] ;
        end;
        tmp_idx := i * 400 + index;
        tmp_value := courses[tmp_idx] ;

        // if field = 4 then begin
        //     break;
        // end;
    end;

    if (attempted_credits <> 0) then begin
        GPA := 1.0 * total_score / attempted_credits;
    end;
    remained_credits := total_credits - passed_credits;

    // write('total_credits = ');
    // writeln(total_credits);

    write('GPA: ');
    write(GPA);
    write('\n');

    write('Hours Attempted: ');
    write(attempted_credits);
    write('\n');

    write('Hours Completed: ');
    write(passed_credits);
    write('\n');

    write('Credits Remaining: ');
    write(remained_credits);
    write('\n');
    
    // tmp_string := 
    write('\n');
    // write('\n');
    write('Possible Courses to Take Next');
    write('\n');

    if (remained_credits = 0) then begin
        writeln('  None - Congratulations!');
    end
    else begin // find the class need to take
        value := 0;
        flag := 1;
        j := 0;

        for i:=0 to (num-1) do begin
            // write('is_passed[');
            // write(i);
            // write(']=');
            // writeln(is_passed[j]);

            if (is_passed[i] = 0) then begin // not even passed, refer
                index := 0;
                j := 0;
                tmp_idx := i * 400 + index;
                while (courses[tmp_idx] <> split) do begin // left courses name
                    course_name[j] := courses[tmp_idx];
                    // write('course_name[');
                    // write(j);
                    // write(']=');
                    // writeln(course_name[j]);

                    j := j + 1;
                    index := index + 1;
                    tmp_idx := i * 400 + index;
                    
                end;

                course_name[j] := myeof; // store courses name
                

                // write('courses[');
                // write(tmp_idx);
                // write(']=');
                // writeln(courses[tmp_idx]);

                index := index + 1;
                tmp_idx := i * 400 + index;
                while (courses[tmp_idx] <> split) do begin
                    index := index + 1;
                    tmp_idx := i * 400 + index;
                end;
                index := index + 1; // skip '|'

                tmp_idx := i * 400 + index;

                // write('courses[');
                // write(tmp_idx);
                // write(']=');
                // writeln(courses[tmp_idx]);

                if (courses[tmp_idx] = split)then begin // output left courses name, because there is no other dependent classes
                    write('  ');
                    for k:=0 to (j-1) do begin
                        write(course_name[k]);
                    end;
                    write('\n');
                end
                else begin

                    flag := 1;
                    key := 0;

                    tmp_idx := i * 400 + index;
                    while (courses[tmp_idx] <> split) do begin //there is other class name
                        tmp_value := courses[tmp_idx];
                        tmp_int := char2int(tmp_value);

                        if (( tmp_int <= intnine) and (tmp_int >= intzero)) then begin
                            tmp_value := courses[tmp_idx];
                            c_tmp1 := char2int(tmp_value);
                            tmp_value := zero;
                            c_tmp2 := char2int(tmp_value);
                            key := key * 10 + c_tmp1 - c_tmp2; // class name enum key
                        end;
                        
                        tmp_idx := i * 400 + index;
                        if (courses[tmp_idx] = ',') then begin
                            value := map[key];
                            if (is_passed[value] = 0) then begin
                                flag := 0; //dependent class not pass, ignore this one
                            end;
                            key := 0; //clear key
                        end;

                        tmp_idx := i * 400 + index;
                        if (courses[tmp_idx] = ';') then begin
                            value := map[key];
                            if (is_passed[value] = 0) then begin
                                flag := 0;
                            end;
                            key := 0;
                            if (flag = 1) then begin
                                break;
                            end
                            else begin
                                flag := 1;
                            end;
                        end;
                        index := index + 1;
                        tmp_idx := i * 400 + index;
                    end;

                    tmp_idx := i * 400 + index;
                    if (courses[tmp_idx] = split) then begin
                        value := map[key];
                        if (is_passed[value] = 0) then begin
                            flag := 0;
                        end;
                    end;

                    if (flag = 1) then begin
                        write('  ');
                        for k:=0 to (j-1) do begin
                            write(course_name[k]);
                        end;
                        write('\n');
                    end;
                    tmp_idx := i * 400 + index;
                end;
                tmp_idx := i * 400 + index;
            end;
            tmp_idx := i * 400 + index;
        end;
        tmp_idx := i * 400 + index;
    end;
    tmp_idx := i * 400 + index;

    // write('\n');
End.
