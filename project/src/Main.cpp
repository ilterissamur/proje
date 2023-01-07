#include <iostream>
#include "Array.h"
#include "Functions.h"
#include "Admin.h"

using namespace std;

int main()
{
    srand(time(NULL)); // For the generate random id numbers.

    ifstream myFile1;
    int size1, size2, size3, choice, budget, usingBudget;

    size1 = calculateDataSize("employee.txt", myFile1) - 1; // Assigning the sizes, according to the file's line numbers.
    size2 = calculateDataSize("refugee.txt", myFile1) - 1;
    size3 = calculateDataSize("guilty.txt", myFile1) - 1;
    Array myArray(size1, size2, size3); // Create Array's objects, and called the three arguments constructor.
    myArray.readArrayData();

    myFile1.open("budget.txt", ios::in); // Reading the budget informations, from the budget file.
    myFile1 >> budget;
    myFile1 >> usingBudget;
    myFile1.close();

    Person person; // Create Person class's object.
    Admin admin;   // Create Admin class's object.

    while (!admin.login())
    {
        system("cls");                                       // Cleaning the terminal.
        cout << "Invalid login, please login again" << endl; // Warning for invalid admin login.
    }

    system("cls");

    choice = displayMenu(); // According to the user's menu preferences, showing some operations.

    while (choice != 4)
    {
        if (choice == 1) // Adding new migrants.
        {
            system("cls");

            person.createPerson(); // Asking the person's informations.

            int control = person.filter(person); // According to the migrant's features, Classification the migrants.

            if (control == 3) // Migrants has a well-done personal point. He/She works on good job and has a good salary.
            {
                system("cls");

                cout << "Person point: " << person.getPoint() << ", "
                     << "Person takes A grade from job classification" << endl;
                cout << "\n";
                Employee employee(person);
                employee.findJob("A");         // Setting job to migrant.
                myArray.addEmployee(employee); // Migrants got a job, and joined the employee class.
                employee.addEmployeeFile();    // Adding Employee's file.
                budget += employee.getTax();   // After the calculate the taxes, their taxes added budget.

                system("cls");
            }
            else if (control == 2) // Migrants has a medium level personal point.
            {
                system("cls");

                cout << "Person point: " << person.getPoint() << ", "
                     << "Person takes B grade from job classification" << endl;
                cout << "\n";
                Employee employee(person);
                employee.findJob("B");         // Setting job to migrant.
                myArray.addEmployee(employee); // Migrants got a job, and joined the employee class.
                employee.addEmployeeFile();    // Adding Employee's file.
                budget += employee.getTax();   // After the calculate the taxes, their taxes added budget.

                system("cls");
            }
            else if (control == 1) // Migrants has a below average personal point.
            {
                system("cls");

                cout << "Person point: " << person.getPoint() << ", "
                     << "Person takes C grade from job classification" << endl;
                cout << "\n";
                Employee employee(person);
                employee.findJob("C");         // Setting job to migrant.
                myArray.addEmployee(employee); // Migrants got a job, and joined the employee class.
                employee.addEmployeeFile();    // Adding Employee's file.
                budget += employee.getTax();   // After the calculate the taxes, their taxes added budget.

                system("cls");
            }
            else if (control == -1) // If migrants cannot work for some problems( child or too old or insufficent personal point).
            {
                system("cls");

                cout << "Person's age is too young for working our country" << endl;
                if ((budget - usingBudget) / 1000 < 1) // There is no budget for the new refugee.
                {
                    cout << "WARNING: There is no bugdet to add refugee to camp. Add new employee or stop adding refugees" << endl;
                    break;
                }
                Refugee refugee(person);
                cout << "\nRemaining refugee capacity: " << int((budget - usingBudget) / 1000) << endl; // According to the budget and using budget, calcualte the capacity.
                refugee.setCamp();                                                                      // Setting the camp.
                myArray.addRefugee(refugee);                                                            // Migrants got a camp, and joined the refugee class.
                refugee.addRefugeeFile();                                                               // Adding Refugee's file.
                usingBudget += 1000;                                                                    // After adding new refugee, using budget increase by 1000.

                system("cls");
            }
            else if (control = -2)
            {
                system("cls");

                cout << "Person's age is too old for working our country" << endl;
                if ((budget - usingBudget) / 1000 < 1)
                {
                    cout << "There is no bugdet to add refugee to camp. Add new employee or stop adding refugees" << endl;
                    break;
                }
                Refugee refugee(person);
                cout << "\nRemaining refugee capacity: " << int((budget - usingBudget) / 1000) << endl; // According to the budget and using budget, calcualte the capacity.
                refugee.setCamp();                                                                      // Setting the camp.
                myArray.addRefugee(refugee);                                                            // Migrants got a camp, and joined the refugee class.
                refugee.addRefugeeFile();                                                               // Adding Refugee's file.
                usingBudget += 1000;                                                                    // After adding new refugee, using budget increase by 1000.

                system("cls");
            }
            else if (control == -3)
            {
                system("cls");

                cout << "Person point: " << person.getPoint() << ", "
                     << "Person's point is too low for working our country" << endl;
                if ((budget - usingBudget) / 1000 < 1)
                {
                    cout << "There is no bugdet to add refugee to camp. Add new employee or stop adding refugees" << endl;
                    break;
                }
                Refugee refugee(person);
                cout << "\nRemaining refugee capacity: " << int((budget - usingBudget) / 1000) << endl; // According to the budget and using budget, calcualte the capacity.
                refugee.setCamp();                                                                      // Setting the camp.
                myArray.addRefugee(refugee);                                                            // Migrants got a camp, and joined the refugee class.
                refugee.addRefugeeFile();                                                               // Adding Refugee's file.
                usingBudget += 1000;                                                                    // After adding new refugee, using budget increase by 1000.

                system("cls");
            }
        }
        else if (choice == 2) // Guilty Detection Operation.
        {
            system("cls");

            int type, index;
            string tempID;
            int employeeSize = myArray.getEmployeeSize();
            int refugeeSize = myArray.getRefugeeSize();

            cout << "1- Employee" << endl;
            cout << "2- Refugee" << endl;
            cout << "Choose migrant type: ";
            cin >> type;
            while (type < 1 || type > 2)
            {
                cout << "Invalid migrant type, please choose again: ";
                cin >> type;
            }
            system("cls");
            cout << "Enter the ID of the guilty: ";
            cin >> tempID;

            if (type == 1) // Guilty from Employee.
            {
                Guilty g1;
                index = g1.search(myArray.employeeArray, myArray.getEmployeeSize(), tempID); // Determine the index of the employee by search function.
                Guilty g2(myArray.employeeArray[index]);                                     // Call the Guilty constructor, and copy the information.
                g2.setCrime(type);                                                           // Set employee's crime.
                g2.setPunishment(type);                                                      // Set employee's punishment.
                g2.applyPunsihment(type, budget, usingBudget, myArray.employeeArray, myArray.refugeeArray, employeeSize, refugeeSize, index);
                myArray.addGuilty(g2); // Add employee's information to the guilty array.
                g2.addGuiltyFile();    // Add employee's information to the guilty's file .

                system("cls");
            }
            else if (type == 2) // Guilty from Refugee.
            {
                Guilty g1;
                index = g1.search(myArray.refugeeArray, myArray.getRefugeeSize(), tempID); // Determine the index of the refugee by search function.
                Guilty g2(myArray.refugeeArray[index]);                                    // Call the Guilty constructor, and copy the information.
                g2.setCrime(type);                                                         // Set refugee's crime.
                g2.setPunishment(type);                                                    // Set refugee's punishment.
                g2.applyPunsihment(type, budget, usingBudget, myArray.employeeArray, myArray.refugeeArray, employeeSize, refugeeSize, index);
                myArray.addGuilty(g2); // Add refugee's information to the guilty array.
                g2.addGuiltyFile();    // Add refugee's information to the guilty's file.

                system("cls");
            }

            myArray.setEmployeeSize(employeeSize);
            myArray.setRefugeeSize(refugeeSize);
        }
        else if (choice == 3) // Display Operation.
        {
            int selection;

            system("cls");

            cout << "1- Display Employees" << endl;
            cout << "2- Display Refugees" << endl;
            cout << "3- Display Guilties" << endl;
            cout << "Choose Display Mode: ";
            cin >> selection;
            while (selection < 1 || selection > 3) // Checking preferences.
            {
                cout << "Invalid choice, please choose again:";
                cin >> selection;
            }

            if (selection == 1) // Print All Employee's information.
            {
                system("cls");
                myArray.print("Employee");
            }
            else if (selection == 2) // Print All Refugee's' information.
            {
                system("cls");
                myArray.print("Refugee");
            }
            else // Print All Guiltie's information.
            {
                system("cls");
                myArray.print("Guilty");
            }
        }

        choice = displayMenu(); // Again showing the menu.
    }

    // Writing the budget informations to the file.
    ofstream myFile2;
    myFile2.open("budget.txt", ios::out);
    myFile2 << budget << endl;
    myFile2 << usingBudget;
    myFile2.close();
}