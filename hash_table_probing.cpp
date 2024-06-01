
#include <iostream>
#include <vector>
#include <cmath>

constexpr int M = 1024; // Size of the hash table
constexpr int NUM_KEYS = 30000; // Number of keys to insert
constexpr int c1 = 1, c2 = 1, c3 = 1; // Constants for probing

// Hash function
int hash(int key) {
    return key % M;
}

// Quadratic probing function
int quadraticProbe(int key, int i) {
    return (hash(key) + c1 * i + c2 * i * i) % M;
}

// Cubic probing function
int cubicProbe(int key, int i) {
    return (hash(key) + c1 * i + c2 * i * i + c3 * i * i * i) % M;
}

// Function to insert keys using a probing function and count clusters
std::pair<int, int> insertAndCountClusters(int (*probeFunc)(int, int)) {
    std::vector<int> table(M, -1); // Initialize hash table
    int numClusters = 0;
    int clusterSize = 0;

    for (int key = 0; key < NUM_KEYS; ++key) {
        int i = 0;
        int index = probeFunc(key, i);
        while (table[index] != -1 && i < M) { // Find an empty slot
            ++i;
            index = probeFunc(key, i);
        }
        if (i > 0) { // We have a cluster
            if (clusterSize == 0) ++numClusters; // New cluster
            ++clusterSize;
        } else {
            clusterSize = 0; // End of current cluster
        }
        if (i < M) table[index] = key; // Insert key
    }
    return {numClusters, NUM_KEYS - numClusters};
}

int main() {
    auto [quadClusters, quadSingle] = insertAndCountClusters(quadraticProbe);
    auto [cubicClusters, cubicSingle] = insertAndCountClusters(cubicProbe);

    std::cout << "Quadratic Probing: " << quadClusters << " clusters, "
              << quadSingle << " single insertions\n";
    std::cout << "Cubic Probing: " << cubicClusters << " clusters, "
              << cubicSingle << " single insertions\n";

    return 0;
}
