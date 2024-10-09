/*
    Task 1:
        Stable partitioning:
            Implement a stable partitioning algorithm that rearranges the elements of an
            array so that all elements that are less than or equal to pivot come before all elements that are greater
            than or equal to pivot.


            The relative order of the elements should be preserved. The algorithm should run in O(n) time and use
            O(n) additional space.

*/

#include <iostream>
#include <vector>


// Function to perform stable partitioning
void stable_partition(std::vector<int>& arr, int pivot) {
    // Create vectors to store elements less than or equal to the pivot, and greater than the pivot
    std::vector<int> left;
    std::vector<int> right;

    // Traverse the array and partition elements based on the pivot
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] < pivot) {
            left.push_back(arr[i]);  // Elements < pivot go into the 'left' vector
        }
        else if (arr[i] > pivot) {
            right.push_back(arr[i]); // Elements > pivot go into the 'right' vector
        }
    }

    left.push_back(pivot);  // Add the pivot to the 'left' vector

    // Combine the 'left' and 'right' vectors back into the original array
    int index = 0; // Index to keep track of the position in the original array
    // Copy elements from 'left' vector to the original array
    for (int i = 0; i < left.size(); ++i) {
        arr[index++] = left[i];
    }
    // Copy elements from 'right' vector to the original array
    for (int i = 0; i < right.size(); ++i) {
        arr[index++] = right[i];
    }
}

int main() {
    // Example usage
    std::vector<int> arr = { 3, 8, 5, 2, 7, 6, 4 };
    int pivot = 3; // Pivot value

    // Print the original array
    std::cout << "Original array: ";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Pivot: " << pivot << std::endl;

    // Perform stable partitioning
    stable_partition(arr, pivot);

    // Print the partitioned array
    std::cout << "Partitioned array: ";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    // return 0 to indicate successful completion
    return 0;
}

// Pivot: 3
// Orignal: 3 8 5 2 7 6 4
// Left:    2 3
// Right:   8 5 7 6 4 
// Partitioned: 2 3 8 5 7 6 4