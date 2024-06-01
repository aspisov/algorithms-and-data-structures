#include "utils.h"

template <typename T>
void merge(std::vector<T>& arr, std::vector<T>& temp, int left, int mid, int right, long long& comparison_count) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        comparison_count++;
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

template <typename T>
void bottom_up_mergesort(std::vector<T>& arr, std::vector<T>& temp, long long& comparison_count) {
    int n = arr.size();
    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += 2 * width) {
            int left = i;
            int mid = std::min(i + width - 1, n - 1);
            int right = std::min(i + 2 * width - 1, n - 1);
            if (mid < right) {
                merge(arr, temp, left, mid, right, comparison_count);
            }
        }
    }
}

int main() {
    std::vector<std::string> elements, temp;
    long long comparison_count = 0;
    read_data(elements);

    auto start = std::chrono::high_resolution_clock::now();

    temp.resize(elements.size());
    bottom_up_mergesort(elements, temp, comparison_count);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    print_results(elements, comparison_count, elapsed_seconds);
    return 0;
}
