#include "utils.h"

std::string get_prefix(const std::string& s, int L) {
    return s.substr(0, std::min(L, static_cast<int>(s.length())));
}

void ternary_string_quick_sort(std::vector<std::string>& R, int low, int high, int L, long long& comparison_count) {
    if (low >= high) return;

    int less = low, equal = low, great = high + 1;

    std::string pivot = get_prefix(R[low + (high - low) / 2], L);

    while (equal < great) {
        std::string prefix = get_prefix(R[equal], L);
        if (prefix < pivot) {
            comparison_count++;
            std::swap(R[less++], R[equal++]);
        } else if (prefix > pivot) {
            comparison_count++;
            std::swap(R[equal], R[--great]);
        } else {
            equal++;
        }
    }

    int excl_start = less;
    for (int i = low; i < less; i++) {
        if (R[i].size() == L) {
            std::swap(R[low++], R[i--]);
        }
    }

    ternary_string_quick_sort(R, low, less - 1, L, comparison_count);
    ternary_string_quick_sort(R, excl_start, equal - 1, L + 1, comparison_count);
    ternary_string_quick_sort(R, great, high, L, comparison_count);
}

int main() {
    std::vector<std::string> elements;
    long long comparison_count = 0;
    read_data(elements);

    auto start = std::chrono::high_resolution_clock::now();

    ternary_string_quick_sort(elements, 0, elements.size() - 1, 0, comparison_count);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    print_results(elements, comparison_count, elapsed_seconds);
    return 0;
}
