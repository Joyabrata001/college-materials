create table item_mstr(
    item_id numeric(10) primary key,
    quantity numeric(5)
);

create table item_tr(
    item_id numeric(10) primary key references item_mstr(item_id) on delete cascade,
    quantity numeric(5)
);

insert into item_mstr values (10001, 10);
insert into item_mstr values (10002, 9);
insert into item_mstr values (10003, 8);


create or replace function processEdit()
    returns trigger
    language plpgsql as $$
        begin
            update item_mstr set quantity = quantity - new.quantity where item_id = new.item_id;
            return null; -- use of trigger return is valid on before trigger only
        end;
    $$;

create trigger updateInsertMSTR
    after insert
    on item_tr
    for each row
    execute function processEdit();

select * from item_mstr order by item_id;

insert into item_tr values (10001, 6);
insert into item_tr values (10002, 5);
insert into item_tr values (10003, 2);

select * from item_mstr order by item_id;

drop table item_tr;
drop table item_mstr;

