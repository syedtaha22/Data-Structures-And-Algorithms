#include <iostream>
#include <vector>

// Function to merge two sorted subarrays and count inversions
int merge_and_count(std::vector<int>& arr, int left, int mid, int right) {
    // Create two subarrays from the input array
    std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    // Initialize variable for counting inversions
    int inversions = 0;
    // Initialize indices for the two subarrays and the main array
    int i = 0, j = 0, k = left;

    // Merge the two subarrays and count inversions
    while (i < leftArr.size() && j < rightArr.size()) {
        // If the element in the left subarray is smaller or equal, copy it to the main array
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        }
        // If the element in the right subarray is smaller, copy it to the main array
        // and increment the inversion count by the number of elements remaining in the left subarray
        else {
            arr[k++] = rightArr[j++];
            inversions += (leftArr.size() - i);
        }
    }
    // Copy remaining elements
    while (i < leftArr.size()) {
        arr[k++] = leftArr[i++];
    }
    while (j < rightArr.size()) {
        arr[k++] = rightArr[j++];
    }

    // return the total number of inversions
    return inversions;
}

// Merge sort with inversion counting
int merge_sort_and_count(std::vector<int>& arr, int left, int right) {
    int inversions = 0; // Initialize the number of inversions

    // Base case: if the subarray has 0 or 1 elements, it is already sorted
    if (left >= right) return inversions;

    // Calculate the midpoint of the subarray
    int mid = left + (right - left) / 2;

    // Recursively sort the left half and count inversions
    inversions += merge_sort_and_count(arr, left, mid);
    // Recursively sort the right half and count inversions
    inversions += merge_sort_and_count(arr, mid + 1, right);
    // Merge the two sorted halves and count inversions
    inversions += merge_and_count(arr, left, mid, right);

    // Return the total number of inversions
    return inversions;
}

int main() {
    // Test Cases generate from ChatGPT
    std::vector<std::vector<int>> testCases = {
        {2, 3, 8, 6, 1},      // Test case 1: 5 inversions
        {1, 2, 3, 4, 5},      // Test case 2: 0 inversions
        {5, 4, 3, 2, 1},      // Test case 3: 10 inversions
        {1, 3, 2, 3, 1},      // Test case 4: 4 inversions
        {}                    // Test case 5: 0 inversions (empty array)
    };

    for (int i = 0; i < testCases.size(); ++i) {
        std::cout << "Test Case " << i + 1 << ": ";
        for (int num : testCases[i]) std::cout << num << " ";
        std::cout << "\nNumber of inversions: " << merge_sort_and_count(testCases[i], 0, testCases[i].size() - 1) << std::endl;
        std::cout << "Sorted array: ";
        for (int num : testCases[i]) std::cout << num << " ";
        std::cout << "\n\n";
    }

    return 0;
}