// *********************************************************
// Program: radix_sort_step.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC4L
// Tutorial Class: T13L
// Trimester: 2610
// Member_1: ID | NAME | EMAIL | PHONE
// Member_2: ID | NAME | EMAIL | PHONE
// Member_3: ID | NAME | EMAIL | PHONE
// Member_4: ID | NAME | EMAIL | PHONE
// *********************************************************
// Task Distribution
// Member_1:
// Member_2: radix_sort_step, radix_sort, radix sort report section
// Member_3:
// Member_4:
// *********************************************************

#include <iostream>
#include <fstream>
#include <string>
#include "record.h"
#include "radix_core.h"

using namespace std;

void writeStep(ofstream& fout, const vector<Record>& arr,
               int startRow, int endRow, const string& label) {
    string line = "[";
    for (int i = startRow; i <= endRow; i++) {
        line += to_string(arr[i - 1].id) + "/" + arr[i - 1].str;
        if (i != endRow) line += ", ";
    }
    line += "] " + label;
    cout << line << "\n";   // print to console
    fout << line << "\n";   // print to file
}

int main(int argc, char* argv[]) {

    // *dataset_n.csv
    string filename = "dataset_1000.csv";
    // *start row
    int startRow = 1;
    // *end row
    int endRow   = 7;

    // Override with command line arguments if provided
    if (argc == 4) {
        filename = argv[1];
        startRow = stoi(argv[2]);
        endRow   = stoi(argv[3]);
    } else if (argc != 1) {
        cerr << "Usage: radix_sort_step <dataset.csv> <start_row> <end_row>" << endl;
        return 1;
    }

    // Extract n from filename e.g. "dataset_1000.csv" -> "1000"
    size_t underscorePos = filename.find_last_of('_');
    size_t dotPos        = filename.find_last_of('.');
    string n = filename.substr(underscorePos + 1, dotPos - underscorePos - 1);

    // ---- Read input ----
    vector<Record> data = readCSV(filename);
    if (data.empty()) {
        cerr << "Error: dataset is empty or could not be read." << endl;
        return 1;
    }

    if (startRow < 1 || endRow > (int)data.size() || startRow > endRow) {
        cerr << "Error: invalid startRow/endRow for dataset of size "
             << data.size() << endl;
        return 1;
    }

    // Build output filename
    string outFilename = "dataset_" + n + "_radix_sorted_step_"
                       + to_string(startRow) + "_" + to_string(endRow) + ".txt";

    ofstream fout(outFilename);
    if (!fout.is_open()) {
        cerr << "Error: cannot create output file " << outFilename << endl;
        return 1;
    }

    // Print original state
    writeStep(fout, data, startRow, endRow, "original");

    // Radix sort pass by pass, print after each digit
    long long digitPlace = 1;
    for (int pass = 0; pass < NUM_DIGITS; pass++) {
        countingSortByDigit(data, digitPlace);
        int dLabel = NUM_DIGITS - pass; // d=10 down to d=1
        writeStep(fout, data, startRow, endRow, "d=" + to_string(dLabel));
        digitPlace *= RADIX;
    }

    fout.close();

    cout << "\nOutput written to: " << outFilename << endl;

    return 0;
}
