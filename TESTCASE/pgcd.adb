
procedure gcd is

a : Integer;
b : Integer;
temp : Integer := 0;

begin
read(a, b);
while b /= 0 loop
  temp := a;
  a := b;
  b := temp mod b;
end loop;

print (a);

end gcd;