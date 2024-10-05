-- Retrieve the name of the students whose name starts with ‘S’ and contains ‘r’
-- as the second last character.
-- Idea: use Regex
-- Hint: use `like` keyword, % -> many characters, _ -> one character
-- NOTE: like doesn't work with char(10), but works with varchar(10)
-- see this link: https://stackoverflow.com/questions/1543133/like-does-not-work-as-expected
select name
from students
where name like 'S%r_';

-- Retrieve the name of the youngest student(s) from the ‘CST’ department
-- along with the total marks obtained by him (them).
-- Hint: youngest age will have largest year
select name, bdate, sum(marks)
from students, crs_regd
where crs_rollno = rollno
and deptcode = 'CST'
group by rollno
having bdate = ( select max(bdate)
                from students
                where deptcode = 'CST');

-- Find the age of all the students.
-- Hint: look up the commands used here
select name, (EXTRACT(YEAR from AGE(NOW(), bdate))) as age
from students;