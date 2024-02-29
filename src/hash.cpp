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
//     unsigned int primes[] = { 0x859b35, 0x5c0939, 0x70f849, 0x6c40c7, 0x912515 };
//
//     int sizePrimes = sizeof(primes) / sizeof(primes[0]);
//
//     unsigned int* chunks = getChunks(text);
//     int numChunks = numOfChunks(text);
//     unsigned int hash = 5011;
//
//     for (int i = 0; i < numChunks; i++) {
//         unsigned int chunk = chunks[i];
//         hash ^= primes[0];
//         hash += chunk;
//         hash += (hash << 7);
//         hash ^= (hash >> 6);
//     }
//     hash += (hash << 3);
//     hash ^= (hash >> 11);
//     hash += (hash << 15);
//     return hash;
// }

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
//         hash ^= prime1;
//         hash = (hash << 16);
//         hash ^= prime2;
//         hash += prime3;
//     }
//
//     return hash;
// }

unsigned int hash_function(string text)
{
    unsigned int* chunks = getChunks(text);
    int nchunks = numOfChunks(text);

    unsigned int key;

    for (unsigned int key : chunks) {
        key = (~key) + (key << 21); // key = (key << 21) - key - 1;
        key = key ^ (key >> 24);
        key = (key + (key << 3)) + (key << 8); // key * 265
        key = key ^ (key >> 14);
        key = (key + (key << 2)) + (key << 4); // key * 21
        key = key ^ (key >> 28);
        key = key + (key << 31);
    }
    return key;
}
