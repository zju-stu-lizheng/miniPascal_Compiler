program typerecord;
type
  InfoType = record
    MyName : String;
    Age : integer;
    City, State : integer;
    Zip : integer;
  end;
var
  Book1, Book2: InfoType;
begin
  Book1.MyName := 'AI';
  Write(Book1.MyName);
end.