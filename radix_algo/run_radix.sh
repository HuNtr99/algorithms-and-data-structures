#!/bin/bash

DATASETS="dataset_1000.csv dataset_3000.csv dataset_11000.csv dataset_39000.csv dataset_130000.csv dataset_450000.csv dataset_1000000.csv dataset_5000000.csv dataset_17000000.csv dataset_60000000.csv dataset_100000000.csv dataset_150000000.csv"

for f in $DATASETS; do
    echo "=============================="
    echo "Processing $f"

    # Edit filename in radix_sort_step.cpp and recompile
    sed -i '' "s/string filename = \".*\";/string filename = \"$f\";/" radix_sort_step.cpp
    g++ -O2 -o radix_sort_step radix_sort_step.cpp
    ./radix_sort_step

    # Edit filename in radix_sort.cpp and recompile
    sed -i '' "s/string filename = \".*\";/string filename = \"$f\";/" radix_sort.cpp
    g++ -O2 -o radix_sort radix_sort.cpp
    ./radix_sort

    echo ""
done