CREATE TABLE depts (
	deptcode varchar(4) PRIMARY KEY,
	deptname varchar(50) NOT NULL
);

CREATE TABLE students (
	rollno numeric(8) PRIMARY KEY,
	name varchar(30),
	bdate date CHECK (bdate < '2021-01-01'),
	deptcode char(4) REFERENCES depts (deptcode) ON DELETE CASCADE,
	hostel numeric CHECK (hostel < 10),
	parent_inc numeric(8, 1)
);

CREATE TABLE faculty (
	fac_code varchar(8) PRIMARY KEY,
	fac_name varchar(30) NOT NULL,
	fac_dept varchar(5) REFERENCES depts (deptcode)
);

CREATE TABLE crs_offrd (
	crs_code varchar(10) PRIMARY KEY,
	crs_name varchar(35) NOT NULL,
	crs_credits numeric(2, 1),
	crs_fac_cd varchar(8) REFERENCES faculty (fac_code)
);

CREATE TABLE crs_regd (
	crs_rollno numeric(8) REFERENCES students (rollno),
	crs_cd char(10) REFERENCES crs_offrd (crs_code),
	marks numeric(5, 2),
	PRIMARY KEY (crs_rollno, crs_cd)
);

INSERT INTO depts VALUES ('CST', 'Computer Science and Technology');
INSERT INTO depts VALUES ('ELE', 'Electronics and Telecommunication');
INSERT INTO depts VALUES ('PH', 'Physics');
INSERT INTO depts VALUES ('CH', 'Chemistry');
INSERT INTO depts VALUES ('ARCH', 'Architecture');

INSERT INTO students VALUES (1, 'Abhiroop', '2002-09-25', 'CST', 8, 16000);
INSERT INTO students VALUES (2, 'Karmanya', '2001-09-25', 'ELE', 7, 18000);
INSERT INTO students VALUES (3, 'Mehul', '2001-08-25', 'ELE', 5, 19000);
INSERT INTO students VALUES (4, 'Rahul', '2001-08-26', 'CST', 9, 20000);
INSERT INTO students VALUES (5, 'Aditi', '2001-09-25', 'ELE', 5, 9000);
INSERT INTO students VALUES (92005102, 'Himanshu', '2001-08-25', 'ELE', 5, 22000);
INSERT INTO students VALUES (92005010, 'Sanjana', '2000-08-26', 'CST', 9, 21000);
INSERT INTO students VALUES (6, 'Srijan', '2001-08-26', 'ELE', 5, 26000);
INSERT INTO students VALUES (7, 'master', '2001-09-26', 'ELE', 5, 28000);
INSERT INTO students VALUES (8, 'Superconductors', '2000-09-26', 'ARCH', 5, 18000);
INSERT INTO students VALUES (9, 'Shamra', '2000-12-01', 'ELE', 9, 10000);

INSERT INTO faculty VALUES ('CST_F1', 'dbp', 'CST');
INSERT INTO faculty VALUES ('CST_F2', 'hed', 'CST');
INSERT INTO faculty VALUES ('EE_F1', 'nls', 'ELE');
INSERT INTO faculty VALUES ('EE_F2', 'jst', 'ELE');
INSERT INTO faculty VALUES ('PH_F1', 'sfgf', 'PH');
INSERT INTO faculty VALUES ('CH_F1', 'poi', 'CH');
INSERT INTO faculty VALUES ('ARCH_F1', 'wer', 'ARCH');

INSERT INTO crs_offrd VALUES ('CS101', 'DBMS', 4, 'CST_F1');
INSERT INTO crs_offrd VALUES ('CS102', 'OS', 5, 'CST_F2');
INSERT INTO crs_offrd VALUES ('CS103', 'MIS', 6, 'CST_F1');
INSERT INTO crs_offrd VALUES ('CS104', 'Software Engg.', 7, 'CST_F2');
INSERT INTO crs_offrd VALUES ('EE101', 'ELE Course 1', 6, 'EE_F1');
INSERT INTO crs_offrd VALUES ('EE102', 'ELE Course 2', 7, 'EE_F2');
INSERT INTO crs_offrd VALUES ('EE103', 'ELE Course 3', 5, 'EE_F1');
INSERT INTO crs_offrd VALUES ('EE104', 'ELE Course 4', 4, 'EE_F2');
INSERT INTO crs_offrd VALUES ('PH106', 'PH Course 1', 4, 'PH_F1');
INSERT INTO crs_offrd VALUES ('CH103', 'CH Course 1', 3, 'CH_F1');
INSERT INTO crs_offrd VALUES ('ARCH101', 'ARCH Course 1', 4, 'ARCH_F1');

INSERT INTO crs_regd VALUES (1, 'CS101', 89.6);
INSERT INTO crs_regd VALUES (1, 'CS102', 98.6);
INSERT INTO crs_regd VALUES (1, 'CS103', 67.6);
INSERT INTO crs_regd VALUES (1, 'CS104', 95.6);
INSERT INTO crs_regd VALUES (1, 'PH106', 100);
INSERT INTO crs_regd VALUES (1, 'CH103', 90);
INSERT INTO crs_regd VALUES (2, 'EE101', 89.4);
INSERT INTO crs_regd VALUES (2, 'EE102', 92.6);
INSERT INTO crs_regd VALUES (2, 'EE103', 87.7);
INSERT INTO crs_regd VALUES (2, 'EE104', 75.9);
INSERT INTO crs_regd VALUES (3, 'EE102', 94.6);
INSERT INTO crs_regd VALUES (3, 'EE103', 82.7);
INSERT INTO crs_regd VALUES (3, 'EE104', 79.4);
INSERT INTO crs_regd VALUES (3, 'PH106', 84.3);
INSERT INTO crs_regd VALUES (3, 'CH103', 97.8);
INSERT INTO crs_regd VALUES (4, 'CS101', 82.6);
INSERT INTO crs_regd VALUES (4, 'CS102', 68.6);
INSERT INTO crs_regd VALUES (4, 'CS103', 63.6);
INSERT INTO crs_regd VALUES (4, 'CS104', 90.6);
INSERT INTO crs_regd VALUES (4, 'PH106', 82.3);
INSERT INTO crs_regd VALUES (4, 'CH103', 95.8);
INSERT INTO crs_regd VALUES (5, 'EE101', 90.4);
INSERT INTO crs_regd VALUES (5, 'EE102', 91.6);
INSERT INTO crs_regd VALUES (5, 'EE103', 89.7);
INSERT INTO crs_regd VALUES (5, 'EE104', 76.9);
INSERT INTO crs_regd VALUES (5, 'PH106', 82.8);
INSERT INTO crs_regd VALUES (5, 'CH103', 95.9);
INSERT INTO crs_regd VALUES (92005102, 'EE101', 89.4);
INSERT INTO crs_regd VALUES (92005102, 'EE102', 93.6);
INSERT INTO crs_regd VALUES (92005102, 'EE103', 86.7);
INSERT INTO crs_regd VALUES (92005102, 'EE104', 70.4);
INSERT INTO crs_regd VALUES (92005102, 'PH106', 88.8);
INSERT INTO crs_regd VALUES (92005102, 'CH103', 91.9);
INSERT INTO crs_regd VALUES (92005010, 'CS101', 83.6);
INSERT INTO crs_regd VALUES (92005010, 'CS102', 34.6);
INSERT INTO crs_regd VALUES (92005010, 'CS103', 69.6);
INSERT INTO crs_regd VALUES (92005010, 'CS104', 90.3);
INSERT INTO crs_regd VALUES (92005010, 'PH106', 82.8);
INSERT INTO crs_regd VALUES (92005010, 'CH103', 99.9);
INSERT INTO crs_regd VALUES (7, 'CS101', 90.4);
INSERT INTO crs_regd VALUES (7, 'CS102', 90.4);
INSERT INTO crs_regd VALUES (7, 'CS103', 90.4);
INSERT INTO crs_regd VALUES (7, 'CS104', 90.4);
INSERT INTO crs_regd VALUES (7, 'EE101', 90.4);
INSERT INTO crs_regd VALUES (7, 'EE102', 91.6);
INSERT INTO crs_regd VALUES (7, 'EE103', 89.7);
INSERT INTO crs_regd VALUES (7, 'EE104', 76.9);
INSERT INTO crs_regd VALUES (7, 'PH106', 82.8);
INSERT INTO crs_regd VALUES (7, 'CH103', 95.9);
INSERT INTO crs_regd VALUES (7, 'ARCH101', 99.9);
INSERT INTO crs_regd VALUES (6, 'CS101', 90.4);
INSERT INTO crs_regd VALUES (6, 'CS102', 90.4);
INSERT INTO crs_regd VALUES (6, 'CS103', 90.4);
INSERT INTO crs_regd VALUES (6, 'CS104', 90.4);
