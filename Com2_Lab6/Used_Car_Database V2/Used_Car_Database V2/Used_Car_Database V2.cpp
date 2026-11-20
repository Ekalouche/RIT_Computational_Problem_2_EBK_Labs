///////////////////////////////////////////////////////////////////////////////
// This program implements a rudimentary used car database.  It reads a text
// file that contains the list of cars in the database.  Each line of the file
// represents a single vehicle where there are six fields: Make, Model, Year,
// Engine Type (ICE or EV), Fuel/Energy Capacity, and mileage efficiency.
// The user is allowed to query the database to see the list of vehicles that
// match their search criteria.
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include "GasVehicle.h"
#include "ElectricVehicle.h"

// Changed from Lab 5: Added this header to use a forward linked list.
// Previously, this header was not included.
#include <forward_list>

using namespace std;

int main()
{
    // The inventory file
    ifstream InFile;
    // The string for each line of the inventory file
    string Line;
    // The used car database as pointers to objects
#define DATABASE_SIZE (20)

    // Changed from Lab 5: Replaced the array with a forward linked list.
    // Previously was: Vehicle* Database[DATABASE_SIZE];
    forward_list<Vehicle*> Database;

    // Changed from Lab 5: Added an iterator to track the insertion position.
    // Previously, NumVehicles was used as the array index for insertion.
    forward_list<Vehicle*>::iterator LastVehicle = Database.before_begin();

    // Open the inventory file
    InFile.open("Inventory.txt");
    if (!InFile.is_open())
    {
        cout << "Error! Inventory file could not be opened." << endl;
        return -1;
    } // if()

    // Read the contents of the file one line at a time
    int NumVehicles = 0;
    while (getline(InFile, Line))
    {
        // Enforce the 20-vehicle database limit.
        if (NumVehicles >= DATABASE_SIZE)
        {
            cout << "Error! Inventory contains more than 20 vehicles." << endl;

            // Changed from Lab 5: Loop through the list and delete each car.
            // Previously was: for (int i = 0; i < NumVehicles; i++)
            // with: delete Database[i];
            for (Vehicle* Car : Database)
            {
                delete Car;
            }
            return -4;
        }

        // String stream for parsing words from the line
        istringstream Record(Line);
        // String to hold the parsed field
        string Field;
        // Strings to hold the individual fields
        string Make, Model, Year, EngineType, Capacity, Efficiency;

        // Get the strings from the line
        int FieldCount = 0;
        while (Record >> Field)
        {
            FieldCount++;
            switch (FieldCount)
            {
            case 1: { Make = Field; break; }
            case 2: { Model = Field; break; }
            case 3: { Year = Field; break; }
            case 4: { EngineType = Field; break; }
            case 5: { Capacity = Field; break; }
            case 6: { Efficiency = Field; break; }
            } // switch()
        } // while()

        if (FieldCount != 6)
        {
            cout << "Error! Inventory file is malformed." << endl;
            cout << Line << endl;

            // Changed from Lab 5: Loop through the list and delete each car.
            // Previously was: for (int i = 0; i < NumVehicles; i++)
            // with: delete Database[i];
            for (Vehicle* Car : Database)
            {
                delete Car;
            }
            return -2;
        } // if()

        // Depending on the propulsion type, instantiate a GasVehicle or
        // ElectricVehicle, populate the fields, and put it into the list.
        if (EngineType == "ICE")
        {
            // Instantiate a gas propulsion car object
            GasVehicle* Car = new GasVehicle;

            // Set the fields
            Car->SetMake(Make);
            Car->SetModel(Model);
            Car->SetYear(stoi(Year));
            Car->SetFuelCapacity(stod(Capacity));
            Car->SetEfficiency(stod(Efficiency));

            // Changed from Lab 5: Insert the gas car after LastVehicle,
            // then update LastVehicle to the newly inserted element.
            // Previously was: Database[NumVehicles] = Car;
            LastVehicle = Database.insert_after(LastVehicle, Car);
        } // if()
        else if (EngineType == "EV")
        {
            // Instantiate an electric propulsion car object
            ElectricVehicle* Car = new ElectricVehicle;

            // Set the fields
            Car->SetMake(Make);
            Car->SetModel(Model);
            Car->SetYear(stoi(Year));
            Car->SetEnergyCapacity(stod(Capacity));
            Car->SetEfficiency(stod(Efficiency));

            // Changed from Lab 5: Insert the electric car after LastVehicle,
            // then update LastVehicle to the newly inserted element.
            // Previously was: Database[NumVehicles] = Car;
            LastVehicle = Database.insert_after(LastVehicle, Car);
        } // if...if...else()
        else
        {
            cout << "Error! Unrecognized propulsion type." << endl;

            // Changed from Lab 5: Loop through the list and delete each car.
            // Previously was: for (int i = 0; i < NumVehicles; i++)
            // with: delete Database[i];
            for (Vehicle* Car : Database)
            {
                delete Car;
            }
            return -3;
        } // if...else()

        // Increment the running counter of the cars in the inventory
        NumVehicles++;
    } // while()

    InFile.close();

    bool ExitRequested = false;
    do {
        char Command;
        // Prompt the user for the program option (search by Make, Model, Year,
        // or exit the program)
        cout << "Enter Command (? for help) > ";
        if (!(cin >> Command))
        {
            break;
        }

        // Process the command
        switch (Command)
        {
        case '?': // Help screen
        {
            cout << " ? = Display Help" << endl;
            cout << " A = Search by Make" << endl;
            cout << " O = Search by model" << endl;
            cout << " Y = Search by Year" << endl;
            cout << " Q = Quit / Exit the program" << endl;
            break;
        } // Case '?'

        case 'a': case 'A': // Search by Make
        {
            // Prompt the user for the search criteria
            string DesiredMake;
            cout << "Enter Make > ";
            cin >> DesiredMake;

            // Search the database and print every matching entry.
            bool MatchFound = false;

            // Changed from Lab 5: Search each car in the forward linked list.
            // Previously was: for (int i = 0; i < NumVehicles; i++)
            // Every Database[i]-> below was replaced with Car->.
            for (Vehicle* Car : Database)
            {
                if (Car->GetMake() == DesiredMake)
                {
                    cout << Car->GetMake() << " "
                        << Car->GetModel() << " "
                        << Car->GetYear() << endl;
                    cout << Car->GetPropulsionInfo() << endl;
                    MatchFound = true;
                }
            }

            if (!MatchFound)
            {
                cout << "No matching vehicles found." << endl;
            }
            break;
        } // case 'a' or 'A'

        case 'o': case 'O': // Search by Model
        {
            // Prompt the user for the search criteria
            string DesiredModel;
            cout << "Enter Model > ";
            cin >> DesiredModel;

            // Search the database and print every matching entry.
            bool MatchFound = false;

            // Changed from Lab 5: Search each car in the forward linked list.
            // Previously was: for (int i = 0; i < NumVehicles; i++)
            // Every Database[i]-> below was replaced with Car->.
            for (Vehicle* Car : Database)
            {
                if (Car->GetModel() == DesiredModel)
                {
                    cout << Car->GetMake() << " "
                        << Car->GetModel() << " "
                        << Car->GetYear() << endl;
                    cout << Car->GetPropulsionInfo() << endl;
                    MatchFound = true;
                }
            }

            if (!MatchFound)
            {
                cout << "No matching vehicles found." << endl;
            }
            break;
        } // case 'o' or 'O'

        case 'y': case 'Y': // Search by Year
        {
            // Prompt the user for the search criteria
            int DesiredYear;
            cout << "Enter Year > ";
            if (!(cin >> DesiredYear))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a numeric year." << endl;
                break;
            }

            // Search the database and print every matching entry.
            bool MatchFound = false;

            // Changed from Lab 5: Search each car in the forward linked list.
            // Previously was: for (int i = 0; i < NumVehicles; i++)
            // Every Database[i]-> below was replaced with Car->.
            for (Vehicle* Car : Database)
            {
                if (Car->GetYear() == DesiredYear)
                {
                    cout << Car->GetMake() << " "
                        << Car->GetModel() << " "
                        << Car->GetYear() << endl;
                    cout << Car->GetPropulsionInfo() << endl;
                    MatchFound = true;
                }
            }

            if (!MatchFound)
            {
                cout << "No matching vehicles found." << endl;
            }
            break;
        } // case 'y' or 'Y'

        case 'q': case 'Q': // Exit the program
        {
            ExitRequested = true;
            break;
        } // case 'q' or 'Q'

        // "otherwise" is not needed, any other command is ignored
        } // switch()

    } while (!ExitRequested);

    // Release all objects created with new.

    // Changed from Lab 5: Loop through the list and delete each car.
    // Previously was: for (int i = 0; i < NumVehicles; i++)
    // with: delete Database[i];
    for (Vehicle* Car : Database)
    {
        delete Car;
    }

    // Program completed successfully
    return 0;
} // main()