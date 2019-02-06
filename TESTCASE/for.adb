procedure forStatement is

n : Integer := 1;
a, b : Integer;
max, min : Integer;
begin

min := 1;
max := 100;

read(a, b); 

for n in min .. (max * 2) loop

  if(n mod a = 0)  then
    print(n);
  elsif(n mod b = 0) then
    print(n);
  end if;

end loop; 

end forStatement;