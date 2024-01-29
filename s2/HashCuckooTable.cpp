#include "HashCuckooTable.h"
#include <functional>
#include <iostream>

HashCuckooTable::HashCuckooTable(int capacity) : capacity(capacity) {
    table1.resize(capacity, -1);
    table2.resize(capacity, -1);
}

void HashCuckooTable::insert(int key) {
    if (search(key)) { // Key already exists
        return;
    }

    size_t pos1 = hash1(key), pos2;
    int loopCounter = 0, maxLoops = 50; // Limiting the number of loops to avoid infinite loop

    while (loopCounter < maxLoops) {
        if (table1[pos1] == -1) {
            table1[pos1] = key;
            return;
        }

        std::swap(key, table1[pos1]);
        pos2 = hash2(key);

        if (table2[pos2] == -1) {
            table2[pos2] = key;
            return;
        }

        std::swap(key, table2[pos2]);
        pos1 = hash1(key);
        loopCounter++;
    }

    rehash(); // Rehash if a cycle is detected
    insert(key); // Try inserting again
}

bool HashCuckooTable::search(int key) const {
    size_t pos1 = hash1(key);
    size_t pos2 = hash2(key);

    return table1[pos1] == key || table2[pos2] == key;
}

size_t HashCuckooTable::hash1(int key) const {
    return std::hash<int>{}(key) % capacity;
}

size_t HashCuckooTable::hash2(int key) const {
    return (std::hash<int>{}(key) / capacity) % capacity;
}

void HashCuckooTable::rehash() {
    std::vector<int> oldTable1 = table1;
    std::vector<int> oldTable2 = table2;

    table1.clear();
    table2.clear();
    table1.resize(capacity * 2, -1);
    table2.resize(capacity * 2, -1);
    capacity *= 2;

    for (int i : oldTable1) {
        if (i != -1) {
            insert(i);
        }
    }

    for (int i : oldTable2) {
        if (i != -1) {
            insert(i);
        }
    }
}

// Overload operator<<
std::ostream& operator<<(std::ostream& os, const HashCuckooTable& table) {
    os << "[ ";
    for (int i = 0; i < table.capacity; ++i) {
        if (table.table1[i] == -1) {
            os << "empty ";
        } else {
            os << table.table1[i] << " ";
        }
    }
    os << "]\t[";
    for (int i = 0; i < table.capacity; ++i) {
        if (table.table2[i] == -1) {
            os << "empty ";
        } else {
            os << table.table2[i] << " ";
        }
    }
    os << "]";

    return os;
}