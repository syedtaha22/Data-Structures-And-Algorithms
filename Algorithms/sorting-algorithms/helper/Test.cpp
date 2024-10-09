/*
    Template class to test sorting algorithms
*/

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <functional>

// Template class Test to measure sorting algorithm performance
template <typename T>
class Test {
private:
    // Function to generate a random array of size n
    std::vector<T> generateRandomArray(int n) {
        std::vector<T> arr(n);
        std::mt19937 rng(std::time(nullptr)); // Random number generator seeded with current time
        for (int i = 0; i < n; ++i) {
            arr[i] = rng(); // Generate random numbers
        }
        return arr;
    }

public:
    // Overloaded operator() to perform the test
    double operator()(void (*sortingAlgo)(std::vector<T>&), int n) {
        // Generate a random array of size n
        std::vector<T> arr = generateRandomArray(n);

        // Get the current time before sorting
        auto start = std::chrono::high_resolution_clock::now();

        // Perform the sorting using the given sorting algorithm
        sortingAlgo(arr);

        // Get the current time after sorting
        auto end = std::chrono::high_resolution_clock::now();

        // Calculate the duration of the sort
        std::chrono::duration<double> duration = end - start;

        // Print the duration of the sort
        std::cout << "Time taken to sort " << n << " elements: " << duration.count() << "s" << std::endl;

        return duration.count();  // Return the duration if needed
    }

};