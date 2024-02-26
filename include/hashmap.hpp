#include <string>
#include <iostream>

using namespace std;

typedef struct slot {
    string data;
    slot* next;
} slot;

typedef struct slots {
    int collection_length;
    slot* collection;
} slots;

class hashmap {
private:
    slots* array;
    size_t numberOfSlots;

public:
    hashmap(int num);
    ~hashmap(void);
    void insert(int index, string data);
    void remove(int index, string data);
    void display(int index);
    int getCollectionLength(int index);
};
