-- Retrieve the name of the student(s) who obtained second highest marks in ‘DBMS’.
-- Idea: ordet by has limit and offset
-- limit: limit no.of outputs
-- offset: generally starting point is start, offset x increses starting point by x no. of rows
-- NOTE: direct order then limit 1 offset 1 can give wring result when there are mutiple student with max marks in DBMS 
select rollno, name, marks, crs_cd 
from students, crs_regd, crs_offrd
where   
    crs_rollno = rollno
    and crs_cd = crs_code
    and crs_name = 'DBMS'
    and marks = (   select distinct(marks)
                    from crs_regd, crs_offrd
                    where crs_cd = crs_code
                    and crs_name = 'DBMS'
                    order by marks desc limit 1 offset 1);



-- Find out the differences between highest and lowest marks obtained in each subject.
select crs_cd,max(marks) - min(marks) as mark_diff
from crs_regd
group by crs_cd
order by crs_cd;

-- Assuming the existance of several interdepartmental courses, retrieve the
-- name of the student(s) who is(are) studing under at least one faculty from
-- each department.

select name , count(distinct fac_dept)
from    students 
        left join crs_regd on crs_rollno = rollno
        left join crs_offrd on crs_cd = crs_code
        left join faculty on crs_fac_cd = fac_code
group by name
having count(distinct fac_dept) = (select count(*) from depts);

-- Another Possible Solution
SELECT 
        name
FROM 
        crs_offrd
        ,faculty
        ,crs_regd
        ,students
WHERE 
        crs_fac_cd=fac_code
        AND crs_cd=crs_code
        AND crs_rollno=rollno
GROUP BY name
HAVING COUNT(DISTINCT(fac_dept)) = (SELECT COUNT(*) FROM depts);


-- Assuming the existance of several interdepartmental courses, retrieve the
-- name of the student(s) who is(are) studing under the faculties only from
-- his(their) own department.

-- Step 1: left joins
select *
from    students
        left join crs_regd on crs_rollno = rollno
        left join crs_offrd on crs_cd = crs_code
        left join faculty on crs_fac_cd = fac_code;


-- step 2 : get student rollno who have enrolled on subjects from only one depratment
select rollno
from    
        students 
        left join crs_regd on crs_rollno = rollno
        left join crs_offrd on crs_cd = crs_code
        left join faculty on crs_fac_cd = fac_code
group by rollno
having count(distinct fac_dept) = 1;

--step 3: use the rollno's found in step 2 to get whole data from table, and then see that if deptcode = fac_dept present
select distinct name
from    
        (
                students 
                left join crs_regd on crs_rollno = rollno 
                left join crs_offrd on crs_cd = crs_code
                left join faculty on crs_fac_cd = fac_code
        ) 
        natural join  -- join will happen by roll no as both name same
        (
                select rollno
                from    
                        students 
                        left join crs_regd on crs_rollno = rollno
                        left join crs_offrd on crs_cd = crs_code
                        left join faculty on crs_fac_cd = fac_code
                group by rollno
                having count(distinct fac_dept) = 1
        ) as tb
where deptcode = fac_dept;

-- Another possible Solution
SELECT rollno, name 
FROM students 
WHERE rollno NOT IN (SELECT DISTINCT(rollno) 
                      FROM crs_offrd, faculty, crs_regd, students 
                      WHERE crs_fac_cd=fac_code 
                      AND crs_cd=crs_code 
                      AND crs_rollno=rollno 
                      AND fac_dept!=deptcode 
                      GROUP BY rollno
                      
                      UNION 
                      ((select rollno from students) EXCEPT (select distinct crs_rollno from crs_regd)));