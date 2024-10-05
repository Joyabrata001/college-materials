create table cust_acct(
    acc_no numeric(10) primary key,
    balance numeric(6) default 0
);

insert into cust_acct values (510719007, 100);
insert into cust_acct values (510719008, 1100);
insert into cust_acct values (510719009, 1200);
insert into cust_acct values (510719010, 900);

select * from cust_acct order by acc_no;

create or replace function updateTable(amount numeric(6))
    returns void
    language plpgsql
    as $$
    declare
        f record;
    begin
        for f in (select * from cust_acct) loop
            if(f.balance > amount) then
                update cust_acct
                set balance = balance - amount
                where acc_no = f.acc_no;
            end if;
        end loop;
    end;
$$;

select updateTable(1000);

select * from cust_acct order by acc_no;

drop function updateTable;
drop table cust_acct;