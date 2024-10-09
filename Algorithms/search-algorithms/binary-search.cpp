/*
    Binary Search:
    - Binary search is a fast search algorithm with run-time complexity of O(log n).
    - This search algorithm works on the principle of divide and conquer.
    - For this algorithm to work properly, the data collection should be in sorted form.
    - Binary search looks for a particular item by comparing the middle most item of the collection.
    - If a match occurs, then the index of the item is returned.
    - If the middle item is greater than the item, then the item is searched in the sub-array to
     the left of the middle item.
    - Otherwise, the item is searched for in the sub-array to the right of the middle item.
    - This process continues on the sub-array as well until the size of the subarray reduces to zero.

    Time Complexity:
    - Best Case: O(1) - The best case occurs when the middle element is the desired element.
    - Average Case: O(log n) - The average case occurs when the desired element is found after
      log n comparisons.
    - Worst Case: O(log n) - The worst case occurs when the desired element is not present in the array.

    Space Complexity:
    - O(1) - Binary search is an in-place algorithm.
*/

#include <iostream>
#include <vector>

// Include Quick Sort to sort the array before performing binary search
#include "../sorting-algorithms/quick-sort.cpp"

// Template function perform binary search on a given array
template <typename T>
int binarySearch(std::vector<T>& arr, T key) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) return mid; // If key is found, return the index
        if (arr[mid] < key) left = mid + 1; // If key is greater, ignore left half
        else right = mid - 1; // If key is smaller, ignore right half

    }

    // If the key is not found, return -1
    return -1;
}

// Main function to test the binary search algorithm
int main() {
    std::vector<int> arr = { 12, 45, 64, 78, 93, 108, 123, 200, 245, 300 };
    int key = 93;

    // Sort the array before performing binary search
    quickSort(arr);

    // Perform binary search
    int index = binarySearch(arr, key);

    if (index != -1) {
        std::cout << "Element found at index: " << index << std::endl;
    }
    else {
        std::cout << "Element not found in the array." << std::endl;
    }

    return 0;
}