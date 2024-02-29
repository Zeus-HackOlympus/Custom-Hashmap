/*
 * input data divided into 4 byte chunks
 * chunk is multiplied by constant value c
 * upper 32 bytes are extracted
 * shifted value is XORed with original chunk
 *
 */
#include "../include/hash.hpp"

using namespace std;

unsigned int hash_function(string text)
{
    unsigned int hash = 0;

    for (int i = 0; i < text.size(); i++) {
        hash += (int)text[i];

        hash += (hash << 12);
        hash ^= (hash >> 22);
        hash += (hash << 4);
        hash ^= (hash >> 9);
        hash += (hash << 10);
        hash += (hash << 7);
        hash ^= (hash >> 2);
        hash ^= (hash >> 12);

        /* Knuth's Multiplicative Method */
        hash = (hash >> 3) * 2654435761;
    }
    return hash;
}
