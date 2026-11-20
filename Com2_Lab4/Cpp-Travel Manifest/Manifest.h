#ifndef MANIFEST_H
#define MANIFEST_H

#include "Passenger.h"

using namespace std;

class Manifest
{
private:
    // Array that holds up to 100 passengers
    Passenger Passengers[100];
    // Passenger counts
    int Count;
    int PortCount;
    int CenterCount;
    int StarboardCount;

    // Update the passenger counts
    void UpdateCounts();

public:
    // Start the list
    Manifest();

    // Add passenger (0 = success, 1 = duplicate name, 2 = invalid passenger, 3 = full)
    int AddPassenger(Passenger ThePassenger);
    // Remove passenger (0 = success, 1 = passenger not found)
    int RemovePassenger(Passenger ThePassenger);

    // Show the passengers and counts
    void Print(void);
};

#endif
