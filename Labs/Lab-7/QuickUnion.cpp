/*
    * Quick Union Implementation of Union-Find Data Structure
*/

#include <iostream>
#include <vector>

class QuickUnion {
private:
    std::vector<int> parent;  // parent[i] points to the parent of i, if parent[i] == i, i is a root
    std::vector<int> rank;    // rank[i] is the rank (or size) of the tree with root i

public:
    // Constructor: creates a Union-Find data structure with n elements (0 to n-1)
    QuickUnion(int n) {
        parent.resize(n);
        rank.resize(n, 1);  // Initially, all elements are in their own set and have rank 1
        for (int i = 0; i < n; i++) {
            parent[i] = i;  // Each element is its own root initially
        }
    }

    // Find the root of element p with path compression
    int find(int p) {
        if (p != parent[p]) {
            parent[p] = find(parent[p]);  // Path compression
        }
        return parent[p];
    }

    // Union the sets containing elements p and q
    void unionSets(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);

        if (rootP != rootQ) {
            // Union by rank: attach the smaller tree to the root of the larger tree
            if (rank[rootP] > rank[rootQ]) {
                parent[rootQ] = rootP;  // Root P becomes the parent of root Q
            }
            else if (rank[rootP] < rank[rootQ]) {
                parent[rootP] = rootQ;  // Root Q becomes the parent of root P
            }
            else {
                parent[rootQ] = rootP;  // Either can become the parent; increase the rank of root P
                rank[rootP]++;
            }
        }
    }

    // Check if elements p and q are in the same set
    bool connected(int p, int q) {
        return find(p) == find(q);
    }

    static void unitTest() {
        // Initialize a Union-Find data structure with 10 elements
        QuickUnion qu(10);
        qu.unionSets(4, 3);
        qu.unionSets(3, 8);
        qu.unionSets(6, 5);
        qu.unionSets(9, 4);
        qu.unionSets(2, 1);

        // Find parent of 8
        std::cout << "Parent of 8: " << qu.find(8) << std::endl;
        // Find parent of 9
        std::cout << "Parent of 9: " << qu.find(9) << std::endl;
        // Check if 8 and 9 are connected
        std::cout << "Connected(8, 9): " << qu.connected(8, 9) << std::endl;
        // Check if 5 and 4 are connected
        std::cout << "Connected(5, 4): " << qu.connected(5, 4) << std::endl;

        qu.unionSets(5, 0);
        qu.unionSets(7, 2);
        qu.unionSets(6, 1);

        // Get the parent of 0
        std::cout << "Parent of 0: " << qu.find(0) << std::endl;
        // Get the parent of 1
        std::cout << "Parent of 1: " << qu.find(1) << std::endl;
        // Check if 5 and 0 are connected
        std::cout << "Connected(5, 0): " << qu.connected(5, 0) << std::endl;
        // Check if 7 and 2 are connected
        std::cout << "Connected(7, 2): " << qu.connected(7, 2) << std::endl;
        // Check if 6 and 1 are connected
        std::cout << "Connected(6, 1): " << qu.connected(6, 1) << std::endl;
        // Check if 7 and 3 are connected
        std::cout << "Connected(7, 3): " << qu.connected(7, 3) << std::endl;

    }
};


// int main() {
//     QuickUnion::unitTest();
//     return 0;
// }