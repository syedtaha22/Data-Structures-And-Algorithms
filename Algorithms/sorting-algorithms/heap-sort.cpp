/*
    Heap Sort:
    - Heap Sort is a comparison-based sorting algorithm that uses a max-heap data structure.
    - It first builds a max-heap from the input array and then repeatedly extracts the maximum
     element from the heap.
    - The extracted elements are placed at the end of the array, resulting in a sorted array.

    Time Complexity:
    - Best Case: O(n)
    - Average Case: O(n log n)
    - Worst Case: O(n log n)

    Space Complexity: O(1)
    In-Place: Yes
    Stable: No
*/

#include <iostream>
#include <vector>

// Function to perform iterative heapify on a max heap using 1-based indexing
void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i; // Initialize largest as root
    while (true) {
        int left = 2 * i;     // Left child (1-based indexing)
        int right = 2 * i + 1; // Right child (1-based indexing)

        // If the left child is larger than the root
        if (left <= n && arr[left] > arr[largest]) {
            largest = left;
        }

        // If the right child is larger than the largest so far
        if (right <= n && arr[right] > arr[largest]) {
            largest = right;
        }

        // If the largest is not the root
        if (largest != i) {
            std::swap(arr[i], arr[largest]); // Swap root with largest

            // Move to the largest node and continue heapifying
            i = largest;
        }
        else {
            break; // Exit loop if the heap property is satisfied
        }
    }
}

// Function to perform heap sort using max heap
void heapSort(std::vector<int>& arr) {
    int n = arr.size() - 1; // Size of the heap (adjusted for 1-based indexing)

    // Build the max heap (rearrange the array)
    for (int i = n / 2; i >= 1; --i) {
        heapify(arr, n, i);
    }

    // One by one extract elements from the heap
    for (int i = n; i > 1; --i) {
        std::swap(arr[1], arr[i]); // Move the current root to the end
        heapify(arr, i - 1, 1);    // Heapify the reduced heap
    }
}