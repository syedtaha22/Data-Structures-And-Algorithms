/*
    Task 1:
    Throwing eggs from a building. Suppose that you have an N-story building and plenty of eggs. Suppose
    also that an egg is broken if it is thrown off from floor F or higher, and unbroken otherwise.
    We can use binary search to determine the value of F using ∼ lg N throws
    (the number of broken eggs is also ∼ lg N)

    Here we use a function object to simulate the process of throwing eggs from a building. The value of F
    is randomly chosen between 1 and N.

    ```cpp
        class EggDrop {
        public:
            EggDrop(int N) : F(std::random_device()() % N + 1) {}
            bool operator()(int x) {
                if (x >= F) return true;
                return false;
            }
        private:
            int F;
        };
        int main() {
            int N = 10000;
            EggDrop eggdrop(N);
            int lo = 1, hi = N;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (eggdrop(mid)) hi = mid;
                else lo = mid + 1;
            }
            std::cout << "The value of F is " << lo << std::endl;
            return 0;
        }
    ```

    Devise and implement a strategy to reduce the cost to ∼ 2 lg F when N is much larger than F.
    Hint: Probe at height 2^0, 2^1, 2^2, ..., 2^k, ... to find the value of k such that 2^k <= F < 2^(k+1).
    Then do a binary search between lo = 2k and hi = 2k+1.
*/

// Include the iostream and random headers
#include <iostream>
#include <random>

// Define a class EggDrop to simulate the process of throwing eggs from a building
class EggDrop {
public:
    // Constructor to initialize the value of F randomly between 1 and N
    EggDrop(int N) : F(std::random_device()() % N + 1) {}

    // Function call operator to simulate the egg drop process
    bool operator()(int x) {
        // If the height x is greater than or equal to F, return true (egg breaks)
        if (x >= F) return true;
        // Otherwise, return false (egg does not break)
        return false;
    }

    int getF() { return F; }

private:
    int F; // Private member variable to store the value of F
};


// Main function to test the EggDrop class and find the value of F
int main() {
    int N = 10000; // Number of floors in the building
    EggDrop eggdrop(N); // Create an instance of the EggDrop class with N floors

    // Probe at height 2^0, 2^1, 2^2, ..., 2^k, ... to find the value of k such that 2^k <= F < 2^(k+1)
    int k = 0;
    // Keep probing until the egg breaks
    while (eggdrop(1 << k) == false) {
        k++;
    }

    // 2^k >= F, which causes egg to break => eggdrop(2^k) = true
    // Reduce k by 1 to get 2^k < F
    k--;

    // Perform binary search between lo = 2^k and hi = 2^(k+1)
    int lo = 1 << k;
    int hi = 1 << (k + 1);

    // Binary search to find the value of F
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2; // Calculate the mid value
        if (eggdrop(mid)) hi = mid; // If egg breaks at height mid, set hi = mid
        else lo = mid + 1; // Otherwise, set lo = mid + 1
    }

    // Display the calculated and actual value of F
    std::cout << "The calculated value of F is " << lo << std::endl;
    std::cout << "The actual value of F is " << eggdrop.getF() << std::endl;

    // Return 0 to indicate successful completion of the program
    return 0;
}