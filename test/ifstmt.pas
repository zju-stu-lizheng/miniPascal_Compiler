program ifstmt;
Const
    constTerm1 = 3;
    constTerm2 = 3.14;
var
    curTerm1 :integer;
    curTerm2 :integer;
begin
    curTerm1 := constTerm1;
    curTerm1 := 1 + 2*(2 + 3);
    
    if curTerm1 = 11 then
        curTerm2 := 5
    else
        if curTerm1 = 12 then
            curTerm2 := 6
        else
            curTerm2 := 7;

    writeln(curTerm1);
    WriteLn(curTerm2);
end.