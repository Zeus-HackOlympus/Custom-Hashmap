/*
 * input data divided into 4 byte chunks
 * chunk is multiplied by constant value c
 * upper 32 bytes are extracted
 * shifted value is XORed with original chunk
 *
 */
#include <iostream>
#include <string>
#include "../include/hash.hpp"

using namespace std;

int numOfChunks(string text)
{
    return (text.length() + 3) / 4;
}

unsigned int* getChunks(string input)
{
    int numChunks = numOfChunks(input);
    unsigned int* chunks = new unsigned int[numChunks];

    const char* data = input.c_str();

    int c = 0;
    while (*data != '\0') {
        unsigned chunk = 0;

        int i;
        for (i = 0; i < 4 && *data != '\0'; i++) {
            chunk = chunk << 8;
            chunk = chunk | *data;
            data++;
        }

        // if string size not in multiples of 4, add padding of null bytes
        while (i < 4) {
            chunk = chunk << 8;
            i++;
        }

        chunks[c] = chunk;
        c++;
    }
    return chunks;
}

unsigned int hash_function(string text)
{
    // inspired from murmur hash
    unsigned int hash = 0x13371337;
    unsigned int seed = 0xb00b5;
    unsigned int c1 = 0xdeadbeef; // 0xdeadbeef
    unsigned int m = 0xcafebabe; // 0xcafebabe;
    unsigned int lucky_number = 16;

    unsigned int* chunks = getChunks(text);
    int numChunks = numOfChunks(text);

    for (int i = 0; i < numChunks; i++) {
        unsigned int chunk = chunks[i];
        hash = hash * m;
        hash = hash >> lucky_number;
        hash = hash * chunk;
        hash = hash | seed;
    }

    return hash;
}
