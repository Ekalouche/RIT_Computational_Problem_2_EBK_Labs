#include <iostream>
#include <vector>
#include <forward_list>
#include "Module.h"

using namespace std;

// Largest value added to each container.
const int MaxValue = 100000000;

// Insert immediately after this item number.
const int InsertionPosition = 500000;

// Number of new values to insert.
const int NumInsertions = 20;

// Number of items to delete from the front.
const int NumDeletions = 100;

void TestVector(ofstream& OutFile)
{
    // Creates an empty vector.
    vector<double> Numbers;

    // Stores the starting and ending times.
    chrono::steady_clock::time_point Start, End;

    cout << "\nVECTOR" << endl;

    // Fill the vector with values from 0 through 100,000,000.
    Start = chrono::steady_clock::now();

    //Attempt to make it faster 
    // Makes enough space for all the values
    Numbers.reserve(MaxValue + 1 + NumInsertions);

    for (long int Value = 0; Value <= MaxValue; Value++)
    {
        Numbers.push_back(Value);
    }

    End = chrono::steady_clock::now();
    cout << "Populate: ";
    PrintTime(Start, End);

    // Write the populate time in the first column.
    OutFile << chrono::duration_cast<chrono::microseconds>(End - Start).count() << ",";

    // Insert 20 values after the 500,000th item.
    Start = chrono::steady_clock::now();

    for (long int Count = 0; Count < NumInsertions; Count++)
    {
        // Start at the beginning for each insertion.
        vector<double>::iterator Position = Numbers.begin();

        // Move to item 500,001.
        for (long int i = 0; i < InsertionPosition; i++)
        {
            Position++;
        }

        // Insert before item 500,001, which is after item 500,000.
        Numbers.insert(Position, Count + 1.0);
    }

    End = chrono::steady_clock::now();
    cout << "Insert 20 (total, including searches): ";
    PrintTime(Start, End);

    // Write the insertion time in the second column.
    OutFile << chrono::duration_cast<chrono::microseconds>(
        End - Start).count() << ",";

    // Delete the first item 100 separate times.
    Start = chrono::steady_clock::now();

    for (long int Count = 0; Count < NumDeletions; Count++)
    {
        Numbers.erase(Numbers.begin());
    }

    End = chrono::steady_clock::now();
    cout << "Delete first item 100 times (total): ";
    PrintTime(Start, End);

    // Write the deletion time in the third column and end the row.
    OutFile << chrono::duration_cast<chrono::microseconds>(End - Start).count() << endl;

    cout << "Check - first value: " << Numbers.front() << ", last value: " << Numbers.back() << ", items: " << Numbers.size() << endl;
}

void TestForwardList(ofstream& OutFile)
{
    // Creates an empty forward list.
    forward_list<double> Numbers;

    chrono::steady_clock::time_point Start, End;

    cout << "\nFORWARD_LIST" << endl;

    // Start before the first item so we can insert into an empty list.
    forward_list<double>::iterator LastNumber = Numbers.before_begin();

    // Fill the list with values from 0 through 100,000,000.
    Start = chrono::steady_clock::now();

    for (long int Value = 0; Value <= MaxValue; Value++)
    {
        LastNumber = Numbers.insert_after(LastNumber, Value);
    }

    End = chrono::steady_clock::now();
    cout << "Populate: ";
    PrintTime(Start, End);

    // Write the populate time in the first column.
    OutFile << chrono::duration_cast<chrono::microseconds>(End - Start).count() << ",";

    // Insert 20 values after the 500,000th item.
    Start = chrono::steady_clock::now();

    for (long int Count = 0; Count < NumInsertions; Count++)
    {
        // Start at the beginning for each insertion.
        forward_list<double>::iterator Position = Numbers.begin();

        // Move from item 1 to item 500,000.
        for (long int Item = 1; Item < InsertionPosition; Item++)
        {
            Position++;
        }

        Numbers.insert_after(Position, Count + 1.0);
    }

    End = chrono::steady_clock::now();
    cout << "Insert 20 (total, including searches): ";
    PrintTime(Start, End);

    // Write the insertion time in the second column.
    OutFile << chrono::duration_cast<chrono::microseconds>(End - Start).count() << ",";

    // Delete the first node 100 separate times.
    Start = chrono::steady_clock::now();

    for (long int Count = 0; Count < NumDeletions; Count++)
    {
        Numbers.pop_front();
    }

    End = chrono::steady_clock::now();
    cout << "Delete first item 100 times (total): ";
    PrintTime(Start, End);

    // Write the deletion time in the third column and end the row.
    OutFile << chrono::duration_cast<chrono::microseconds>(End - Start).count() << endl;

    cout << "Check - first value: " << Numbers.front() << ", last value: " << *LastNumber << endl;
}

void PrintTime(chrono::steady_clock::time_point Start,
    chrono::steady_clock::time_point End)
{
    cout << "Time (msec): " << chrono::duration_cast<chrono::milliseconds>(End - Start).count() << endl;

    cout << "Time (usec): " << chrono::duration_cast<chrono::microseconds>(End - Start).count() << endl;
}