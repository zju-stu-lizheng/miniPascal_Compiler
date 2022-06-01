program ifstmt;
var
    curTerm1 :integer;
    curTerm2 :integer;
begin
    curTerm1 := 1 + 2*(2 + 3);
    
    if curTerm1 = 11 then
        curTerm2 := 5
    else
        curTerm2 := 7;
end.