/*
    Task:
        Implement Yaroslavskiy's dual-pivot quicksort.
        Compare its performance with the standard quicksort using a vector of size 10,000 random integers.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono> // For performance measurement

// Dual-Pivot Partitioning
// std::vector<int>& a: the array to partition
// int lo: the lower bound of the partition
// int hi: the upper bound of the partition
// int& lp: the left pivot position
// int& rp: the right pivot position
void dualPivotPartition(std::vector<int>& a, int lo, int hi, int& lp, int& rp) {
    // If the left element is greater than the right element, swap them
    if (a[lo] > a[hi]) {
        std::swap(a[lo], a[hi]);
    }

    // Initialize the left and right pivot positions
    // int pivot1 = a[lo], pivot2 = a[hi];

    // Initialize the pointers
    int i = lo + 1, lt = lo + 1, gt = hi - 1;

    // While i is less than or equal to gt
    while (i <= gt) {
        // If the element is less than the left pivot, swap it with the element at lt
        if (a[i] < a[lo]) {
            std::swap(a[i], a[lt]);
            lt++; // Increment lt
        }
        // Else if the element is greater than the right pivot, swap it with the element at gt
        else if (a[i] > a[hi]) {
            // Swap the elements
            std::swap(a[i], a[gt]);
            gt--; // Decrement gt
            i--; // Decrement i to recheck the element at a[i]
        }
        i++; // Increment i
    }

    // Decrement lt and increment gt
    lt--;
    gt++;

    // Swap pivots to their correct positions
    std::swap(a[lo], a[lt]);
    std::swap(a[hi], a[gt]);

    // Update the left and right pivot positions
    lp = lt;
    rp = gt;
}

// Dual-Pivot Quicksort
void dualPivotQuicksort(std::vector<int>& a, int lo, int hi) {
    if (hi <= lo) return;

    int lp, rp;
    dualPivotPartition(a, lo, hi, lp, rp);

    dualPivotQuicksort(a, lo, lp - 1);   // Left side of the first pivot
    dualPivotQuicksort(a, lp + 1, rp - 1); // Between the two pivots
    dualPivotQuicksort(a, rp + 1, hi);   // Right side of the second pivot

}

// Overloaded Dual-Pivot quicksort function to sort the entire array
void dualPivotQuicksort(std::vector<int>& a) {
    std::shuffle(a.begin(), a.end(), std::default_random_engine(std::random_device{}()));
    dualPivotQuicksort(a, 0, a.size() - 1);
}

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


// Overloaded quicksort function to sort the entire array
void quicksort(std::vector<int>& a) {
    // Shuffle the array to ensure performance
    std::shuffle(a.begin(), a.end(), std::default_random_engine(std::random_device{}()));
    // Call the recursive quicksort function
    quicksort(a, 0, a.size() - 1);
}

// Function to generate a random vector of size 'size'
std::vector<int> generateRandomVector(int size) {
    std::vector<int> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100000);

    for (int i = 0; i < size; i++) {
        vec[i] = dis(gen);
    }
    return vec;
}

int main() {
    const int SIZE = 10000;

    // Generate random data for sorting
    std::vector<int> data1 = generateRandomVector(SIZE);
    std::vector<int> data2 = data1; // Create a copy for fair comparison

    // Print the unsorted array up to 10 elements
    std::cout << "Unsorted array: ";
    for (int i = 0; i < 10; i++)
        std::cout << data1[i] << " ";
    std::cout << "...\n";



    // Measure time for standard quicksort
    auto start = std::chrono::high_resolution_clock::now();
    quicksort(data1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> standard_quicksort_time = end - start;

    // Print the sorted array up to 10 elements
    std::cout << "Sorted array using standard quicksort: ";
    for (int i = 0; i < 10; i++)
        std::cout << data1[i] << " ";
    std::cout << "...\n";


    // Measure time for dual-pivot quicksort
    start = std::chrono::high_resolution_clock::now();
    dualPivotQuicksort(data2);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dual_pivot_quicksort_time = end - start;

    // Print the sorted array up to 10 elements
    std::cout << "Sorted array using dual-pivot quicksort: ";
    for (int i = 0; i < 10; i++)
        std::cout << data2[i] << " ";
    std::cout << "...\n\n";



    // Output the results
    std::cout << "Time taken by Hoare's Orignal quicksort: " << standard_quicksort_time.count() << " seconds.\n";
    std::cout << "Time taken by dual-pivot quicksort: " << dual_pivot_quicksort_time.count() << " seconds.\n";

    return 0;
}
