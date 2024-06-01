import random


class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size

    def hash(self, key):
        return key % self.size

    def insert(self, key, c1, c2, c3=None):
        i = 0
        while True:
            if c3 is None:
                index = (self.hash(key) + c1 * i + c2 * i * i) % self.size
            else:
                index = (self.hash(key) + c1 * i + c2 * i * i + c3 * i * i * i) % self.size

            if self.table[index] is None:
                self.table[index] = key
                return True
            else:
                i += 1
                if i >= self.size:
                    return False

    def count_clusters(self):
        clusters = 0
        in_cluster = False
        for slot in self.table:
            if slot is not None:
                if not in_cluster:
                    clusters += 1
                    in_cluster = True
            else:
                in_cluster = False
        return clusters


def compare_clusters(size, c1, c2, c3=None):
    table = HashTable(size)
    elements_inserted = 0
    while elements_inserted < (size * 0.75):
        key = random.randint(1, 10000)
        if table.insert(key, c1, c2, c3):
            elements_inserted += 1
        else:
            break
    return table.count_clusters()


sizes = [2 ** x for x in range(4, 9)]
cluster_comparison = {'size': [], 'quadratic': [], 'cubic': []}

for size in sizes:
    q_clusters = compare_clusters(size, 1, 1)
    c_clusters = compare_clusters(size, 1, 1, 1)

    cluster_comparison['size'].append(size)
    cluster_comparison['quadratic'].append(q_clusters)
    cluster_comparison['cubic'].append(c_clusters)

print(cluster_comparison)
