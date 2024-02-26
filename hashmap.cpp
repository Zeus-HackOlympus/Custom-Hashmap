#include "hashmap.hpp"

using namespace std;

hashmap::hashmap(int num)
{
    this->numberOfSlots = num;
    this->array = new slots[num];

    for (int i = 0; i < numberOfSlots; i++) {
        slots* parentSlot = &this->array[i];
        parentSlot->collection_length = 0;
        parentSlot->collection = nullptr;
    }
}

hashmap::~hashmap()
{
    for (int i = 0; i < numberOfSlots; i++) {
        slots* parentSlot = &this->array[i];
        slot* current = parentSlot->collection;
        while (current != nullptr) {
            slot* temp = current;
            current = current->next;
            delete temp;
        }
    }

    delete[] this->array;
}

void hashmap::insert(int index, string data)
{
    slot* newSlot = new slot;
    newSlot->data = data;
    newSlot->next = nullptr;

    slots& parentSlot = this->array[index];
    if (parentSlot.collection == nullptr) {
        parentSlot.collection = newSlot;
    } else {
        slot* current = parentSlot.collection;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newSlot;
    }

    parentSlot.collection_length++;
}

void hashmap::remove(int index, string data)
{
    slots& parentSlot = this->array[index];
    slot* current = parentSlot.collection;
    slot* previous = nullptr;

    if (parentSlot.collection == nullptr) {
        return;
    }

    if (current->data == data) {
        parentSlot.collection = current->next;
        delete current;
        parentSlot.collection_length--;
        return;
    }

    while (current != nullptr && current->data != data) {
        previous = current;
        current = current->next;
    }

    if (current != nullptr) {
        previous->next = current->next;
        delete current;
        parentSlot.collection_length--;
    }
}

void hashmap::display(int index)
{
    slots& parentSlot = this->array[index];
    slot* current = parentSlot.collection;
    cout << "Slot " << index << ": ";

    if (current == nullptr) {
        cout << endl;
        return;
    }

    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int hashmap::getCollectionLength(int index)
{
    slots* parentSlot = &this->array[index];
    return parentSlot->collection_length;
}
