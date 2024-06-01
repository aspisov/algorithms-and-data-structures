#include "utils.h"
#include <unordered_map>

const std::string VOCAB = "!#%()*-0123456789:;@ABCDEFGHIJKLMNOPQRSTUVWXYZ^abcdefghijklmnopqrstuvwxyz";
const int VOCAB_SIZE = VOCAB.size();

std::unordered_map<char, int> build_vocab_map() {
    std::unordered_map<char, int> vocab_map;
    for (int i = 0; i < VOCAB_SIZE; ++i) {
        vocab_map[VOCAB[i]] = i;
    }
    return vocab_map;
}

template<typename T>
void quicksort(std::vector<T>& arr, int low, int high, long long& comparison_count) {
    if (low < high) {
        T pivot = arr[(low + high) / 2];
        int i = low;
        int j = high;
        while (i <= j) {
            while (arr[i] < pivot) { comparison_count++; i++; }
            while (arr[j] > pivot) { comparison_count++; j--; }
            if (i <= j) {
                std::swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
        quicksort(arr, low, j, comparison_count);
        quicksort(arr, i, high, comparison_count);
    }
}

void msd_radix_sort_with_switch(std::vector<std::string>& arr, int depth, long long& comparison_count, int threshold = 10, const std::unordered_map<char, int>& vocab_map = build_vocab_map()) {
    if (arr.size() <= 1) return;

    if (arr.size() < threshold) {
        quicksort(arr, 0, arr.size() - 1, comparison_count);
        return;
    }

    std::vector<std::vector<std::string>> buckets(VOCAB_SIZE + 1);

    for (const std::string& s : arr) {
        int index = (depth < s.size()) ? vocab_map.at(s[depth]) + 1 : 0;
        buckets[index].push_back(s);
        comparison_count++;
    }

    arr.clear();

    for (auto& bucket : buckets) {
        if (!bucket.empty()) {
            msd_radix_sort_with_switch(bucket, depth + 1, comparison_count, threshold, vocab_map);
            arr.insert(arr.end(), bucket.begin(), bucket.end());
        }
    }
}

int main() {
    std::vector<std::string> elements;
    long long comparison_count = 0;
    read_data(elements);

    auto start = std::chrono::high_resolution_clock::now();
    msd_radix_sort_with_switch(elements, 0, comparison_count, 10, build_vocab_map());
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    print_results(elements, comparison_count, elapsed_seconds);
    return 0;
}
