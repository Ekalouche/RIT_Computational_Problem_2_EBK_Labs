#include <iostream>
#include "Manifest.h"

using namespace std;

// Start with an empty list and zero counts
Manifest::Manifest()
{
    Count = 0;
    PortCount = 0;
    CenterCount = 0;
    StarboardCount = 0;
}

int Manifest::AddPassenger(Passenger ThePassenger)
{
    string first;
    string last;
    string cabin;
    ThePassenger.GetInfo(first, last, cabin);

    // Check if any information is missing
    if (first == "" || last == "" || cabin == "")
    {
        return 2;
    }

    // Look for the same first and last name
    for (int i = 0; i < Count; i += 1)
    {
        string oldFirst;
        string oldLast;
        string oldCabin;
        Passengers[i].GetInfo(oldFirst, oldLast, oldCabin);
        if (first == oldFirst && last == oldLast)
        {
            return 1;
        }
    }

    // Check if the array is full
    if (Count >= 100)
    {
        return 3;
    }

    // Put the new passenger in the next empty spot
    Passengers[Count] = ThePassenger;
    Count += 1;
    UpdateCounts();
    return 0;
}

int Manifest::RemovePassenger(Passenger ThePassenger)
{
    string first;
    string last;
    string cabin;
    ThePassenger.GetInfo(first, last, cabin);

    // Look for the same first and last name
    for (int i = 0; i < Count; i += 1)
    {
        string oldFirst;
        string oldLast;
        string oldCabin;
        Passengers[i].GetInfo(oldFirst, oldLast, oldCabin);

        if (first == oldFirst && last == oldLast)
        {
            // Move passengers left to fill the empty spot
            for (int j = i; j < Count - 1; j += 1)
            {
                Passengers[j] = Passengers[j + 1];
            }

            Count -= 1;
            Passengers[Count] = Passenger();
            UpdateCounts();
            return 0;
        }
    }

    return 1;
}

// Count the passengers on each side
void Manifest::UpdateCounts()
{
    PortCount = 0;
    CenterCount = 0;
    StarboardCount = 0;

    for (int i = 0; i < Count; i += 1)
    {
        string first;
        string last;
        string cabin;
        Passengers[i].GetInfo(first, last, cabin);
        if (cabin[0] == 'P')
        {
            PortCount += 1;
        }
        else if (cabin[0] == 'C')
        {
            CenterCount += 1;
        }
        else
        {
            StarboardCount += 1;
        }
    }
}

// Show the passengers and counts
void Manifest::Print(void)
{
    cout << "\n========== TRAVEL MANIFEST ==========\n";

    if (Count == 0)
    {
        cout << "No passengers.\n";
    }

    for (int i = 0; i < Count; i += 1)
    {
        string first;
        string last;
        string cabin;
        Passengers[i].GetInfo(first, last, cabin);

        // Show one passenger
        cout << "\nPassenger " << i + 1 << "\n";
        cout << "First name: " << first << "\n";
        cout << "Last name: " << last << "\n";
        cout << "Cabin: " << cabin << "\n";
    }

    // Show the passenger counts
    cout << "\nTotal passengers: " << Count << "\n";
    cout << "Port passengers: " << PortCount << "\n";
    cout << "Center passengers: " << CenterCount << "\n";
    cout << "Starboard passengers: " << StarboardCount << "\n";
}
