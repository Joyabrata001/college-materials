create table circle(
    radius real,
    circumference real
);

-- $$ -> consider as braces
create function insertIntoCircle(radius numeric(6,4)) 
    returns void
    language plpgsql as $$
        begin
            insert into circle values (radius, 2 * pi() * radius);
        end;
$$ ;
    

do $$
    begin
        for counter in 1..10 by 2 loop
            perform insertIntoCircle(counter);
        end loop;
    end;
$$;

select * from circle;

drop function insertIntoCircle;
drop table circle;

