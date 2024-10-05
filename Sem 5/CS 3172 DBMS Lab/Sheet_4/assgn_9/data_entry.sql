create table DEPT(
    DEPTNO varchar(5) primary key check(DEPTNO like 'D%'),
    DNAME varchar(10) check(
                            DNAME = 'Accounting'
                            or DNAME = 'Sales'
                            or DNAME = 'Research'
                            or DNAME = 'Operations'
                            ),
    LOC varchar(10)
);

insert into DEPT values ('D001', 'Accounting', 'Mumbai');
insert into DEPT values ('D002', 'Sales', 'Hyderabad');
insert into DEPT values ('D003', 'Research', 'Chandigarh');
insert into DEPT values ('D004', 'Operations', 'Kolkata');

create table EMP(
    EMPNO numeric(10) primary key check(EMPNO between 7000 and 8000),
    ENAME varchar(10), --varchar(10) checks ENAME must not exceed 10 characters
    JOB varchar(10) check ( JOB in ('President', 'Manager', 'Clerk', 'Salesman', 'Analyst')),
    MGR numeric(10),    --manager emp id
    HIREDATE date,
    SAL numeric(10),
    COMM numeric(5) default 0 check(COMM < 1500),
    DEPTNO varchar(5) references DEPT(DEPTNO)
);

-- row with null MGR is President 
insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO)
values (7001, 'Nirmal', 'President', '2020-09-21', 9000, 1000, 'D001');

insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO, MGR)
values (7002, 'Sudarshan', 'Manager', '2021-08-21', 1000, 1001, 'D001', 7001);

insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO, MGR)
values (7003, 'Sharma', 'Clerk', '2021-09-10', 1500, 1002, 'D001', 7002);

insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO, MGR)
values (7004, 'Akshi', 'Salesman', '2021-08-15', 1600, 1003, 'D001', 7002);

insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO, MGR)
values (7005, 'Rajni', 'Analyst', '2021-09-15', 650, 1004, 'D001', 7002);




insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO)
values (7101, 'Lina', 'President', '2021-09-21', 9500, 1100, 'D002');

insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO, MGR)
values (7102, 'Diti', 'Manager', '2019-08-21', 905, 1101, 'D002', 7101);

insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO, MGR)
values (7103, 'Dhruv', 'Clerk', '2018-09-10', 1505, 1102, 'D002', 7102);

insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO, MGR)
values (7104, 'Aamani', 'Salesman', '2019-08-15', 5600, 1103, 'D002', 7102);




insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO)
values (7201, 'Kajal', 'President', '2020-10-21', 920, 1200, 'D003');

insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO, MGR)
values (7202, 'Karan', 'Manager', '2021-02-21', 1002, 1201, 'D003', 7201);

insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO, MGR)
values (7203, 'Dharma', 'Clerk', '2021-07-10', 15002, 1202, 'D003', 7202);

insert into EMP (EMPNO, ENAME, JOB, HIREDATE, SAL, COMM, DEPTNO, MGR)
values (7205, 'Kavi ', 'Analyst', '2021-05-15', 1652, 1204, 'D003', 7202);

