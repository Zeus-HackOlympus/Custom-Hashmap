#include "../include/hash.hpp"

using namespace std;

unsigned int hash_function(string text)
{
    const unsigned int prime_modulo = 101;
    unsigned int hash = 121;

    for (char c : text) {
        hash = (hash * 3) + c;

        hash = (hash + 0x7ed55d16) + (hash << 12);
        hash = (hash ^ 0xc761c23c) ^ (hash >> 19);
        hash = (hash + 0x165667b1) + (hash << 5);
        hash = (hash + 0xd3a2646c) ^ (hash << 9);
        hash = (hash + 0xfd7046c5) + (hash << 3);
        hash = (hash ^ 0xb55a4f09) ^ (hash >> 16);

        hash = (hash + 0x7ed55d16) + (hash << 12);
        hash = (hash ^ 0xc761c23c) ^ (hash >> 19);
        hash = (hash + 0x165667b1) + (hash << 5);
        hash = (hash + 0xd3a2646c) ^ (hash << 9);
        hash = (hash + 0xfd7046c5) + (hash << 3);
        hash = (hash ^ 0xb55a4f09) ^ (hash >> 16);
    }

    return hash % prime_modulo; // Take modulo to fit in array size
}
