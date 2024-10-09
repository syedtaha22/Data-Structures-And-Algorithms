#include <iostream>
#include <vector>
#include <random>
#include <chrono> // For timing
#include <algorithm> // For std::is_sorted
#include <numeric>   // For accumulate
#include <iomanip>   // For formatting the output

const int CUTOFF = 10;  // cutoff for switching to insertion sort

// Insertion sort for small subarrays
void insertionSort(std::vector<int>& a, int lo, int hi) {
    for (int i = lo + 1; i <= hi; ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= lo && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

// Merge function for combining two sorted subarrays
void merge(std::vector<int>& a, std::vector<int>& aux, int lo, int mid, int hi) {
    for (int k = lo; k <= hi; k++) {
        aux[k] = a[k];
    }

    // Merge the two halves back into the original array
    int i = lo, j = mid + 1;

    for (int k = lo; k <= hi; k++) {
        // If the left half is exhausted, copy the right half
        if (i > mid) {
            a[k] = aux[j++];
        }
        // If the right half is exhausted, copy the left half
        else if (j > hi) {
            a[k] = aux[i++];
        }
        // Check if the element in the right half is smaller
        else if (aux[j] < aux[i]) {
            a[k] = aux[j++];
        }
        // Otherwise, the element in the left half is smaller
        else {
            a[k] = aux[i++];
        }
    }
}

// Standard (unoptimized) merge sort
void unoptimizedSort(std::vector<int>& a, std::vector<int>& aux, int lo, int hi) {
    // Base case: if the subarray has 0 or 1 elements, it is already sorted
    if (hi <= lo) return;
    // Calculate the midpoint of the subarray
    int mid = lo + (hi - lo) / 2;
    // Recursively sort the left half
    unoptimizedSort(a, aux, lo, mid);
    // Recursively sort the right half
    unoptimizedSort(a, aux, mid + 1, hi);
    // Merge the two sorted halves
    merge(a, aux, lo, mid, hi);
}

void unoptimizedSort(std::vector<int>& a) {
    // Initialize the auxiliary array and start sorting
    size_t N = a.size();
    std::vector<int> aux(N);
    unoptimizedSort(a, aux, 0, N - 1);
}

// Optimized merge sort with cutoff and sorted check
void optimizedSort(std::vector<int>& a, std::vector<int>& aux, int lo, int hi) {
    // Base case: if the subarray has 0 or 1 elements, it is already sorted
    if (hi <= lo) return;

    // 1. Cutoff to insertion sort for small subarrays
    if (hi <= lo + CUTOFF) {
        insertionSort(a, lo, hi);
        return;
    }

    // Calculate the midpoint
    int mid = lo + (hi - lo) / 2;


    // Recursively sort the left half
    optimizedSort(a, aux, lo, mid);
    // Recursively sort the right half
    optimizedSort(a, aux, mid + 1, hi);


    // Check if already sorted
    if (a[mid] <= a[mid + 1]) {
        return;
    }

    // Merge the sorted halves
    merge(a, aux, lo, mid, hi);
}

// Overloaded function to initialize auxiliary array and start optimized sorting
void optimizedSort(std::vector<int>& a) {
    // Initialize the auxiliary array and start sorting
    size_t N = a.size();
    std::vector<int> aux(N);
    // Call the optimized sort function with the cutoff value
    optimizedSort(a, aux, 0, N - 1);
}

// Function to analyze sorting times
void analyzeSortPerformance(int arraySize, int numTests) {
    // Initialize random number generator
    std::mt19937 gen(std::random_device{}());
    // Vectors to store the times for unoptimized and optimized merge sort
    std::vector<double> unoptimizedTimes, optimizedTimes;

    for (int t = 0; t < numTests; ++t) {
        // Print Progress
        std::cout << "Test " << t + 1 << " / " << numTests << "\r";
        // Generate random arrays
        std::vector<int> a(arraySize), b(arraySize);

        // Populate random arrays for testing
        for (int i = 0; i < arraySize; i++) {
            int random_number = gen();
            a[i] = random_number;
            b[i] = random_number;  // Copy same values for a fair comparison
        }

        // Measure time for unoptimized merge sort
        auto start_unoptimized = std::chrono::high_resolution_clock::now();
        unoptimizedSort(a);
        auto end_unoptimized = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_unoptimized = end_unoptimized - start_unoptimized;
        unoptimizedTimes.emplace_back(duration_unoptimized.count());

        // Measure time for optimized merge sort
        auto start_optimized = std::chrono::high_resolution_clock::now();
        optimizedSort(b);
        auto end_optimized = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration_optimized = end_optimized - start_optimized;
        optimizedTimes.emplace_back(duration_optimized.count());
    }

    // Calculate average, min, and max times
    double avg_unoptimized = std::accumulate(unoptimizedTimes.begin(), unoptimizedTimes.end(), 0.0) / numTests;
    double avg_optimized = std::accumulate(optimizedTimes.begin(), optimizedTimes.end(), 0.0) / numTests;
    double min_unoptimized = *std::min_element(unoptimizedTimes.begin(), unoptimizedTimes.end());
    double max_unoptimized = *std::max_element(unoptimizedTimes.begin(), unoptimizedTimes.end());
    double min_optimized = *std::min_element(optimizedTimes.begin(), optimizedTimes.end());
    double max_optimized = *std::max_element(optimizedTimes.begin(), optimizedTimes.end());

    // Calculate percentage improvement
    double percent_faster = ((avg_unoptimized - avg_optimized) / avg_unoptimized) * 100.0;

    // Output the results
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Results for " << numTests << " random arrays of size " << arraySize << ":\n";
    std::cout << "Unoptimized Merge Sort:\n";
    std::cout << "  Average Time: " << avg_unoptimized << "s\n";
    std::cout << "  Min Time:     " << min_unoptimized << "s\n";
    std::cout << "  Max Time:     " << max_unoptimized << "s\n";
    std::cout << "\nOptimized Merge Sort:\n";
    std::cout << "  Average Time: " << avg_optimized << "s\n";
    std::cout << "  Min Time:     " << min_optimized << "s\n";
    std::cout << "  Max Time:     " << max_optimized << "s\n";
    std::cout << "\nOptimized version is " << percent_faster << "% faster on average.\n";
}

int main() {
    int arraySize = 100000;  // Size of the arrays
    int numTests = 100;      // Number of tests to run


    std::cout << "Analyzing sorting performance...\n";
    analyzeSortPerformance(arraySize, numTests);

    return 0;
}
