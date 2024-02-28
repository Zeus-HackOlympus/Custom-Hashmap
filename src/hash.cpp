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

unsigned int hash_function(string text)
{
    unsigned int primes[] = { 0x859b35, 0x5c0939, 0x70f849, 0x6c40c7, 0x912515 };

    int sizePrimes = sizeof(primes) / sizeof(primes[0]);

    unsigned int* chunks = getChunks(text);
    int numChunks = numOfChunks(text);
    unsigned int hash = chunks[0];

    for (int i = 1; i < numChunks; i++) {
        unsigned int chunk = chunks[i];
        for (int i = 0; i < sizePrimes; i++) {
            hash = (hash * primes[i]) ^ chunk;
        }
    }
    return hash;
}
