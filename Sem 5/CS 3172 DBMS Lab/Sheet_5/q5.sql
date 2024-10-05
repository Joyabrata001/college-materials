create table emp(
    emp_id numeric(10) primary key,
    salary numeric(10) default 0
);

insert into emp values (510719007, 100000);
insert into emp values (510719008, 110000);
insert into emp values (510719009, 120000);
insert into emp values (510719010, 900000);

select * from emp order by emp;

create or replace procedure raiseWage(in id numeric(10), in amount numeric(10))
    language plpgsql as $$
        begin
            if(id not in (select E.emp_id from emp E)) then
                raise exception 'nonexistent ID --> %', emp_id
                    using hint= 'Please check your emp_id';
            elsif (amount is null) then
              raise exception 'amount can''t be null'
                    using hint= 'Please check your amount';
            end if;

            update emp
               set salary=salary + amount
             where emp_id = id;
        end;
    $$;

call raiseWage(510719010,1000);

select * from emp order by emp;
drop procedure raiseWage;
drop table emp;