/*
    Selection Sort Algorithm:
    - Find the minimum element in the unsorted part of the array and swap it with the first element.

    Time Complexity:
    - Best Case: O(n^2) - When the array is already sorted.
    - Average Case: O(n^2) - When the array is in random order.
    - Worst Case: O(n^2) - When the array is in reverse order.

    Space Complexity: O(1)
    In-Place: Yes
    Stable: No
*/

#include <iostream>
#include <vector>

// Template function to perform Selection Sort
template <typename T>
void selectionSort(std::vector<T>& arr) {
    // Get the size of the array
    int n = arr.size();
    for (int i = 0;i < n - 1;i++) {
        // Variable to store the minimum element
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                // Update the minimum element index
                minIndex = j;
            }
        }
        // Swap the minimum with the current element
        std::swap(arr[i], arr[minIndex]);
    }
}