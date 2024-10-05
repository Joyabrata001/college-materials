-- Display the highest parent incomes, in descending order, for each
-- department excluding ‘ARCH’ such that only those highest parent incomes
-- will appear that are below 12,000.
select name, parent_inc
from students
where 
    deptcode != 'ARCH'
    AND parent_inc < 12000
order by parent_inc desc;


-- Retrieve the fifth highest parent income for hostel number 5.
select parent_inc 
from students
where hostel = 5
order by parent_inc desc limit 1 offset 4;

-- Find the roll number of the students from each department who 
-- obtained highest total marks in their own department.

-- IDEA: first group by  rollno to get sum(marks), then use resulting table to group by max(sum(marks)), use the result to get name, and rollno

--STEP 1: group by rollno and get sum marks
select 
    deptcode
    ,rollno
    ,name
    ,sum(marks) as sum
from 
    students 
    inner join crs_regd on crs_rollno = rollno
group by rollno;

-- step 2: use resulting table (see the from table) and group by deptcode to get max(sum(marks))
select 
    deptcode
    ,max(sum)
from    
    (   
        select 
            deptcode
            ,rollno
            ,name
            ,sum(marks) as sum
            from 
                students 
                inner join crs_regd on crs_rollno = rollno
            group by  rollno
    ) as tb1
group by deptcode;


-- step 3: use the previous made table's ans to get name, rollno
select * 
from    
    (   
        select 
            deptcode
            ,rollno
            ,name
            ,sum(marks) as sum
        from 
            students 
            inner join crs_regd on crs_rollno = rollno
        group by  rollno
    ) as tb1
where 
    (deptcode, sum) in  (  
                            select deptcode,max(sum)
                            from    
                                (   
                                    select 
                                        deptcode
                                        ,rollno
                                        ,name
                                        ,sum(marks) as sum
                                    from 
                                        students 
                                        inner join crs_regd on crs_rollno = rollno
                                    group by  rollno
                                ) as tb1
                            group by deptcode
                        );
