#ifndef HASHLP_TABLE_H
#define HASHLP_TABLE_H

#include <iostream>

class HashLPTable {
public:
    HashLPTable(int capacity); // Constructor with initial capacity
    ~HashLPTable(); // Destructor

    void insert(const int& key); // Insert key
    bool search(const int& key) const; // Search key
    void remove(const int& key); // Remove key

    friend std::ostream& operator<<(std::ostream& os, const HashLPTable& table);

private:
    struct Entry {
        int key;
        bool occupied;
        bool deleted;

        Entry() : key(0), occupied(false), deleted(false) {}
    };

    Entry* table; // Pointer to the table array
    int capacity; // Capacity of the hash table
    int count; // Number of elements in the hash table

    int hash(const int& key) const; // Hash function
    int probe(const int& key) const; // Linear probing function
};

#endif // HASHLP_TABLE_H
