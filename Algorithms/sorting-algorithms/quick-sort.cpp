/*
    Quick Sort:
    - Quick Sort is a divide-and-conquer algorithm that uses a pivot element to partition the
     array into two sub-arrays.
    - It then recursively sorts the sub-arrays.

    Time Complexity:
    - Best Case: O(n log n) - When the pivot divides the array into two equal halves.
    - Average Case: O(n log n) - When the pivot divides the array into two sub-arrays of almost equal size.
    - Worst Case: O(n^2) - When the pivot divides the array into two sub-arrays of size 1 and n-1.

    Space Complexity: O(log n) - For the recursive call stack.
    In-Place: Yes
    Stable: No
*/

#include <iostream>
#include <vector>
#include <random> // For std::random_device and std::mt19937
#include <algorithm> // For std::swap and std::shuffle


// Template function to partition the array
// Use the first element as the pivot
template <typename T>
int partition(std::vector<T>& arr, int low, int high) {
    T pivot = arr[low]; // Choose the first element as the pivot
    int i = low + 1;    // Index of the first element after the pivot
    int j = high;       // Index of the last element

    // While the indexes do not cross
    while (i <= j) {
        // Move i to the right until we find an element greater than the pivot
        while (i <= j && arr[i] <= pivot) {
            i++;
        }
        // Move j to the left until we find an element less than the pivot
        while (i <= j && arr[j] > pivot) {
            j--;
        }
        // If the indexes have not crossed, swap the elements
        if (i < j) std::swap(arr[i], arr[j]);
    }
    // Swap the pivot with the element at index j
    std::swap(arr[low], arr[j]);
    // Return the index of the pivot element
    return j;
}

// Template function to perform Quick Sort
template <typename T>
void quickSort(std::vector<T>& arr, int low, int high) {
    if (low >= high) return; // Base case: 0 or 1 element

    // Partition the array
    int pivot = partition(arr, low, high);
    // Recursively sort the left and right sub-arrays
    quickSort(arr, low, pivot - 1);
    quickSort(arr, pivot + 1, high);
}

// Wrapper function to call Quick Sort
template <typename T>
void quickSort(std::vector<T>& arr) {
    // First shuffle the array to avoid worst-case time complexity
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(arr.begin(), arr.end(), g);
    // Call the recursive function
    quickSort(arr, 0, arr.size() - 1);
}