// *********************************************************
// File: radix_core.h
// Description: LSD radix sort implementation using counting
//              sort as the stable sub-sort for each digit.
//              Processes from the rightmost (least significant)
//              digit toward the leftmost (most significant) digit.
//
//              IDs range from 1,000,000,000 to 9,999,999,999
//              -> 10 decimal digits -> 10 passes total
//              (digit place values: 1, 10, 100, ..., 1e9)
// *********************************************************
#ifndef RADIX_CORE_H
#define RADIX_CORE_H

#include <vector>
#include "record.h"

using namespace std;

const int NUM_DIGITS = 10;     // 10-digit integers
const int RADIX = 10;          // base 10 -> 10 buckets (0-9)

// One stable counting-sort pass on the digit at the given place value
// e.g. digitPlace = 1   -> sorts by units digit
//      digitPlace = 10  -> sorts by tens digit
//      digitPlace = 1e9 -> sorts by the leftmost (10th) digit
inline void countingSortByDigit(vector<Record>& arr, long long digitPlace) {
    int n = (int)arr.size();
    vector<Record> output(n);
    int count[RADIX] = {0};

    // Step 1: count occurrences of each digit (0-9)
    for (int i = 0; i < n; i++) {
        int digit = (int)((arr[i].id / digitPlace) % RADIX);
        count[digit]++;
    }

    // Step 2: convert counts into starting positions (prefix sum)
    for (int d = 1; d < RADIX; d++) {
        count[d] += count[d - 1];
    }

    // Step 3: place elements into output, traversing input from the
    // back to the front to preserve relative order (stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (int)((arr[i].id / digitPlace) % RADIX);
        count[digit]--;
        output[count[digit]] = arr[i];
    }

    // Step 4: copy back to original array
    arr = output;
}

// Full LSD radix sort: rightmost digit (units) first, leftmost digit last
inline void radixSort(vector<Record>& arr) {
    long long digitPlace = 1; // 1, 10, 100, ..., 1e9
    for (int pass = 0; pass < NUM_DIGITS; pass++) {
        countingSortByDigit(arr, digitPlace);
        digitPlace *= RADIX;
    }
}

#endif // RADIX_CORE_H
