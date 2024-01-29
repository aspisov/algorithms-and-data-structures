#include "s2/HashLPTable.h"
#include "s2/HashCuckooTable.h"
#include <iostream>

void testHashLPTable();

void testHashCuckooTable();

int main() {
    testHashLPTable();
    testHashCuckooTable();

    return 0;
}

void testHashLPTable() {
    HashLPTable hashTable(6);

    hashTable.insert(1);
    std::cout << hashTable << std::endl;
    hashTable.insert(2);
    std::cout << hashTable << std::endl;
    hashTable.insert(5);
    std::cout << hashTable << std::endl;
    hashTable.insert(11);
    std::cout << hashTable << std::endl;
    hashTable.remove(11);
    std::cout << hashTable << std::endl;
    hashTable.insert(17);
    std::cout << hashTable << std::endl;
    hashTable.insert(6);
    std::cout << hashTable << std::endl;
    hashTable.insert(177);
    std::cout << hashTable << std::endl;

    std::cout << "\n" << "-------------------------------" << "\n" << std::endl;
}

void testHashCuckooTable() {
    HashCuckooTable hashTable(6);

    hashTable.insert(1);
    std::cout << hashTable << std::endl;
    hashTable.insert(2);
    std::cout << hashTable << std::endl;
    hashTable.insert(5);
    std::cout << hashTable << std::endl;
    hashTable.insert(11);
    std::cout << hashTable << std::endl;
    hashTable.insert(17);
    std::cout << hashTable << std::endl;
    hashTable.insert(6);
    std::cout << hashTable << std::endl;
    hashTable.insert(177);
    std::cout << hashTable << std::endl;

    std::cout << "\n" << "-------------------------------" << "\n" << std::endl;
}
