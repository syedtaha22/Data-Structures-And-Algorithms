#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For random seed
#include <chrono>  // For high-resolution timing

// Include the sorting algorithms
#include "../bubble-sort.cpp"
#include "../selection-sort.cpp"
#include "../insertion-sort.cpp"
#include "../merge-sort.cpp"
#include "../quick-sort.cpp"
#include "../heap-sort.cpp"

// Function to generate random arrays
std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand(); // Random integer
    }
    return arr;
}

// Function to log data to CSV file
void logToCSV(const std::string& filename, int size, const std::vector<double>& times) {
    std::ofstream file;
    file.open(filename, std::ios::app); // Append to file
    file << size;
    for (double time : times) {
        file << "," << time; // Log each time
    }
    file << "\n";
    file.close();
}

// Function to write the CSV headers dynamically
void writeCSVHeader(const std::string& filename, const std::vector<std::pair<std::string, void (*)(std::vector<int>&)>>& sortingAlgorithms) {
    std::ofstream file(filename);
    file << "Array Size"; // Start with "Array Size"
    for (const auto& algo : sortingAlgorithms) {
        file << "," << algo.first; // Add each algorithm name
    }
    file << "\n";
    file.close();
}

// Function to time a sorting algorithm using the provided signature
template <typename T>
double timeSortingAlgorithm(void (*sortingAlgo)(std::vector<T>&), std::vector<T>& arr) {
    auto start = std::chrono::high_resolution_clock::now();
    sortingAlgo(arr);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count(); // Return elapsed time
}

int main() {
    // Seed for random number generation
    std::srand(static_cast<unsigned>(std::time(0)));

    // Variable to store the starting array size
    constexpr int MIN_SIZE = 0;
    // Variable to store the maximum array size
    constexpr int MAX_SIZE = 100;
    // Variable to store the step size
    constexpr int STEP_SIZE = 100;

    // Vector to store the array sizes
    std::vector<int> sizes;
    for (int i = MIN_SIZE; i <= MAX_SIZE; i += STEP_SIZE) {
        sizes.push_back(i);
    }

    // Store sorting algorithms in a vector
    std::vector<std::pair<std::string, void (*)(std::vector<int>&)>> sortingAlgorithms = {
        {"Bubble Sort", bubbleSort},
        {"Selection Sort", selectionSort},
        {"Insertion Sort", insertionSort},
        {"Merge Sort", mergeSort},
        {"Quick Sort", quickSort},
        {"Heap Sort", heapSort}
    };

    // CSV file for logging
    std::string filename = "sorting_performance.csv";

    // Write the CSV headers dynamically
    writeCSVHeader(filename, sortingAlgorithms);

    // Loop through each array size
    for (int size : sizes) {
        std::vector<int> arr = generateRandomArray(size);
        std::vector<double> times(sortingAlgorithms.size());

        // Time each sorting algorithm
        for (size_t i = 0; i < sortingAlgorithms.size(); ++i) {
            std::vector<int> tempArr = arr; // Create a copy for sorting
            times[i] = timeSortingAlgorithm(sortingAlgorithms[i].second, tempArr); // Time the sort
            std::cout << "Completed " << sortingAlgorithms[i].first << std::endl;
        }

        // Log results to CSV
        logToCSV(filename, size, times);

        // Output to console for progress
        std::cout << "Completed sorting for array size: " << size << std::endl;
        // Add a separator for better readability
        std::cout << "----------------------------------------" << std::endl;
    }


    return 0;
}
