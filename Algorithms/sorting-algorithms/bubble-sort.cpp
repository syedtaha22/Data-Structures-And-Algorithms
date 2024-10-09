/*
    Bubble Sort Algorithm:
    - Compare each pair of adjacent elements from the beginning of an array and,
      if they are in the wrong order, swap them.

    Time Complexity:
    - Best Case: O(n) - When the array is already sorted.
    - Average Case: O(n^2) - When the array is in random order.
    - Worst Case: O(n^2) - When the array is in reverse order.

    Space Complexity: O(1)
    In-Place: Yes
    Stable: Yes


    Bubble Sort is not recommended for large data sets as it is not efficient.
*/

#include <iostream>
#include <vector>

// Template function to perform Bubble Sort
template <typename T>
void bubbleSort(std::vector<T>& arr) {
    // Get the size of the array
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1;j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap the elements if they are in the wrong order
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no elements were swapped, array is already sorted
        if (!swapped)
            break;
    }
}