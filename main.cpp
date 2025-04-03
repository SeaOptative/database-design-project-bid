/* Program name: Final Programming Project.cpp
*  Author: Emmanuel Adebanjo
*  Date last updated: 12/12/2022
* Purpose: Database for Bidex car lot
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <climits>
#include <ctime>
#include <cctype>
#include <regex>
#include "sqlite3.h"

using namespace std;

void printMainMenu();
void viewCars(sqlite3 *);
void viewCustomers(sqlite3 *);
void addCars(sqlite3 *);
void deleteCars(sqlite3 *);
void addCustomer(sqlite3*);
void UpdateCompany(sqlite3 *);
int rollback(sqlite3 *, string);
int commit(sqlite3 *);
int beginTransaction(sqlite3 *);
int mainMenu();

int main() {
  int choice;


  sqlite3 *mydb;

  int rc;

  rc = sqlite3_open_v2("BidexLot.db", &mydb, SQLITE_OPEN_READWRITE, NULL);
  if (rc != SQLITE_OK) 
  {
        // Displays when the database cannot be opened.
    cout << "Couldn't open database for Bidex Lot: " << sqlite3_errmsg(mydb);
    return 1;
  }
  cout << "--------------------------------" << endl;
  cout << "Welcome to Bidex Car Lot Database" << endl;
  choice = mainMenu();
  while (true)
   {
    switch (choice) {
    case 1:
      viewCars(mydb);
      break;
    case 2:
      viewCustomers(mydb);
      break;
	case 3:
      addCars(mydb);
      break;
    case 4:
      addCustomer(mydb);
      break;
    case 5:
     deleteCars(mydb);
      break;
    case 6:
     UpdateCompany(mydb);
      break;
    case -1: {
      sqlite3_close(mydb);
      return 0;
    }
    default:
      cout << "That is not a valid choice." << endl;
	  cout << "Please enter a valid choice." << endl;
    }
    cout << "\n\n";
    choice = mainMenu();
  }
}
// Printing out the main menu
void printMainMenu()
{
    cout<< "*****Main Menu*****"<< endl;
    cout << "Please choose an option (enter -1 to quit):  " << endl;
    cout << "1. View all the cars" << endl;
    cout << "2. View Customer Information" << endl;
    cout << "3. Add a car" << endl;
    cout << "4. Add a Customer" << endl;
    cout << "5. Delete a Car" << endl;
    cout << "6. Update a contracted company" << endl;
    cout << "Enter Choice: ";
}
int mainMenu()
{
    int choice = 0;

    printMainMenu();
    cin >> choice;
    while ((!cin || choice < 1 || choice > 6) && choice != -1)
    {
        if (!cin)
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        // Displays this message if the inputs an invalid choice from the menu
        cout << "That is not a valid choice." << endl
             << endl;
        printMainMenu();
        cin >> choice;
    }
    return choice;
}



void viewCars(sqlite3 *db)
{

    string veh_VIN,veh_MAKE,veh_MODEL,Veh_ID, veh_YEAR; 

    
    string query = "SELECT car_Make|| \" - \" ||car_Model AS 'VEHICLE', car_ID FROM cars ORDER BY car_ID ASC";
    sqlite3_stmt *firstStatement;

if (sqlite3_prepare_v2(db, query.c_str(), -1, &firstStatement, NULL) != SQLITE_OK)
    {
        // When an error occurs preparing the first statement...
        string err = sqlite3_errmsg(db);
        sqlite3_finalize(firstStatement);
        cout << "There was an error: " << err << endl;
        return;
    }
    else
    {
        cout << "Please choose the car you want to see:\n";
        int choice;
        int i = 1;

        while (sqlite3_step(firstStatement) == SQLITE_ROW)
        {
            // print first query results.
            cout << i++ << ". " << sqlite3_column_text(firstStatement, 0) << endl;
        }

        // get input and test for improper values.
        while (!(cin >> choice) || (choice > (i - 1)) || choice < 1)
        {
            if (!cin)
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }

            cout << "That is not a valid choice! Try again!" << endl;
        }
        // reset the statement and iterate to the choice.
        sqlite3_reset(firstStatement);
        for (int i = 0; i < choice; i++)
        {
            sqlite3_step(firstStatement);
        }
        // retrieve our car id, then craft our new query and prepare our next statement.
        Veh_ID = reinterpret_cast<const char *>(sqlite3_column_text(firstStatement, 1));
        sqlite3_finalize(firstStatement);

        string query2 = "SELECT * FROM cars WHERE car_ID = ";
        query2 += Veh_ID += ";";
        sqlite3_stmt *secondStatement;
        if (sqlite3_prepare_v2(db, query2.c_str(), -1, &secondStatement, NULL) != SQLITE_OK)
        {
            // When an error occurs preparing the second statement...
            string err = sqlite3_errmsg(db);
            sqlite3_finalize(secondStatement);
            cout << "There was an error: " << err << endl;
            return;
        }
        else
        {
            // Since we have verified programatically that we should have a result here,
            // we step once without checking that it is valid.
            sqlite3_step(secondStatement);
            veh_VIN = reinterpret_cast<const char *>(sqlite3_column_text(secondStatement, 0));
            veh_MAKE = reinterpret_cast<const char *>(sqlite3_column_text(secondStatement, 2));
            veh_MODEL = reinterpret_cast<const char *>(sqlite3_column_text(secondStatement, 3));
            veh_YEAR = reinterpret_cast<const char *>(sqlite3_column_text(secondStatement, 4));
            sqlite3_finalize(secondStatement);

            cout << "----Car Information----\n";
            cout << "VIN: " << veh_VIN;
            cout << "\nMake: "<< veh_MAKE;
            cout << "\nModel: " << veh_MODEL;
             cout << "\nYear: " << veh_YEAR;
             return;
        }
    }
}

void viewCustomers(sqlite3 *db)
{

    string cusID, cusName, phoneNum, cusAddress;

    string query = "SELECT customer_ID || \" - \" || customer_name AS 'CUSTOMER', customer_ID FROM customers ORDER BY customer_ID ASC";
    sqlite3_stmt *firstStatement;

if (sqlite3_prepare_v2(db, query.c_str(), -1, &firstStatement, NULL) != SQLITE_OK)
    {
        // When an error occurs preparing the first statement...
        string err = sqlite3_errmsg(db);
        sqlite3_finalize(firstStatement);
        cout << "There was an error: " << err << endl;
        return;
    }
    else
    {
        cout << "Please choose the customer you want to see:\n";
        int choice;
        int i = 1;

        while (sqlite3_step(firstStatement) == SQLITE_ROW)
        {
            // print first query results.
            cout << i++ << ". " << sqlite3_column_text(firstStatement, 0) << endl;
        }

        // get input and test for improper values.
        while (!(cin >> choice) || (choice > (i - 1)) || choice < 1)
        {
            if (!cin)
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }

            cout << "That is not a valid choice! Try again!" << endl;
        }
        // reset the statement and iterate to the choice.
        sqlite3_reset(firstStatement);
        for (int i = 0; i < choice; i++)
        {
            sqlite3_step(firstStatement);
        }
        // retrieve our customer id, then craft our new query and prepare our next statement.
        cusID = reinterpret_cast<const char *>(sqlite3_column_text(firstStatement, 1));
        sqlite3_finalize(firstStatement);

        string query2 = "SELECT * FROM customers WHERE customer_ID = ";
        query2 += cusID += ";";
        sqlite3_stmt *secondStatement;
        if (sqlite3_prepare_v2(db, query2.c_str(), -1, &secondStatement, NULL) != SQLITE_OK)
        {
            // When an error occurs preparing the second statement...
            string err = sqlite3_errmsg(db);
            sqlite3_finalize(secondStatement);
            cout << "There was an error: " << err << endl;
            return;
        }
        else
        {
            // Since we have verified programatically that we should have a result here,
            // we step once without checking that it is valid.
            sqlite3_step(secondStatement);
            cusName = reinterpret_cast<const char *>(sqlite3_column_text(secondStatement, 1));
            cusAddress = reinterpret_cast<const char *>(sqlite3_column_text(secondStatement, 2));
            phoneNum = reinterpret_cast<const char *>(sqlite3_column_text(secondStatement, 3));

            sqlite3_finalize(secondStatement);

            cout << "----Customer Information----\n";
            cout << "Name: " << cusName;
            cout << "\nPhone Number: "<< phoneNum;
            cout << "\nAddress: " << cusAddress;
             return;
        }
    }
}

void addCustomer(sqlite3* db)
{
    string FullName, phone, CustoAddrss;
    char initial, yn;
    bool i = false, a = false;
    cout << "Enter the customer's name: "<< endl;
    cout << " Enter the first name & the last name seperated by a space. ";
    getline(cin>>ws,FullName);

    cout << "Enter the customer's address: ";
    getline(cin>>ws, CustoAddrss);

    cout << "Enter the 10 digits of the phone number (in the format xxx-xxx-xxxx): ";
    getline(cin >> ws , phone);
    regex r{"\\d{3}-\\d{3}-\\d{4}"};
    while(!regex_match(phone, r))
    {
        cout << "The customer's phone number is not in the correct format." << endl;
        cout << "Enter the 10 digits of the phone number (in the format xxx-xxx-xxxx): ";
        getline(cin >> ws , phone);
    }
    string query = "insert into customers (customer_name, address, phone_number";
     query +=") values ('";
    query += FullName + "', '";
    query += CustoAddrss + "', '";
    query += phone + "'";
     query += ");";
    cout << query << endl;
    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);

    if (rc != SQLITE_OK)
    {
        rollback(db, query);
        return;
    }
    int customer_ID = sqlite3_last_insert_rowid(db);
    cout << "Successfully inserted customer's information " << customer_ID << endl;

}

void addCars(sqlite3* db)
{
    string vehVIN, vehMake, vehModel, vehYear;

    cout << "Enter the 17 digits car VIN : ";
    getline(cin >> ws , vehVIN);
    
    cout << "Enter the car's make: ";
    getline(cin>>ws, vehMake);

    cout << "Enter the car's model: ";
    getline(cin>>ws, vehModel);

    cout << "Enter the car's Year: ";
    getline(cin>>ws, vehYear);

string query = "insert into cars (car_VIN, car_Make, car_Model, car_Year";
    
query +=") values ('";
    query += vehVIN + "', '";
    query += vehMake + "', '";
    query += vehModel + "', '";
     query += vehYear + "'";
     query += ");";
    cout << query << endl;

int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);

    if (rc != SQLITE_OK)
    {
        rollback(db, query);
        return;
    }
    int car_ID = sqlite3_last_insert_rowid(db);
    cout << "Successfully inserted car " << car_ID << endl;


}

void deleteCars(sqlite3 * db)
{
    string veh_ID ;

    cout << "Enter the car's ID you'd like to delete: ";
    getline(cin>>ws, veh_ID);

string query = "Delete from cars (car_ID";
query +=") values ('";
    query += veh_ID + "', '";
     query += ");";
    cout << query << endl;

     int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);

    if (rc != SQLITE_OK)
    {
        rollback(db, query);
        return;
    }
    cout << "Successfully deleted car " << veh_ID<< endl;

}

void UpdateCompany(sqlite3 * db)
{
    
    string comName, comDriver, comAddress;

    cout << "Enter Company name you would like to update : ";
    getline(cin >> ws , comName);
    
    cout << "Enter the drivers name: ";
    getline(cin>>ws, comDriver);

    cout << "Enter the companys address: ";
    getline(cin>>ws, comAddress);

string query = "insert into contracted_company  (company_name, drivers,company_address";
    
query +=") values ('";
    query += comName + "', '";
    query += comDriver + "', '";
    query += comAddress + "'";
     query += ");";
    cout << query << endl;

int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);

    if (rc != SQLITE_OK)
    {
        rollback(db, query);
        return;
    }
    int car_ID = sqlite3_last_insert_rowid(db);
    cout << "Successfully inserted company " << comName << endl;


}

int rollback(sqlite3 *db, string query)
{

    string error = sqlite3_errmsg(db);
    // sqlite3_finalize(result);
    cout << "There was an error: " << error << endl;
    cout << query << endl;
    char *err;
    string query1 = "rollback";
    int rc = sqlite3_exec(db, query1.c_str(), NULL, NULL, &err);
    if (rc != SQLITE_OK)
    {
        cout << "There was an error on rollback: " << err << endl;
        sqlite3_free(err);
    }
    return rc;
}

int commit(sqlite3 *db)
{
    char *err;
    string query = "commit";
    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
    if (rc != SQLITE_OK)
    {
        cout << "There was an error on commit: " << err << endl;
        sqlite3_free(err);
    }
    return rc;
}


int beginTransaction(sqlite3 *db)
{
    char *err;
    string query = "begin transaction";
    int rc = sqlite3_exec(db, query.c_str(), NULL, NULL, &err);
    if (rc != SQLITE_OK)
    {
        cout << "There was an error on begin transaction: " << err << endl;
        sqlite3_free(err);
    }
    return rc;
}