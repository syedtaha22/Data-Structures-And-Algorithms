/*
    Task 2:
        Verify the running time of brute-force 3Sum algorithm empirically
*/

#include <iostream> 
#include <chrono>     
#include <cstdlib>    
#include <ctime>      

// Function to solve the 3Sum problem using a brute-force approach
int ThreeSum(int arr[], int n) {
    int count = 0; // Initialize a counter to keep track of the number of valid triples

    // Triple nested loops to check all possible combinations of i, j, and k
    for (int i = 0; i < n; i++) {              // First loop: iterates over the first element
        for (int j = i + 1; j < n; j++) {      // Second loop: iterates over the second element
            for (int k = j + 1; k < n; k++) {  // Third loop: iterates over the third element
                // Check if the sum of the three elements is zero
                if (arr[i] + arr[j] + arr[k] == 0) {
                    count++; // Increment the count if a valid triple is found
                }
            }
        }
    }
    return count; // Return the total count of valid triples
}

// Function to generate an array of random integers between -100 and 100
// The function takes an array `arr` of size `n` and fills it with random integers
void generateRandomArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        // Generate a random integer between -100 and 100 and store it in the array
        arr[i] = rand() % 201 - 100;  // rand() % 201 generates a number between 0 and 200, subtracting 100 shifts the range to -100 to 100
    }
}

// Main function to test the running time of the 3Sum algorithm for different array sizes
int main() {
    // Seed the random number generator with the current time
    // This ensures that different random numbers are generated each time the program runs
    srand((time(0)));

    // Array of different sizes to test the 3Sum algorithm
    int sizes[] = { 500, 1000, 2000 };

    // Loop over each array size to test the 3Sum algorithm
    for (int size : sizes) {
        int* arr = new int[size]; // Dynamically allocate an array of the current size
        generateRandomArray(arr, size); // Fill the array with random integers

        // Measure the time taken by the 3Sum function
        auto start = std::chrono::high_resolution_clock::now(); // Start the timer
        int count = ThreeSum(arr, size); // Call the 3Sum function and store the result in `count`
        auto end = std::chrono::high_resolution_clock::now(); // Stop the timer

        // Calculate the duration of the 3Sum function in seconds
        std::chrono::duration<double> duration = end - start;

        // Output the results: the size of the array, the time taken, and the count of valid triples
        std::cout << "3Sum for n = " << size << " took " << duration.count() << " seconds." << std::endl;
        std::cout << "Count: " << count << std::endl;

        // Deallocate the dynamically allocated array to free up memory
        delete[] arr;
    }

    return 0; // Return 0 to indicate successful execution
}
