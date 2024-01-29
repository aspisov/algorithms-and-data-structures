#include "HashLPTable.h"
#include <functional>

// Constructor
HashLPTable::HashLPTable(int capacity) : capacity(capacity), count(0) {
    table = new Entry[capacity];
    for (int i = 0; i < capacity; ++i) {
        table[i].occupied = false;
        table[i].deleted = false;
    }
}

// Destructor
HashLPTable::~HashLPTable() {
    delete[] table;
}

// Insert method
void HashLPTable::insert(const int& key) {
    int index = hash(key);

    // Linear probing to find the correct index
    while (table[index].occupied && !table[index].deleted && table[index].key != key) {
        index = (index + 1) % capacity;
    }

    // Check if the key already exists
    if (table[index].key == key && !table[index].deleted) {
        // Key already exists, handle it according to your policy (overwrite, ignore, etc.)
        return;
    }

    // Insert the new key
    table[index].key = key;
    table[index].occupied = true;
    table[index].deleted = false;
    count++;
}

// Search method
bool HashLPTable::search(const int& key) const {
    int index = hash(key);
    int originalIndex = index;

    // Search for the key using linear probing
    while (table[index].occupied || table[index].deleted) {
        if (table[index].key == key && !table[index].deleted) {
            return true; // Key found
        }
        index = (index + 1) % capacity;
        if (index == originalIndex) {
            break; // We've looped all the way around the table
        }
    }
    return false; // Key not found
}

// Remove method
void HashLPTable::remove(const int& key) {
    int index = hash(key);
    int originalIndex = index;

    // Search for the key using linear probing
    while (table[index].occupied || table[index].deleted) {
        if (table[index].key == key && !table[index].deleted) {
            // Mark as deleted
            table[index].deleted = true;
            count--;
            return; // Key found and marked as deleted
        }
        index = (index + 1) % capacity;
        if (index == originalIndex) {
            break; // We've looped all the way around the table
        }
    }
    // If we reach here, the key was not found
}

// Hash function
int HashLPTable::hash(const int& key) const {
    return std::hash<int>{}(key) % capacity;
}

// Linear probing function
int HashLPTable::probe(const int& key) const {
    int index = hash(key);
    int originalIndex = index;
    while (table[index].occupied && table[index].key != key) {
        index = (index + 1) % capacity;
        if (index == originalIndex) {
            return -1; // Indicates that the table is full
        }
    }
    return index;
}

// Overload operator<<
std::ostream& operator<<(std::ostream& os, const HashLPTable& table) {
    os << "[ ";
    for (int i = 0; i < table.capacity; ++i) {
        if (table.table[i].deleted) {
            os << "DELETED ";
        } else if (!table.table[i].occupied) {
            os << "empty ";
        } else {
            os << table.table[i].key << " ";
        }
    }
    os << "]";
    return os;
}

