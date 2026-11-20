#ifndef MODULE_H
#define MODULE_H

#include <chrono>
#include <fstream>

// Runs the vector tests and writes their times.
void TestVector(std::ofstream& OutFile);

// Runs the forward list tests and writes their times.
void TestForwardList(std::ofstream& OutFile);

// Prints the times to the console.
void PrintTime(std::chrono::steady_clock::time_point Start,
    std::chrono::steady_clock::time_point End);

#endif // MODULE_H