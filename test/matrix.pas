program arraymul;
var 
	array_a : array[0 .. 625] of integer;
    array_b : array[0 .. 625] of integer;
    array_c : array[0 .. 625] of integer;
    m_a : integer;
    n_a : integer;
    s_a : integer;
    m_b : integer;
    n_b : integer;
    s_b : integer;
    s_c : integer;
    i : integer;
    j : integer;
    k : integer;
    tmp_a : Integer;
    tmp_b : Integer;
    tmp_c : Integer;
begin
    //读入矩阵A
    ReadLn(m_a,n_a);
    // WriteLn('m=',m_a,',n=',n_a);
    s_a:=m_a*n_a;
    // WriteLn('m * n = ',s_a);

    for i:=0 to s_a-1 do Read(array_a[i]);
    //读入矩阵B
    ReadLn(m_b,n_b);
    // WriteLn('m=',m_b,',n=',n_b);
    s_b:=m_b*n_b;
    // WriteLn('m * n = ',s_b);

    for i:=0 to s_b-1 do Read(array_b[i]);

    if n_a <> m_b then
        WriteLn('Incompatible Dimensions')
    else begin
        //进行矩阵乘法
        for i:=0 to m_a-1 do
        begin
            for j:=0 to n_b-1 do
            begin
                for k:=0 to m_b-1 do
                begin
                    tmp_c := i*n_b+j;
                    tmp_b := k*n_b+j;
                    tmp_a := i*m_b+k;
                    array_c[tmp_c] := array_c[tmp_c] + array_b[tmp_b] * array_a[tmp_a];
                end;
            end;
        end;

        //测试输出
        s_c := m_a*n_b;
        for i:=0 to m_a-1 do
        begin
            for j:=0 to n_b-1 do
            begin
                k:= i*n_b+j;
                printf(array_c[k]);
            end;
            WriteLn;
        end; 
    end;
end.