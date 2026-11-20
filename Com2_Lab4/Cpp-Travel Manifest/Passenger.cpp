#include "Passenger.h"

using namespace std;

int Passenger::SetFirstName(string Val)
{
    // Check each character in the name
    for (size_t i = 0; i < Val.length(); i += 1)
    {
        // Check that this character is not a space, tab, or line ending
        if (Val[i] != ' ' && Val[i] != '\t' &&
            Val[i] != '\r' && Val[i] != '\n')
        {
            // Save the name
            FirstNameValue = Val;
            return 0;
        }
    }

    // Reject the name if it is empty or only spaces, tabs, or line endings
    return 1;
}

int Passenger::SetLastName(string Val)
{
    // Check each character in the name
    for (size_t i = 0; i < Val.length(); i += 1)
    {
        // Check that this character is not a space, tab, or line ending
        if (Val[i] != ' ' && Val[i] != '\t' &&
            Val[i] != '\r' && Val[i] != '\n')
        {
            // Save the name
            LastNameValue = Val;
            return 0;
        }
    }

    // Reject the name if it is empty or only spaces, tabs, or line endings
    return 1;
}

int Passenger::SetCabinNumber(string Val)
{
    // Check that the cabin looks like P-123, C-123, or S-123
    if (Val.length() != 5)
    {
        return 1;
    }

    if (Val[0] != 'P' && Val[0] != 'C' && Val[0] != 'S')
    {
        return 1;
    }

    if (Val[1] != '-')
    {
        return 1;
    }

    // Check that the last three characters are numbers
    for (int i = 2; i < 5; i += 1)
    {
        if (Val[i] < '0' || Val[i] > '9')
        {
            return 1;
        }
    }

    CabinNumberValue = Val;
    return 0;
}

void Passenger::GetInfo(string& FirstName, string& LastName,
    string& CabinNumber)
{
    // Get the name and cabin
    FirstName = FirstNameValue;
    LastName = LastNameValue;
    CabinNumber = CabinNumberValue;
}
