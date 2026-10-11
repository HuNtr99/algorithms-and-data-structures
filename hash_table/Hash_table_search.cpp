// *********************************************************
// Program: dataset_generator.cpp
// Course: CCP6214 Algorithm Design and Analysis
// Lecture Class: TC3L
// Tutorial Class: T11L
// Trimester: 2610
// Member_1: 243UC245K6 | KOK CHUEN HOU | KOK.CHUEN.HOU@student.mmu.edu.my | 011 1984 8099
// Member_2: 242UC242WF | METHUM RANSIDU ARACHCHI PATHIRANA | ARACHCHI.PATHIRANA.METHUM@student.mmu.edu.my | +60 18 297 9375
// Member_3: 242UC2441D | ABDULLAH MOHAMED AHMED ABDULLA | Abdullah.Mohamed.Ahmed@student.mmu.edu.my | 966 57 280 2255
// Member_4: 243UC247PF | BASMALA MOHAMED ALI ELIMAM | BASMALA.MOHAMED.ALI@student.mmu.edu.my | 966 50 849 3218
// *********************************************************


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>
// Cache flush: ARM (Mac M4) vs Intel
#if defined(__aarch64__) || defined(__arm__)
    #define CACHE_FLUSH(ptr) __asm__ volatile("dc civac, %0" :: "r"(ptr) : "memory")
#else
    #include <emmintrin.h>
    #define CACHE_FLUSH(ptr) _mm_clflush(ptr)
#endif
using namespace std;

ifstream inputFile;
ofstream outputFile;

// Linked List Implementation
struct Node
{
    long long key;
    string value;
    Node *next;
};

class LinkedList
{

private:
    Node *firstNode;

public:
    LinkedList() { firstNode = nullptr; }
    ~LinkedList()
    {
        Node *current = firstNode;
        while (current != nullptr)
        {
            Node *next = current->next;
            delete current;
            current = next;
        }
    }

    void insertAtFront(long long key, string value)
    {

        Node *newNode = new Node();
        newNode->key = key;
        newNode->value = value;
        newNode->next = firstNode;
        firstNode = newNode;
    }

    void insertAtEnd(long long key, string value)
    {

        Node *newNode = new Node();
        newNode->key = key;
        newNode->value = value;
        newNode->next = NULL;
        if (firstNode == nullptr)
        {
            firstNode = newNode;
            return;
        }
        Node *lastNode = firstNode;
        while (lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }

        lastNode->next = newNode;
    }

    bool isListEmpty()
    {
        return firstNode == NULL;
    }

    // Finds whether the linked list has a node with a key that matches our target
    bool findTarget(long long target)
    {
        bool found = false;
        Node *ptr = firstNode;
        while (ptr != nullptr && !found)
        {
            if (ptr->key == target)
            {
                found = true;
            }
            else
                ptr = ptr->next;
        }
        return found;
    }

    // Returns the size of a linked list (how many nodes it has) (used in best & worst case)
    long long listSize()
    {
        long long size = 0;
        if (firstNode == nullptr)
            return size;
        else
        {
            Node *lastNode = firstNode;
            size = 1;
            while (lastNode->next != NULL)
            {
                lastNode = lastNode->next;
                size++;
            }
            return size;
        }
    }

    // Gets the first key in the linked list (used for finding best key)
    long long getFirstKey()
    {
        if (firstNode != nullptr)
        {
            return firstNode->key;
        }
        return -1;
    }

    // Gets the last key in the linked list (used for finding worst key)
    long long getLastKey()
    {
        long long lastKey;
        if (firstNode == nullptr)
            return -1;
        Node *lastNode = firstNode;
        while (lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }
        return lastNode->key;
    }

    // Returns the head node (used during cache cleaning)
    Node *getHead()
    {
        return firstNode;
    }
};

// Hash Table Implementation
class HashTable
{
    vector<LinkedList> table;
    long long numOfBuckets;

public:
    HashTable(long long totalBuckets)
    {
        this->numOfBuckets = totalBuckets;
        table.resize(numOfBuckets);
    }
    // Insert key,value into table
    void insert(long long key, string value)
    {
        table[hashFunc(key)].insertAtFront(key, value);
    };

    // Find target in table using key
    bool findTarget(long long key)
    {
        long long bucketIndex = hashFunc(key);
        return table[bucketIndex].findTarget(key);
    };

    // Hash key to get index where key,value should be stored
    long long hashFunc(long long key)
    {
        return key % table.size();
    }

    // Finds best case key to be searched (key at the beginning of shortest list in the table)
    long long bestCaseTarget()
    {
        long long shortestListSize = 999999999;
        long long bestBucket = -1;

        for (int i = 0; i < table.size(); i++)
        {
            long long currentSize = table[i].listSize();
            if (currentSize == 1)
                return table[i].getFirstKey();
            else if (currentSize < shortestListSize && currentSize != 0)
            {
                shortestListSize = currentSize;
                bestBucket = i;
            }
        }
        if (bestBucket != -1)
        {
            return table[bestBucket].getFirstKey();
        }
        return -1;
    }

    // Finds worst case key to be searched (key at the end of longest list in the table)
    long long worstCaseTarget()
    {
        long long longestListSize = 0;
        long long bucketNum = -1;
        for (int i = 0; i < table.size(); i++)

        {
            long long currentListSize = table[i].listSize();
            if (currentListSize > longestListSize)
            {
                longestListSize = currentListSize;
                bucketNum = i;
            }
        }
        if (bucketNum == -1)
            return -1;
        return table[bucketNum].getLastKey();
    }

// Returns hashed key to find bucket index and use it to find list in that index and flush it
    long long getHashedKey(long long key)
    {
        return hashFunc(key);
    }

// Returns the linked list found in a specific bucket index
    LinkedList &getListInBucket(long long index)
    {
        return table[index];
    }
};

//Helper Functions

// Is the number selected for table size prime?
bool isPrime(long long num)
{
    if (num > 1)
    {
        for (long long i = 2; i <= sqrt(num); i++)
        {
            if (num % i == 0) return false;
        }
        return true;
    }
    return false;
}

// Gets a bigger prime number for table size (to ensure the hash function is good)
long long BiggerPrime(long long numOfElements)
{
    long long biggerPrime = numOfElements * 1.3;
    while (!isPrime(biggerPrime))
    {
        biggerPrime++;
    }
    return biggerPrime;
}

// Once one search is done the cpu caches everything so subsequent searches would be faster to return it to a "cold" state we need to flush
void flushKeyFromCache(long long key, HashTable &ht)
{
    long long bucketIndex = ht.getHashedKey(key);

    LinkedList &list = ht.getListInBucket(bucketIndex);

    CACHE_FLUSH(&list);

    Node *current = list.getHead();
    while (current != nullptr)
    {
        Node *nextToFlush = current->next;
        CACHE_FLUSH(current);

        current = nextToFlush;
    }
}

chrono::duration<double> clearFlushOverhead(long long key, long long n, HashTable &ht) {

    auto controlStart = chrono::steady_clock::now();
for (int i = 0; i < n; i++) {
    flushKeyFromCache(key, ht); 
}
auto controlEnd = chrono::steady_clock::now();
 return chrono::duration<double>(controlEnd - controlStart);
}

int main(int argc, char* argv[])
{
    // num of buckets =  1.3 times the number of keys to be inserted then we take this number and find a prime number bigger than it
    long long n = 150000000; // number of elements in dataset

    // Override with command line argument if provided
    if (argc == 2) {
        n = stoll(argv[1]);
    } else if (argc != 1) {
        cerr << "Usage: hash_table_search <dataset_size>" << endl;
        return 1;
    }
    HashTable hashTable(BiggerPrime(n));
    string fileLine;
    double x = 0, y = 0, z = 0;
    chrono::duration<double> flushOverHead;
    long long keyToStore;
    string valueToStore;
    vector<long long> keyVector;
    // cout << "Enter number of elements in dataset: ";
    // cin >> n;

    // Open Dataset file
    inputFile.open("dataset_" + to_string(n) + ".csv");
    
    // Open Output file
    outputFile.open("hash_table_search_dataset" + to_string(n) + ".txt");

    while (getline(inputFile, fileLine))
    {
        if (fileLine.empty()) continue;
        if (!fileLine.empty() && fileLine.back() == '\r') fileLine.pop_back();
        size_t comma = fileLine.find(',');
        keyToStore   = stoll(fileLine.substr(0, comma));
        valueToStore = fileLine.substr(comma + 1);
        hashTable.insert(keyToStore, valueToStore);
        keyVector.push_back(keyToStore);
    }

    
    // Best Case Timing
    chrono::duration<double> bestDuration;
    long long bestKey = hashTable.bestCaseTarget();
    flushOverHead = clearFlushOverhead(bestKey,n,hashTable);
    auto bestTimeStart = chrono::steady_clock::now();
    for (int i = 0; i < n; i++)
    {
        flushKeyFromCache(bestKey, hashTable);
        hashTable.findTarget(bestKey);
    }
    auto bestTimeEnd = chrono::steady_clock::now();

    if((bestTimeEnd - bestTimeStart) > flushOverHead) {
     bestDuration = bestTimeEnd - bestTimeStart - flushOverHead;
    }
    else {
     bestDuration = bestTimeEnd - bestTimeStart;
    }
    x = bestDuration.count();


    // Average Case Timing
    auto start = chrono::steady_clock::now();

    for (auto key : keyVector)
    {
        hashTable.findTarget(key);
    }
    auto end = chrono::steady_clock::now();

    chrono::duration<double> duration = end - start;

    y = duration.count();

    
    // Worse Case Timing
    chrono::duration<double> worstDuration;
    long long worstKey = hashTable.worstCaseTarget();
        flushOverHead = clearFlushOverhead(worstKey,n,hashTable);
    auto worstTimeStart = chrono::steady_clock::now();
    for (int i = 0; i < n; i++)
    {
        flushKeyFromCache(worstKey, hashTable);
        hashTable.findTarget(worstKey);
    }
    auto worstTimeEnd = chrono::steady_clock::now();


    if((bestTimeEnd - bestTimeStart) > flushOverHead) {
     worstDuration = worstTimeEnd - worstTimeStart - flushOverHead;
    }
    else {
     worstDuration = worstTimeEnd - worstTimeStart;
    }

    z = worstDuration.count();

    // Total time for n searches in each case
    outputFile << "Best case time: " << fixed << setprecision(10) << x << " seconds" << endl;
    outputFile << "Average case time: " << fixed << setprecision(10) << y << " seconds" << endl;
    outputFile << "Worst case time: " << fixed << setprecision(10) << z << " seconds" << endl;

    cout << "Best case time: " << fixed << setprecision(10) << x << " seconds" << endl;
    cout << "Average case time: " << fixed << setprecision(10) << y << " seconds" << endl;
    cout << "Worst case time: " << fixed << setprecision(10) << z << " seconds" << endl;

    return 0;
}