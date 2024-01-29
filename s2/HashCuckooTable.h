#ifndef HASHCUCKOO_TABLE_H
#define HASHCUCKOO_TABLE_H

#include <vector>
#include <stdexcept>

class HashCuckooTable {
public:
    HashCuckooTable(int capacity);
    void insert(int key);
    bool search(int key) const;

private:
    std::vector<int> table1, table2;
    int capacity;

    size_t hash1(int key) const;
    size_t hash2(int key) const;
    void rehash();
    friend std::ostream& operator<<(std::ostream& os, const HashCuckooTable& table);
};

#endif // HASHCUCKOO_TABLE_H
