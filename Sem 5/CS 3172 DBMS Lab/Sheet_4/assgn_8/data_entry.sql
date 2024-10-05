create table Customer(
    cust_id numeric(10) primary key check(cust_id between 100 and 10000), 
    cust_name varchar(20),
    annual_revenue numeric(10),
    cust_type varchar(20) check(cust_type in ('MANUFACTURER', 'WHOLESALER', 'RETAILER'))
);

-- Numeric(10,2) means number will have 10 digit and 2 digit after decimal point
-- Numeric(10) means number will have 10 diigt and no digit after decimal point

create table Truck(
    truck_no numeric(10) primary key,
    driver_name varchar(20)
);

create Table City(
    city_name varchar(10) primary key,
    population numeric(10)
);

create Table Shipment(
    shipment_no numeric(10),
    cust_id numeric(10) references Customer(cust_id) on delete cascade,
    weight integer check (weight < 1000), -- weight in pounds
    truck_no numeric(10) references Truck(truck_no) on delete set null,
    destination varchar(10) references City(city_name),
    ship_date date,

    primary key(shipment_no, cust_id)
);

insert into Customer values(1001, 'Kalpana', 120000, 'MANUFACTURER');   
insert into Customer values(1002, 'Abhiram', 125000, 'MANUFACTURER');   
insert into Customer values(2001, 'Arnav', 150000, 'WHOLESALER');       
insert into Customer values(2002, 'Raghav', 155000, 'WHOLESALER');  -- hyderabad exclusuve    
insert into Customer values(3001, 'Om', 180000, 'RETAILER');           
insert into Customer values(3002, 'Ajay', 185000, 'RETAILER');         

insert into Truck(truck_no, driver_name) values(4001, 'Aarush');
insert into Truck(truck_no, driver_name) values(4002, 'Prabodh');
insert into Truck(truck_no, driver_name) values(4003, 'Iqbal');

insert into City values ('Mumbai',12500000);
insert into City values ('Kolkata', 14900000);
insert into City values ('Chennai', 11235018);
insert into City values ('Hyderabad', 102686);
-- insert into City values ('Pune', 1842686);  -- used for q7

-- 25th
insert into Shipment values(5001, 1001, 250, 4001, 'Mumbai', '2021-09-25');
insert into Shipment values(5001, 1002, 280, 4001, 'Mumbai', '2021-09-25');
insert into Shipment values(5001, 2001, 300, 4001, 'Mumbai', '2021-09-25');
insert into Shipment values(5001, 3002, 160, 4001, 'Mumbai', '2021-09-25');

insert into Shipment values(5002, 1001, 250, 4002, 'Chennai', '2021-09-25');
insert into Shipment values(5002, 1002, 200, 4002, 'Chennai', '2021-09-25');

insert into Shipment values(5003, 1001, 45, 4003, 'Kolkata', '2021-09-25');
insert into Shipment values(5003, 2001, 15, 4003, 'Kolkata', '2021-09-25');
insert into Shipment values(5003, 3002, 60, 4003, 'Kolkata', '2021-09-25');

insert into Shipment values(5004, 1001, 80, 4001, 'Hyderabad', '2021-09-25');
insert into Shipment values(5004, 1002, 12, 4001, 'Hyderabad', '2021-09-25');
insert into Shipment values(5004, 2001, 43, 4001, 'Hyderabad', '2021-09-25');
insert into Shipment values(5004, 2002, 45, 4001, 'Hyderabad', '2021-09-25');
insert into Shipment values(5004, 3001, 46, 4001, 'Hyderabad', '2021-09-25');
insert into Shipment values(5004, 3002, 17, 4001, 'Hyderabad', '2021-09-25');

-- 26th
insert into Shipment values(5005, 1001, 250, 4002, 'Mumbai', '2021-09-26');
insert into Shipment values(5005, 3001, 743, 4002, 'Mumbai', '2021-09-26');

insert into Shipment values(5006, 1002, 150, 4001, 'Chennai', '2021-09-26');

insert into Shipment values(5007, 2001, 400, 4001, 'Kolkata', '2021-09-26');
insert into Shipment values(5007, 3002, 84, 4001, 'Kolkata', '2021-09-26');

insert into Shipment values(5008, 1002, 63, 4003, 'Hyderabad', '2021-09-26');
insert into Shipment values(5008, 2002, 74, 4003, 'Hyderabad', '2021-09-26');
insert into Shipment values(5008, 3002, 26, 4003, 'Hyderabad', '2021-09-26');