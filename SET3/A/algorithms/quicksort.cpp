#include "utils.h"

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

int main() {
    std::vector<std::string> elements;
    long long comparison_count = 0;
    read_data(elements);

    auto start = std::chrono::high_resolution_clock::now();

    quicksort(elements, 0, elements.size() - 1, comparison_count);
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    print_results(elements, comparison_count, elapsed_seconds);
    return 0;
}
