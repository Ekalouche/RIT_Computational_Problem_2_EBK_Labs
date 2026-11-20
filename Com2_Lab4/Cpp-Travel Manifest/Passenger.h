#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>

using namespace std;

// Passenger class
class Passenger
{
private:
    // Store the name and cabin
    string FirstNameValue;
    string LastNameValue;
    string CabinNumberValue;

public:
    // Set the name and cabin (0 = success, 1 = error)
    int SetFirstName(string Val);
    int SetLastName(string Val);
    int SetCabinNumber(string Val);

    // Get the name and cabin together
    void GetInfo(string& FirstName, string& LastName,
        string& CabinNumber);
};

#endif
