# Sample Guide for how to use PSQL in Ubuntu

Assumed you have installed PSQL and added your role

If you have not refer this : https://medium.com/@Josylad/how-to-install-postgresql-on-ubuntu-linux-mac-5e08b09b3fb9

first make a .sql file and write what all you want to do

Sample: (filename is `test.sql`)
```sql
create table course(
    cno integer, 
    cname varchar(20),
    age integer
);

insert into course values (1, 'Abhiroop', 18);
insert into course values (1, 'Sanjana', 21);
insert into course values(1, 'Rahul', 20);
insert into course values(1, 'Arnab', 20);

select * from course;

drop table course;
```

Now you need to start psql service
```
$ sudo service postgresql start
```

Now go inside psql service
```
$ psql
```

Now run the script 
```psql
user=# \i test.sql
```

and the file will be executed

## Specials

list all table = `\dt`
describe table = `\d+ TABLE_NAME`

