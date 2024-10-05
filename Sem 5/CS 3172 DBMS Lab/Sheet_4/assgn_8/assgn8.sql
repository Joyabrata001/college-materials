-- 1)   Give names of customer who have sent packages (shipments) to Kolkata, Chennai
-- and Mumbai.
select 
    distinct cust_name
from
    Shipment S natural join Customer C 
where
    destination in ('Kolkata', 'Chennai' , 'Mumbai');


-- 2)   List the names of the driver who have delivered shipments weighing over 200
-- pounds.
select 
    distinct driver_name 
from
    Shipment S natural join Truck T
where
    S.weight > 200;


-- 3)   Retrieve the maximum and minimum weights of the shipments. Rename the output as
-- Max_Weight and Min_Weight respectively.
select 
    max(weight) as Max_Weight,
    min(weight) as Min_Weight
from
    Shipment;

-- 4)   For each customer, what is the average weight of package sent by the customer?
select 
    cust_id,
    avg(weight) as avg_wt
from 
    Shipment
group by cust_id
order by cust_id;

-- 5)   List the names and populations of cities that have received a shipment weighing over
-- 100 pounds.
select
    city_name,
    population
from   
    Shipment S inner join City C on (S.destination = C.city_name)
where
    weight > 100
group by city_name;

-- 6)   List cities that have received shipments from every customer.
select
    city_name
from   
    Shipment S inner join City C on (S.destination = C.city_name)
group by city_name
having count(distinct cust_id) =    (
                                        select 
                                            count(*) 
                                        from 
                                            Customer
                                    );

-- 7)   For each city, what is the maximum weight of a package sent to that city?
-- Left join cause we want to also show cities who don't have any shipment
select
    city_name, max(weight)
from
    City left join Shipment on destination = city_name  
group by city_name;

-- 8)   List the name and annual revenue of customers whose shipments have been delivered
-- by truck driver ‘IQBAL’.
select 
    cust_name, annual_revenue 
from
    Customer natural join Shipment natural join Truck
where
    driver_name = 'Iqbal'
group by (cust_name, annual_revenue); --group by done to remove dublicates

-- 9) List drivers who have delivered shipments to every city.
select 
    truck_no,
    driver_name
from 
    Shipment natural join Truck
group by truck_no, driver_name  --driver_name just cause I want to print
having count(distinct destination) =    (
                                            select
                                                count(*)
                                            from
                                                City
                                        );

-- 10) For each city, with population over 1 million, what is the minimum weight of a
-- package sent to that city.    
select
    city_name, min(weight)
from      
    Shipment, City 
where
    destination = city_name
group by city_name
having population > 1000000;                            