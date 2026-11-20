#include <iostream>
#include <string>
#include "Passenger.h"
#include "Manifest.h"

using namespace std;

int main()
{
    Manifest ship;
    // Keep the last passenger created
    Passenger current;
    string choice = "";

    // Keep showing the menu
    while (choice != "0")
    {
        cout << "\n1. Create passenger\n";
        cout << "2. Add current passenger\n";
        cout << "3. Remove current passenger\n";
        cout << "4. Print manifest\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        // Read the menu choice
        cin >> choice;
        if (!cin)
        {
            break;
        }

        if (choice == "1")
        {
            // Ask for single-word names and the cabin
            Passenger candidate;
            string first;
            string last;
            string cabin;
            // Clear the previous selection
            current = Passenger();

            cout << "First name: ";
            cin >> first;
            if (!cin)
            {
                break;
            }
            cout << "Last name: ";
            cin >> last;
            if (!cin)
            {
                break;
            }
            cout << "Cabin (example P-101): ";
            cin >> cabin;
            if (!cin)
            {
                break;
            }

            if (candidate.SetFirstName(first) != 0 ||
                candidate.SetLastName(last) != 0)
            {
                cout << "Invalid name. Names cannot be blank.\n";
            }
            else if (candidate.SetCabinNumber(cabin) != 0)
            {
                cout << "Invalid cabin. Use P, C, or S, a dash, "
                    << "and exactly three digits.\n";
            }
            else
            {
                // Save this passenger
                current = candidate;
                cout << "Passenger created. Choose 2 to add them.\n";
            }
        }
        else if (choice == "2")
        {
            // Add this passenger to the list
            int result = ship.AddPassenger(current);
            if (result == 0)
            {
                cout << "Passenger added.\n";
            }
            else if (result == 1)
            {
                cout << "Duplicate name. Passenger not added.\n";
            }
            else if (result == 3)
            {
                cout << "Manifest is full. Maximum 100 passengers.\n";
            }
            else
            {
                cout << "Create a valid passenger first.\n";
            }
        }
        else if (choice == "3")
        {
            // Remove this passenger from the list
            if (ship.RemovePassenger(current) == 0)
            {
                cout << "Passenger removed.\n";
            }
            else
            {
                cout << "Passenger not found.\n";
            }
        }
        else if (choice == "4")
        {
            ship.Print();
        }
        else if (choice != "0")
        {
            cout << "Invalid choice. Enter 0 through 4.\n";
        }
    }

    return 0;
}
