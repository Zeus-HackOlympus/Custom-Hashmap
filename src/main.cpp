/*
CSE 310 Hash Function DIY Contest
Instructor: Yiran "Lawrence" Luo
Your name(s):
Your team alias:
*/

#include <cmath>
#include <iostream>
#include <string>
#include "xxhash64.h"
#include "../include/hashmap.hpp"
using namespace std;

int main(int argc, char* argv[])
{

    int k = 0;
    int n = 0;
    string texts[500];

    cin >> k;
    string line;
    getline(cin, line);

    while (getline(cin, line)) {
        texts[n] = line;
        n++;
    }

    cout << "num of inputs: " << n << endl;

    hashmap map = *new hashmap(n);

    // traverse through all the n inputs
    for (int i = 0; i < n; i++) {

        string data = texts[i];
        unsigned int hash = XXHash64::hash(data.c_str(), data.size(), 0);
        size_t index = hash % k;
        map.insert(index, data);
    }

    cout << "==== Printing the contents of the first 5 slots ====" << endl;
    for (int i = 0; i < 5; i++) {
        map.display(i);
    }

    cout << "==== Printing the slot lengths ====" << endl;
    float sum = 0;
    for (int i = 0; i < k; i++) {
        int length = map.getCollectionLength(i);
        sum += length;
        cout << "Slot " << i << ": " << length << endl;
    }

    cout << "==== Printing the standard variance =====" << endl;
    float N = k;
    float mean = sum / n;

    sum = 0;

    for (int i = 0; i < N; i++) {
        float x = (map.getCollectionLength(i) - mean);
        x = x * x;
        sum += x;
    }

    float variance = (1 / N) * sum;

    float std_dev = sqrt(variance);
    cout << std_dev << endl;

    return 0;
}
