// *********************************************************
// File: record.h
// Description: Shared data structure and CSV I/O helpers
//              used by radix_sort_step.cpp and radix_sort.cpp
// *********************************************************
#ifndef RECORD_H
#define RECORD_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Each dataset row: a 10-digit unique positive integer + a 5-letter string
struct Record {
    long long id;   // e.g. 1000000038
    string str;     // e.g. "uoren"
};

// Read all records from a CSV file: "id,str" per line
inline vector<Record> readCSV(const string& filename) {
    vector<Record> data;
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Error: cannot open file " << filename << endl;
        return data;
    }

    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        // Strip \r for Windows line endings
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, str;

        if (getline(ss, idStr, ',') && getline(ss, str)) {
            // Strip \r from str too just in case
            if (!str.empty() && str.back() == '\r') str.pop_back();
            Record r;
            r.id = stoll(idStr);
            r.str = str;
            data.push_back(r);
        }
    }

    fin.close();
    return data;
}

// Write all records to a CSV file: "id,str" per line
inline void writeCSV(const string& filename, const vector<Record>& data) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cerr << "Error: cannot create file " << filename << endl;
        return;
    }

    for (const auto& r : data) {
        fout << r.id << "," << r.str << "\n";
    }

    fout.close();
}

#endif // RECORD_H
