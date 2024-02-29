/*
 * input data divided into 4 byte chunks
 * chunk is multiplied by constant value c
 * upper 32 bytes are extracted
 * shifted value is XORed with original chunk
 *
 */
#include "../include/hash.hpp"

#define CHUNK_LENGTH 4

using namespace std;

int numOfChunks(string text)
{
    return (text.length() + 3) / CHUNK_LENGTH;
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
        for (i = 0; i < CHUNK_LENGTH && *data != '\0'; i++) {
            chunk = chunk << 8;
            chunk = chunk | *data;
            data++;
        }

        // if string size not in multiples of 4, add padding of null bytes
        while (i < CHUNK_LENGTH) {
            chunk = chunk << 8;
            i++;
        }

        chunks[c] = chunk;
        c++;
    }
    return chunks;
}


// unsigned int hash_function(string text)
// {
//
//     unsigned int prime1 = 0x859b35;
//     unsigned int prime2 = 0x5c0939;
//     unsigned int prime3 = 0x70f849;
//     unsigned int prime4 = 0x6c40c7;
//
//     const char* str = text.c_str();
//     unsigned long hash = 0;
//     int c;
//
//     while ((c = *str++)) {
//         hash = hash + (c << 6);
//         hash = (hash << 16);
//     }
//
//     return hash;
// }

// wang hash
// unsigned int hash_function(string text)
// {
//     unsigned int hash = 0;
//
//     for (char c : text) {
//         hash = hash << 8;
//         hash |= (int)c;
//     }
//
//     hash = (~hash) + (hash << 21); // hash = (hash << 21) - hash - 1;
//     hash = hash ^ (hash >> 24);
//     hash = (hash + (hash << 3)) + (hash << 8); // hash * 265
//     hash = hash ^ (hash >> 14);
//     hash = (hash + (hash << 2)) + (hash << 4); // hash * 21
//     hash = hash ^ (hash >> 28);
//     hash = hash + (hash << 31);
//     return hash;
// }
