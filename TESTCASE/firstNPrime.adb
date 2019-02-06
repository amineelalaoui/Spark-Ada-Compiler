procedure isPrime is

n : Integer;
max : Integer;
i : Integer;
result : Boolean;

begin

read(max);
n := 2;

for n in 2 .. max loop
    --print(n);
    result := true;
    i := 2;
    if n = 1 then
    result := false;
    end if;

    while (i * i <= n) and (result = true) loop
    if n mod i = 0 then
        result := false;
    end if;
    i := i + 1;
    end loop;

    if(result = true) then
        print(n);
    end if;
end loop;

end isPrime;