#include <iostream>
#include "Module.h"

using namespace std;

// How many times to run both tests.
const int NumRuns = 100;

int main()
{
    // Open a separate output file for each container.
    ofstream VectorFile("ResultsVector.csv");
    ofstream ListFile("ResultsForwardList.csv");

    if (!VectorFile || !ListFile)
    {
        cout << "Could not open the results files." << endl;
        return 1;
    }

    for (long int Run = 1; Run <= NumRuns; Run++)
    {
        cout << "\n========== Run " << Run << " ==========" << endl;

        TestVector(VectorFile);
        TestForwardList(ListFile);
    }

    VectorFile.close();
    ListFile.close();

    if (!VectorFile || !ListFile)
    {
        cout << "An error occurred while saving the results." << endl;
        return 1;
    }

    cout << "\nResults saved to ResultsVector.csv" << " and ResultsForwardList.csv" << endl;

    return 0;
}