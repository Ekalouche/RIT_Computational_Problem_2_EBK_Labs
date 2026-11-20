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

using namespace std;

int main()
{
    // The inventory file
    ifstream InFile;
    // The string for each line of the inventory file
    string Line;
    // The used car database as pointers to objects
#define DATABASE_SIZE (20)
    Vehicle* Database[DATABASE_SIZE];

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
        // Do not write past the end of the 20-vehicle array.
        if (NumVehicles >= DATABASE_SIZE)
        {
            cout << "Error! Inventory contains more than 20 vehicles." << endl;
            for (int i = 0; i < NumVehicles; i++)
            {
                delete Database[i];
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
            for (int i = 0; i < NumVehicles; i++)
            {
                delete Database[i];
            }
            return -2;
        } // if()

      // Depending on the propulsion type, instantiate a GasVehicle or ElectricVehicle,
      //   populate the fields, and put it into the database array
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

            // Insert the gas car into the database
            Database[NumVehicles] = Car;
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

            // Insert the electric car into the database
            Database[NumVehicles] = Car;
        } // if...if...else()
        else
        {
            cout << "Error! Unrecognized propulsion type." << endl;
            for (int i = 0; i < NumVehicles; i++)
            {
                delete Database[i];
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
        // Prompt the user for the program option (search by Make, Model, Year, or
        //   or exit the program)
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
            for (int i = 0; i < NumVehicles; i++)
            {
                if (Database[i]->GetMake() == DesiredMake)
                {
                    cout << Database[i]->GetMake() << " "
                        << Database[i]->GetModel() << " "
                        << Database[i]->GetYear() << endl;
                    cout << Database[i]->GetPropulsionInfo() << endl;
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
            for (int i = 0; i < NumVehicles; i++)
            {
                if (Database[i]->GetModel() == DesiredModel)
                {
                    cout << Database[i]->GetMake() << " "
                        << Database[i]->GetModel() << " "
                        << Database[i]->GetYear() << endl;
                    cout << Database[i]->GetPropulsionInfo() << endl;
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
            for (int i = 0; i < NumVehicles; i++)
            {
                if (Database[i]->GetYear() == DesiredYear)
                {
                    cout << Database[i]->GetMake() << " "
                        << Database[i]->GetModel() << " "
                        << Database[i]->GetYear() << endl;
                    cout << Database[i]->GetPropulsionInfo() << endl;
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
    for (int i = 0; i < NumVehicles; i++)
    {
        delete Database[i];
    }

    // Program completed successfully
    return 0;
} // main()
