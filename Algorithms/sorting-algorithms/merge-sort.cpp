/*
    Merge Sort:
    - Merge Sort is a Divide and Conquer algorithm.
    - It recursively divides the array into two halves until each sub-array contains only one element.
    - It then merges the sub-arrays in a sorted order.

    Time Complexity:
    - Best Case: O(n log n) - When the array is already sorted.
    - Average Case: O(n log n) - When the array is in random order.
    - Worst Case: O(n log n) - When the array is in reverse order.

    Space Complexity: O(n)
    In-Place: No
    Stable: Yes
*/

#include <iostream>
#include <vector>

// Template Function to merge two sub-arrays
template <typename T>
void merge(std::vector<T>& arr, int left, int mid, int right) {
    int n = right - left + 1; // Total number of elements to merge
    std::vector<T> temp(n);      // Single auxiliary array
    int i = left;             // Starting index for the left half
    int j = mid + 1;          // Starting index for the right half
    int k = 0;                // Index for temp array

    // Merge the two halves into the temp array
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }

    // Copy remaining elements of the left half, if any
    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    // Copy remaining elements of the right half, if any
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    // Copy the merged elements back into the original array
    for (int p = 0; p < n; p++) {
        arr[left + p] = temp[p];
    }
}



// Template function to perform Merge Sort
template <typename T>
void mergeSort(std::vector<T>& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2; // Calculate the middle index

    mergeSort(arr, left, mid); // Sort the left half
    mergeSort(arr, mid + 1, right); // Sort the right half
    merge(arr, left, mid, right); // Merge the sorted halves
}

// Template function to perform Merge Sort
template <typename T>
void mergeSort(std::vector<T>& arr) {
    mergeSort<T>(arr, 0, arr.size() - 1);
}
