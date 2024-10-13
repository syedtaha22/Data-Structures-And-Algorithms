#include <iostream>
#include <vector>
#include <stdexcept>
#include "QuickUnion.cpp" 

class Percolation {
private:

    int n; // Variable to store the size of the grid
    int openSiteCount; // Variable to store the number of open sites

    int topVirtual; // Variable to store the index of the virtual site at the top
    int bottomVirtual; // Variable to store the index of the virtual site at the bottom


    std::vector<std::vector<bool>> grid;  // 2D vector to store the grid of sites
    QuickUnion qu;  // For quick union-find operations
    QuickUnion quFull;  // Additional structure to avoid backwash issues

    // Convert 2D coordinates to a single index
    int getIndex(int row, int col) const {
        return row * n + col;
    }

    // Check if the given coordinates are valid
    void validate(int row, int col) const {
        // If the coordinates are out of bounds,
        if (row < 0 || row >= n || col < 0 || col >= n) {
            // Throw an exception.
            throw std::invalid_argument("Index out of bounds");
        }
    }

public:
    // Constructor: initializes an n-by-n grid, with all sites blocked
    // and creates the UnionFind data structure of size n*n + 2
    // n(n) => n = n
    // openSiteCount(0) => openSiteCount = 0
    // grid(n, std::vector<bool>(n, false)) => grid = n x n grid with all sites blocked(false)
    // uf(n* n + 2) => uf = UnionFind data structure of size n*n + 2
    // ufFull(n* n + 1) => ufFull = UnionFind data structure of size n*n + 1
    // topVirtual(n* n) => topVirtual = n*n
    // bottomVirtual(n* n + 1) => bottomVirtual = n*n + 1
    Percolation(int n) : n(n), openSiteCount(0), grid(n, std::vector<bool>(n, false)),
        qu(n* n + 2), quFull(n* n + 1), topVirtual(n* n), bottomVirtual(n* n + 1) {

        // If n is less than or equal to 0,
        if (n <= 0) {
            // Throw an exception.
            throw std::invalid_argument("Grid size must be greater than 0");
        }
    }

    // Opens the site (row, col) if it is not open already
    void open(int row, int col) {
        validate(row, col);

        if (isOpen(row, col)) return;  // Already open, do nothing

        // Open the site and increment the count
        grid[row][col] = true;
        openSiteCount++;


        // Get the index of the site
        int index = getIndex(row, col);

        // Connect with virtual top and bottom if in first or last row
        if (row == 0) {
            qu.unionSets(index, topVirtual);
            quFull.unionSets(index, topVirtual);
        }
        if (row == n - 1) {
            qu.unionSets(index, bottomVirtual);
        }

        // Connect to neighboring open sites (up, down, left, right)
        if (row > 0 && isOpen(row - 1, col)) {  // up
            qu.unionSets(index, getIndex(row - 1, col));
            quFull.unionSets(index, getIndex(row - 1, col));
        }
        if (row < n - 1 && isOpen(row + 1, col)) {  // down
            qu.unionSets(index, getIndex(row + 1, col));
            quFull.unionSets(index, getIndex(row + 1, col));
        }
        if (col > 0 && isOpen(row, col - 1)) {  // left
            qu.unionSets(index, getIndex(row, col - 1));
            quFull.unionSets(index, getIndex(row, col - 1));
        }
        if (col < n - 1 && isOpen(row, col + 1)) {  // right
            qu.unionSets(index, getIndex(row, col + 1));
            quFull.unionSets(index, getIndex(row, col + 1));
        }
    }

    // Is the site (row, col) open?
    bool isOpen(int row, int col) const {
        validate(row, col);
        return grid[row][col];
    }

    // Is the site (row, col) full (i.e., connected to the top)?
    bool isFull(int row, int col) {
        validate(row, col);
        return quFull.connected(getIndex(row, col), topVirtual);
    }

    // Returns the number of open sites
    int numberOfOpenSites() const {
        return openSiteCount;
    }

    // Does the system percolate?
    bool percolates() {
        return qu.connected(topVirtual, bottomVirtual);
    }

    // Unit testing (required)
    static void test() {
        // Create a Percolation object with size 3
        Percolation perc(3);
        // Open the sites (0, 0), (1, 0), and (2, 0)
        perc.open(0, 0);
        perc.open(1, 0);
        perc.open(2, 0);

        // Check if the system percolates
        std::cout << "Percolates: " << (perc.percolates() ? "Yes" : "No") << std::endl;
        // Check the number of open sites
        std::cout << "Number of open sites: " << perc.numberOfOpenSites() << std::endl;
        // Check if (2, 0) is full
        std::cout << "Is (2, 0) full: " << (perc.isFull(2, 0) ? "Yes" : "No") << std::endl;
    }
};


int main() {
    Percolation::test();
    return 0;
}