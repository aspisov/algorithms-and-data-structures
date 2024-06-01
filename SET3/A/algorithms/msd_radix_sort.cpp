#include "utils.h"
#include <unordered_map>

const std::string VOCAB = "!#%()*-0123456789:;@ABCDEFGHIJKLMNOPQRSTUVWXYZ^abcdefghijklmnopqrstuvwxyz";
const int VOCAB_SIZE = VOCAB.size();

std::unordered_map<char, int> build_vocab_map() {
    std::unordered_map<char, int> vocab_map;
    for (int i = 0; i < VOCAB_SIZE; ++i) {
        vocab_map[VOCAB[i]] = i + 1;
    }
    return vocab_map;
}

int find_max_depth(const std::vector<std::string>& arr) {
    int max_depth = 0;
    for (const auto& s : arr) {
        if (s.length() > max_depth) {
            max_depth = s.length();
        }
    }
    return max_depth;
}

void msd_radix_sort(std::vector<std::string>& arr, int left, int right, int depth, long long& comparison_count, int max_depth, const std::unordered_map<char, int>& vocab_map) {
    if (left >= right || depth >= max_depth) return;

    std::vector<int> count(VOCAB_SIZE + 2, 0);
    std::vector<std::string> aux(right - left + 1);

    for (int i = left; i <= right; ++i) {
        int c = (depth < arr[i].size()) ? vocab_map.at(arr[i][depth]) : 0;
        count[c + 1]++;
        comparison_count++;
    }

    for (int r = 0; r < VOCAB_SIZE + 1; ++r) {
        count[r + 1] += count[r];
    }

    for (int i = left; i <= right; ++i) {
        int c = (depth < arr[i].size()) ? vocab_map.at(arr[i][depth]) : 0;
        aux[count[c]++] = std::move(arr[i]);
    }

    for (int i = left; i <= right; ++i) {
        arr[i] = std::move(aux[i - left]);
    }

    for (int r = 0; r < VOCAB_SIZE + 1; ++r) {
        msd_radix_sort(arr, left + count[r], left + count[r + 1] - 1, depth + 1, comparison_count, max_depth, vocab_map);
    }
}

int main() {
    std::vector<std::string> elements;
    long long comparison_count = 0;
    read_data(elements);

    auto start = std::chrono::high_resolution_clock::now();

    int max_depth = find_max_depth(elements);
    std::unordered_map<char, int> vocab_map = build_vocab_map();
    msd_radix_sort(elements, 0, elements.size() - 1, 0, comparison_count, max_depth, vocab_map);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    print_results(elements, comparison_count, elapsed_seconds);
    return 0;
}
