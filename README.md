# database-design-project-bid

This project involves creating a database using SQL for a fictional company that is growing and will like to transition from the paper style record keeping into keeping records in a database. I created a database that allows the business keep track of customers, orders, payments. The data base made it easy to track business inventory and help business run reports easier to see trends. Creating the database from scratch included defining busoness rules, creating an entity relationship diagram, primary key and integrity rules. C++ was then utilized for user input and populate database. 


## 1.	Introduction
  Bidex is an entrepreneur who has an interest in owning a car lot. Bidex just acquired a 15-acre land and is operating an impound there. This lot will store impounded vehicles, release the car to the registered owners or authorized personnel, and release the car to insurance once authorized by the owner. Also, this lot will auction cars that have not been picked up within 35 days of storing them. 

  Bidex has contracts will multiple tow truck companies that will help transport impounded cars. The business has a record of all the tow truck drivers that work for each tow truck company and the fees they are required to charge per tow.
  When a car is brought in by a tow truck driver, information such as make, model, color, vehicle identification number, location of tow, and reason for a tow are used to store the car in the system.  On the second day of storage, the business will send letters to the registered owner informing them of the location of their car and what they must do to get it out.

  Bidex car lot has employees that work in various departments, employees in the dispatch department send information about cars that need to be towed to the available tow truck driver, and the lot attendant deals with storing the cars in the lot at their designed location and also taking customers to their cars when necessary, security department makes sure the lot and its environment are safe while the customer service representatives attend to customers and attend to incoming calls. 

## 2.	Business Rules
  •	Discounts can be given to customers whose cars were stolen.
  •	All contracted companies are responsible for the maintenance of their trucks.
  •	Selling a car at the auction clears the fees owed.
  •	There are no refunds after payment. 
  •	Vehicles that weigh above 10000 pounds will be charged as heavy duty.
  •	Customers are responsible for paying the fees charged for the letter. 
  •	Checks should be sent to the owner of a car if it sells for more than the fees owed. 
  •	Drivers must upload pictures of extra services offered before their fees can be granted.
  •	Cars are prepped for auction after 30 days. 
  •	Make, model, color, year, VIN, and location towed from are required for a car to be checked in.
  •	The business provides tow trucks.
  •	Dispatcher decides if a customer needs a tow truck or a flatbed.
  •	Payments can be made online or in person. 
  
## 3.	Entity Relationship Diagram
![Entity Relationship Diagram](https://github.com/user-attachments/assets/406ca7eb-bb05-4967-994f-64a146d1ad83)

## 4.	 Entity Relationship Diagram (Expanded)
![Entity Relationship Diagram Expanded](https://github.com/user-attachments/assets/1cfc9436-419a-4cf6-b2b6-a5fd4be28a35)

## 5.	Primary Key Table
![Primary key table.](https://github.com/user-attachments/assets/8fa18c58-9f80-42da-86bf-f894c9ae833a)

## 6.	Integrity Rules
_Entity Integrity Rule_ – The primary key must exist, be unique, and cannot be null.
_Referential Integrity Rule_ – The foreign key may be null (if it isn’t part of the table’s primary key), but it must have a valid entry.
![integrity rule 1](https://github.com/user-attachments/assets/7487fc2e-631f-4d53-aa47-a71fb32ecf91)
![integrity rule 2](https://github.com/user-attachments/assets/71857330-9896-4c54-9ce1-1bb8e71278f8)

## 7.	Definition of Relationships Table
![relationship table](https://github.com/user-attachments/assets/bf9d27d4-5e71-4e19-8147-6734349c9360)

## 8.	SQL Statements used to create table
![image](https://github.com/user-attachments/assets/9d2f8705-745d-43f6-92df-952d2cc8fe3b)
![image](https://github.com/user-attachments/assets/b3a3f9c6-0c26-4b9f-8c24-2c4395f738b0)

## 9.	Primary Keys in SQL Statements – highlighted in orange.

## 10.	 Database Populated with Five Records per Table
```
insert into customers
values ('10', 'Mark Sterling', '9 Iroquois Road','5879654889'),
('11', 'Mark United', '995 Brown Court','5879659874'),
('12', 'John Tuchell', '9966 Longbranch Dr.','3175659874'),
('13', 'Mason Mount', '242 Southampton Ave.','3172584874'),
('14', 'Kai Harvetz', '252 Lilac Street.','3173256987');


insert into cars
values ('1LNHM81V87Y600143','25','Lincoln','Town Car','2007'),
('4A3AA46G11E035323','26','Mitsubishi','Galant','2001'),
('SAJWA1C78D8V38055','27','Toyota','Camry','2002'),
('SAJWA1C78D8V38055','28','Jaguar','XJ','2013'),
('5J6RM4850CL703159','29','Honda','CR V EX','2012');


insert into contracted_company
values ('Big Doug', 'Scott', '3 South St.'),
('First to Arrive', 'Gilbert','7971 South Division Drive'),
('Towing You','','9895 Saxon Dr.'),
('Hick','Tom','182 Catherine St.'),
('BJ Towing', 'Lee','182 Catherine St.');

insert into extra_services
values ('SAJWA1C78D8V38055', 'Off the road','50','Winch','Hick'),
('SAJWA1C78D8V38055','Extra time','30','','First to Arrive'),
('4A3AA46G11E035323','Cleanup','30','Cleaning','BJ Towing'),
('1LNHM81V87Y600143','Extra time','30','', 'Big Doug'),
('5J6RM4850CL703159', 'Off the road','50','Winch','Towing You');


insert into auction(auction_date,car_ID,auction_fees)
VALUES ('11/05/2022','25','2500'),
('11/11/2022','26','2000'),
('12/03/2022','27','1500'),
('11/15/2022','28','2500'),
('12/12/2022','29','3500');


insert into payment (receipt_ID, car_ID,customer_ID,payment_amount,payment_type)
VALUES ('1235','27','11','327','Cash'),
('1236','25','10','127','Cash'),
('1265','26','12','227','Credit Card'),
('1239','29','13','333','Cash'),
('1289','28','14','27','');
```

