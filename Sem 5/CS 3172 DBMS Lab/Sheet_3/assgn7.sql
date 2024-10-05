-- Create a view named as cse_stud for ‘CSE’ dept students having attributes rollno, name,
-- hostel
create view cse_stud as
    select rollno, name, hostel, parent_inc
    from students
    where deptcode = 'CST';

-- Insert a new student of CSE. Analyse the result.
insert into cse_stud(rollno, name, hostel, parent_inc)
    values (1234, 'hola', 9, 100000);

-- Analysis 1: new data created at base table also, but
-- it only has rollno, name, hostel    

-- Analysis 2: below command does not show data      
select * from cse_stud;
-- but this shows new data
select * from students;

-- Analysis 3: lets go other way around
INSERT INTO students VALUES (10, 'Shamrrwer', '2000-12-01', 'CST', 9, 10000);
-- This change got reflected to view

-- Increment parental income by Rs. 5000 for all peeps in table.
update students 
set parent_inc = parent_inc + 5000;
-- Analysis 1: changes in actual table refelcts in view

-- delete the view
drop view cse_stud;





-- Create another view of all students in dept Mechanical Engineering (department Name).
-- The view will contain attributes namely Roll-No, Name, Department Name, Age.
create view mech_stud as
    select 
        rollno, 
        name, 
        deptcode, 
        extract(year from age(bdate)) as age
    from students
    where deptcode = 'MECH';

-- Insert a new student of Mechanical Engineering Department.
INSERT INTO students VALUES (14, 'Vanika', '2002-9-01', 'MECH', 8, 14000);
-- Analysis: this gets added to view

-- Delete a student (for a given Name) of the same department
delete from students
where name = 'Vanika';
-- Analysis: removed from view also


-- Shift a student (for a given Name) from Mechanical to Computer Science.
update students 
set deptcode = 'CST'
where name = 'Vani';
-- Analysis: roll 13 got removed from mech_stud but now visible in cse_stud

select * from mech_stud;
drop view mech_stud;