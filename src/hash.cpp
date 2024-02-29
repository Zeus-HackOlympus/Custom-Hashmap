/*
 * input data divided into 4 byte chunks
 * chunk is multiplied by constant value c
 * upper 32 bytes are extracted
 * shifted value is XORed with original chunk
 *
 */
#include "../include/hash.hpp"
#include <sched.h>

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
    unsigned int prime1 = 0x8E0487;
    unsigned int prime2 = 0x9F02A7;
    unsigned int prime3 = 0x8E04DD;
    unsigned int prime4 = 0x9F02C5;

    unsigned int* chunks = getChunks(text);
    int numChunks = numOfChunks(text);
    unsigned int hash = 9043;

    for (int i = 1; i < numChunks; i++) {
        unsigned int chunk = chunks[i];
        hash = ((hash << 5) + hash) + chunk;
        hash ^= prime1;
        hash = ((hash << 5) + hash) + chunk;
        hash ^= prime2;
        hash = ((hash << 5) + hash) + chunk;
        hash ^= prime3;
        hash = ((hash << 5) + hash) + chunk;
        hash ^= prime4;
    }

    return hash;
}
