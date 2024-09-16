/*
    Task 3:
        Hoare's original quicksort:
            Implement a version of Hoare's original quicksort algorithm. It's similar to our two-way partitioning
            algorithm except that the pivot is not swapped into its final position. Instead, the pivot is left in
            one of the two subarrays, no element is fixed in its final position, and the two subarrays where the
            pointers cross are sorted recursively.
*/

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

// Function to partition the array
// std::vector<int>& a: the array to partition
// int lo: the lower bound of the partition
// int hi: the upper bound of the partition
int partition(std::vector<int>& a, int lo, int hi) {
    // Put i and j at the beginning and end of the partition
    int i = lo, j = hi;

    // Use while loop instead of do-while to partition the array
    while (true) {
        // Move i to the right until it finds an element greater than or equal to the pivot
        while (a[i] < a[lo]) i++;

        // Move j to the left until it finds an element less than or equal to the pivot
        while (a[j] > a[lo]) j--;

        // If i and j cross, break
        if (i >= j) return j;

        // Swap the elements at i and j
        std::swap(a[i], a[j]);

        // Move i and j for the next iteration
        i++;
        j--;
    }
}

void quicksort(std::vector<int>& a, int lo, int hi) {
    // Base case: if hi <= lo, the array is already sorted
    if (hi <= lo) return;

    // Partition the array
    int j = partition(a, lo, hi);

    // Recursively sort the left partition
    quicksort(a, lo, j);
    // Recursively sort the right partition
    quicksort(a, j + 1, hi);
}

void quicksort(std::vector<int>& a) {
    // Shuffle the array to ensure performance
    std::shuffle(a.begin(), a.end(), std::default_random_engine(std::random_device{}()));
    // Call the recursive quicksort function
    quicksort(a, 0, a.size() - 1);
}

int main() {
    // Generate a random vector of integers
    std::vector<int> arr = { 12, 4, 56, 17, 8, 99, 5, 23, 1, 65 };

    // Print the unsorted array
    std::cout << "Unsorted array: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;

    // Call the quicksort function
    quicksort(arr);

    // Print the sorted array
    std::cout << "Sorted array: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}
