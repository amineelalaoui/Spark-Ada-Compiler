procedure isWeekEnd is

  day : Integer;

begin

  read(day); 
  case day is
    when 1 =>
      print(0);
    when 2 =>
      print(0);
    when 3 =>
      print(0);
    when 4 =>
      print(0);
    when 5 =>
      print(0);
    when 6 =>
      print(1);
    when 7 =>
      print(1);
  end case;

end isWeekEnd;