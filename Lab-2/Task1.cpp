/*
    Task 2:
        Do the empirical analysis of resizing-array based stack and linked-list based stack.
            (a) Using the code provided in the lecture notes, implement the resizing-array based stack
                and linked-list based stack.
            (b) Write a test program that performs 1 million push operations. Calculate the worst-case
                and average time taken to perform a push operation.
*/

#include <iostream>
#include <chrono>
#include <limits>
#include <cmath>
#include "headers/linkedstackofstrings.hpp"
#include "headers/resizingarraystackofstrings.hpp"

// Number of push operations to perform during the test
const int NUM_OPERATIONS = 1000000;

// Template function to analyze the performance of push operations on a given stack type
template<typename StackType>
void analyzePushOperations(StackType& stack, const std::string& stackType) {
    long double totalTime = 0;  // Variable to accumulate total time taken for all push operations
    long double averageTime;  // Variable to store the average time per push operation

    long double worstcaseTime = std::numeric_limits<long double>::min();  // Variable to track the worst-case time
    int worstcasePush;  // Variable to store the index of the worst-case push operation

    long double worstTime = std::numeric_limits<long double>::min();  // Variable to store the longest time for a single push operation
    std::string worstString;  // Variable to store the worstTime string


    // Perform the push operations
    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        // Define test string with a unique value
        std::string testString = "test_string_" + std::to_string(i);

        auto start = std::chrono::high_resolution_clock::now(); // Start timing before the push operation
        stack.push(testString); // Perform the push operation with a unique string 
        auto end = std::chrono::high_resolution_clock::now(); // Stop timing after the push operation

        // Calculate the duration taken for this push operation
        std::chrono::duration<double> duration = end - start;
        double timeTaken = duration.count();

        // Accumulate the time taken
        totalTime += timeTaken;

        // Worst case push operation, Size of Stack is doubled
        if (i == pow(2, 19) + 1) {
            worstcasePush = i;
            worstcaseTime = timeTaken;
        }

        // Store the worst time and string
        if (timeTaken > worstTime) {
            worstTime = timeTaken;
            worstString = testString;
        }
    }

    // Calculate the average time per push operation
    averageTime = totalTime / NUM_OPERATIONS;

    // Output the analysis results for this stack type
    std::cout << stackType << " Stack Analysis:\n";
    std::cout << "\tTotal time for " << NUM_OPERATIONS << " push operations: " << totalTime << " seconds.\n";
    std::cout << "\tAverage time per push: " << averageTime << " seconds.\n";
    std::cout << "\tTime taken for worst case scenario: " << worstcaseTime << " seconds.\n";
    std::cout << "\tWorst-case push operation index: " << worstcasePush << std::endl;
    std::cout << "\tLongest time take for a single push operation: " << worstTime << " seconds, with string: " << worstString << "\n\n";
}

int main() {
    // Add newline for spacing
    std::cout << std::endl;

    // Create an instance of the resizing-array-based stack
    ResizingArrayStackOfStrings arrayStack;

    // Create an instance of the linked-list-based stack
    LinkedStackOfStrings linkedListStack;

    // Analyze the performance of the resizing-array-based stack
    analyzePushOperations(arrayStack, "Resizing-Array");

    // Analyze the performance of the linked-list-based stack
    analyzePushOperations(linkedListStack, "Linked-List");

    return 0; // End of program
}
