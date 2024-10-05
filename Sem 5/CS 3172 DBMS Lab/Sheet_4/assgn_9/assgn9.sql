-- Display the difference between highest and lowest salary of each department in
-- descending order. Label the column as “Difference”.
select
    DNAME, 
    max(SAL) - min(SAL) as difference
from DEPT left join EMP on (DEPT.DEPTNO = EMP.DEPTNO)
group by DEPT.DEPTNO
order by difference desc;

-- List all the employees’ employee number and name along with their immediate
-- managers’ employee number and name.
select
    A.EMPNO as employee_id,
    A.ENAME as employee_name, 
    B.EMPNO as manager_id,
    B.ENAME as manager_name
from EMP A left join EMP B on (A.MGR = B.EMPNO);

-- Create a query that will display the total number of employees and the total number
-- of employees who were hired only in 2020. Give the column headings as “TOTAL”
-- and “TOTAL_2020” respectively.
select
    TOTAL, TOTAL_2020
from 
    (select count(*) as TOTAL from EMP) as tb1,
    (select
        count(*) as TOTAL_2020 
    from EMP 
    where HIREDATE between '2020-01-01' and '2020-12-31') as tb2;

-- Display the manager number and the salary of the lowest paid employee under that
-- manager. Exclude anyone whose manager is not known. Exclude any group where the
-- minimum salaryis less than 1000. Sort the output in descending order of salary.

select 
    MGR as manager_id,
    min(SAL) as min_salary
from EMP 
group by MGR
having
    MGR is not null
    and min(SAL) > 1000
order by min_salary desc;

-- Assume that there are some departments where no employee is assigned. Now, write
-- a query to display the department name, location name, number of employees, and the
-- average salary for all the employees in that department. Label the columns as
-- “DNAME”, “LOCATION”, “NUMBER OF PEOPLE”, and “AVERAGE SALARY”
-- respectively. Round the averge salary to two decimal places. The outcome of the
-- query must include the details of the departments where no employee is assigned and
-- in that case the “AVERAGE SALARY” for that department is to be displayed as 0
-- (zero).
select
    DNAME as "DNAME", 
    LOC as "LOCATION",
    count(EMPNO) as "NUMBER OF PEOPLE",
    coalesce(round(avg(SAL),2),0.0) as "AVERAGE SALARY"
from DEPT left join EMP on (EMP.DEPTNO = DEPT.DEPTNO)
group by DNAME, LOC;

---------------another method----------------
select 
    DNAME as "DNAME", 
    LOC as "LOCATION",
    (
        select count(*)
        from EMP
        where EMP.DEPTNO = DEPT.DEPTNO
    ) as "NUMBER OF PEOPLE",
    (
        select round(coalesce(avg(sal), 0.0), 2)
        from EMP
        where EMP.DEPTNO = DEPT.DEPTNO
    ) as "AVERAGE SALARY"
from DEPT;



-------------------------------------- Practices---------------------
-- Display status of employee who has salary more than 
-- avg salary of their department

select
    EMPNO,
    ENAME,
    SAL,
    DEPTNO,
    avg_sal
from
    EMP 
    natural join    (
                        select 
                            DEPTNO, 
                            avg(SAL) as avg_sal
                        from EMP
                        group by DEPTNO
                    ) as average_employee
    where 
    SAL > avg_sal;