#include <string>
#include <iostream>

using namespace std;

typedef struct slot {
    string data;
    slot* next; // pointer to next node
} slot;

typedef struct slots {
    int collection_length;
    slot* collection; // pointer to head of linked list
} slots;

class hashmap {
private:
    slots* array;
    size_t numberOfSlots;

public:
    hashmap(int num);
    ~hashmap(void);
    // insert puts an element with "data" at given "index"
    void insert(int index, string data);
    // removes an element with "data" at given "index"
    void remove(int index, string data);
    // prints linked list at slot index
    void display(int index);
    // return the size of slots
    int getCollectionLength(int index);
};
