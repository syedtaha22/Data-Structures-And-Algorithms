#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <stdexcept>
#include "Percolation.cpp"  // Percolation class
#include <chrono>  // For timing

class PercolationStats {
private:
    int n;            // Size of the grid (n-by-n)
    int trials;       // Number of independent trials
    std::vector<double> thresholds;  // Stores the percolation threshold for each trial

    // Helper function to perform a single trial
    double runTrial() {
        // Initilise an n-by-n grid for percolation
        Percolation perc(n);

        // Random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, n - 1);

        // While the system does not percoclate,
        while (!perc.percolates()) {
            // Get a random site
            int row = dis(gen);
            int col = dis(gen);

            // If the site is not open,
            if (!perc.isOpen(row, col)) {
                // open the site
                perc.open(row, col);
            }
        }

        // Return the fraction of open sites to the total number of sites
        return static_cast<double>(perc.numberOfOpenSites()) / (n * n);
    }

public:
    // Constructor: performs 'trials' independent trials on an n-by-n grid
    PercolationStats(int n, int trials) : n(n), trials(trials), thresholds(trials) {
        // Throw an exception if the grid size or number of trials is invalid(<=0)
        if (n <= 0 || trials <= 0) {
            throw std::invalid_argument("Grid size and number of trials must be greater than 0");
        }


        // Run the trials and store the thresholds
        for (int i = 0; i < trials; ++i) {
            thresholds[i] = runTrial();
        }
    }

    // Returns the sample mean of percolation thresholds
    double mean() const {
        double sum = 0.0;
        for (const auto& threshold : thresholds) {
            sum += threshold;
        }
        return sum / trials;
    }

    // Returns the sample standard deviation of percolation thresholds
    double stddev() const {
        // Get the mean
        double avg = mean();
        // Calculate the sum of squared differences
        double sumSquaredDiffs = 0.0;
        for (const auto& threshold : thresholds) {
            sumSquaredDiffs += (threshold - avg) * (threshold - avg);
        }
        // Return the square root of the average
        return std::sqrt(sumSquaredDiffs / (trials - 1));
    }

    // Returns the low endpoint of the 95% confidence interval
    double confidenceLow() const {
        // 1.96 is the z-score for a 95% confidence interval
        return mean() - (1.96 * stddev() / std::sqrt(trials));
    }

    // Returns the high endpoint of the 95% confidence interval
    double confidenceHigh() const {
        // 1.96 is the z-score for a 95% confidence interval
        return mean() + (1.96 * stddev() / std::sqrt(trials));
    }

    // Unit testing
    static void test() {
        int n = 20;  // Grid size
        int trials = 100;  // Number of trials
        PercolationStats stats(n, trials);

        std::cout << "mean() = " << stats.mean() << std::endl;
        std::cout << "stddev() = " << stats.stddev() << std::endl;
        std::cout << "confidenceLow() = " << stats.confidenceLow() << std::endl;
        std::cout << "confidenceHigh() = " << stats.confidenceHigh() << std::endl;
    }
};

int main(int argc, char* argv[]) {
    // Check if the number of arguments is correct
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <grid size> <number of trials>\n";
        return 1;
    }


    int n = std::stoi(argv[1]); // Grid size
    int trials = std::stoi(argv[2]); // Number of trials

    auto start = std::chrono::high_resolution_clock::now(); // Start the timer
    PercolationStats stats(n, trials); // Run the trials
    auto end = std::chrono::high_resolution_clock::now(); // Stop the timer
    std::chrono::duration<double> duration = end - start; // Calculate the duration 

    std::cout << "mean() = " << stats.mean() << std::endl;
    std::cout << "stddev() = " << stats.stddev() << std::endl;
    std::cout << "confidenceLow() = " << stats.confidenceLow() << std::endl;
    std::cout << "confidenceHigh() = " << stats.confidenceHigh() << std::endl;
    std::cout << "elapsed time = " << duration.count() << std::endl;

    // Return 0 to indicate success
    return 0;
}