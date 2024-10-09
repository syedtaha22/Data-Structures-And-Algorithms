/*
    Insertion Sort Algorithm:
    - In insertion sort, we start from the second element of the array and compare it with the elements before it.
    - If the element is smaller than the previous element, we shift the previous element to the right.
    - We continue this process until we find the correct position for the element.
    - This process is repeated for all elements in the array.

    Time Complexity:
    - Best Case: O(n) - When the array is already sorted.
    - Average Case: O(n^2) - When the array is in random order.
    - Worst Case: O(n^2) - When the array is in reverse order.

    Space Complexity: O(1)
    In-Place: Yes
    Stable: Yes
*/

#include <iostream>
#include <vector>

// Template function to perform Insertion Sort
template <typename T>
void insertionSort(std::vector<T>& arr) {
    // Get the size of the array
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        // Store the Current element
        T key = arr[i];
        int j = i - 1; // Index of the previous element
        // Move elements of arr[0..i-1] that are greater than key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // Shift the element to the right
            j--;
        }
        arr[j + 1] = key; // Insert the key in the correct position
    }
}