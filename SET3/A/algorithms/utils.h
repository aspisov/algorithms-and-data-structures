#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <iterator>

void read_data(std::vector<std::string>& elements) {
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);
    std::string item;
    while (iss >> item) {
        elements.push_back(item);
    }
}

void print_results(const std::vector<std::string>& elements, long long comparison_count, std::chrono::duration<double> elapsed_seconds) {
    for (size_t i = 0; i < elements.size(); ++i) {
        std::cout << elements[i];
        if (i != elements.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    std::cout << elapsed_seconds.count() << " " << comparison_count;
}



