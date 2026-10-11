// *********************************************************
// Program: radix_sort.cpp
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
#include <chrono>
#include "record.h"
#include "radix_core.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {

    // *dataset filenames in csv
    string filename = "dataset_1000.csv";

    // Override with command line argument if provided
    if (argc == 2) {
        filename = argv[1];
    } else if (argc != 1) {
        cerr << "Usage: radix_sort <dataset.csv>" << endl;
        return 1;
    }

    // Extract n from filename e.g. "dataset_1000.csv" -> "1000"
    size_t underscorePos = filename.find_last_of('_');
    size_t dotPos        = filename.find_last_of('.');
    string n = filename.substr(underscorePos + 1, dotPos - underscorePos - 1);

    // ---- Read input (NOT timed) ----
    vector<Record> data = readCSV(filename);
    if (data.empty()) {
        cerr << "Error: dataset is empty or could not be read." << endl;
        return 1;
    }
    cout << "Loaded " << data.size() << " records from " << filename << endl;

    // ---- Sort (TIMED) ----
    auto start = high_resolution_clock::now();
    radixSort(data);
    auto end = high_resolution_clock::now();

    double elapsedSeconds = duration_cast<duration<double>>(end - start).count();

    // ---- Write output (NOT timed) ----
    string outFilename = "radix_sorted_dataset_" + n + ".csv";
    writeCSV(outFilename, data);

    // ---- Print running time to console and log file ----
    cout << "Radix sort completed for n = " << n << endl;
    cout << "Running time: " << elapsedSeconds << " seconds" << endl;
    cout << "Sorted output written to: " << outFilename << endl;

    ofstream logFile("radix_sort_runtime_log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << "dataset_" << n << ".csv -> "
                << "Radix sort running time: " << elapsedSeconds << " seconds" << endl;
        logFile.close();
    }

    return 0;
}
