create table emp(
    emp_id numeric(10) primary key,
    salary numeric(10) default 0
);

insert into emp values (510719007, 100000);
insert into emp values (510719008, 110000);
insert into emp values (510719009, 120000);
insert into emp values (510719010, 900000);

select * from emp order by emp;


create or replace function raiseWage(percetage int)
    returns void 
    language plpgsql as $$
        declare
            emp_rec record;
            emp_cur cursor for select * from emp order by emp;
        begin
            open emp_cur;

            loop
                fetch emp_cur into emp_rec; -- fetch row into record
                exit when not found;    -- exit when no more row to fetch

                update emp
                set salary = salary + salary * percetage /100
                where emp_id = emp_rec.emp_id;
            end loop;

            close emp_cur;
        end;
    $$;

select raiseWage(15);
select * from emp order by emp;
drop function raiseWage;
drop table emp;