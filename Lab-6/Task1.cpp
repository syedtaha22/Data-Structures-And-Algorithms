/**********************************************
    Task 1:

    - Print out all integers of the form a^3 + b^3
      where a and b are integers between 0 and n in sorted order,
      without using excessive space.

    - Instead of computing an array of the n^2 sums and sorting them,
      build a minimum-oriented priority queue, initially containing:

      (0^3 + 0^3, 0, 0), (1^3 + 1^3, 1, 1), ..., (n^3 + n^3, n, n).

    - While the priority queue is nonempty, remove the smallest item
      (i^3 + j^3, i, j), print it, and then, if j < n, insert the item
      (i^3 + (j + 1)^3, i, j + 1).

    - Find all distinct integers a, b, c, and d between 0 and 10^6
      such that a^3 + b^3 = c^3 + d^3.

      Example: 1729 = 9^3 + 10^3 = 1^3 + 12^3.
***********************************************/

#include <iostream>
#include <vector>
#include <unordered_map> 

// Priority Queue Class
class MinPriorityQueue {
private:
    // Heap to store elements
    // Tuple: (i³ + j³, i, j)
    std::vector<std::tuple<long long, int, int>> heap;

    // Swim function to correct heap order from bottom to top
    void swim(int k) {
        // while index is not root
        while (k > 0) {
            // if the current element is smaller than the parent, swap them
            // Compared with the first element of the tuple i.e. i³ + j³ (Sum)
            if (get<0>(heap[k]) < get<0>(heap[(k - 1) / 2])) {
                swap(heap[k], heap[(k - 1) / 2]);
                k = (k - 1) / 2;
            }
            // Otherwise, break
            else break;
        }
    }

    // Sink function to correct heap order from top to bottom
    void sink(int k) {
        // Get the heap size
        int size = heap.size();

        // While the current element is not in it's correct position
        while (true) {
            // Get the smallest element index
            int smallest = k;
            // Get the left child index
            int leftChild = 2 * k + 1; // Left child index = 2 * parent index + 1 (0-based index)
            // Get the right child index
            int rightChild = 2 * k + 2; // Right child index = 2 * parent index + 2 (0-based index)

            // If the left child is smaller than the parent, update the smallest index
            if (leftChild < size && get<0>(heap[leftChild]) < get<0>(heap[smallest])) {
                smallest = leftChild;
            }
            // If the right child is smaller than the parent, update the smallest index
            if (rightChild < size && get<0>(heap[rightChild]) < get<0>(heap[smallest])) {
                smallest = rightChild;
            }

            // If smallest is not the parent, swap the parent with the smallest child
            if (smallest != k) {
                swap(heap[k], heap[smallest]);
                k = smallest; // Update the current index
            }
            // If the smallest does not change it means the current element is in it's
            // correct position we can break
            else break;
        }
    }

public:
    // Check if the heap is empty
    bool isEmpty() const { return heap.empty(); }

    // Insert an element into the heap
    void insert(std::tuple<long long, int, int> element) {
        // Insert the element at the end of the heap
        heap.push_back(element);
        // Have it swim to it's correct position
        swim(heap.size() - 1);
    }

    // Extract the minimum element from the heap
    std::tuple<long long, int, int> extractMin() {
        // minElement is the first element of the heap
        std::tuple<long long, int, int> minElement = heap[0];
        // Swap the first element with the last element
        heap[0] = heap.back();
        // Remove the last element (min element)
        heap.pop_back();
        // Sink the first element to it's correct position
        sink(0);
        // Return the minimum element
        return minElement;
    }
};

int main() {
    int n = 100; // Upper limit for i and j
    MinPriorityQueue pq;

    // Insert initial values: (i^3 + i^3, i, i)
    for (int i = 0; i <= n; ++i) {
        pq.insert(std::make_tuple(static_cast<long long>(i) * i * i + i * i * i, i, i));
    }

    // Use a map to find distinct (a^3 + b^3 = c^3 + d^3)
    // Map: <sum, vector of pairs (a, b)>
    // Basically we will map the sum to a list of (i, j) pairs for which i^3 + j^3 = sum
    // We can then print out this list if it has more than 1 pair
    std::unordered_map<long long, std::vector<std::pair<int, int>>> seen;

    // Counter for unique sums
    int uniqueCount = 0;

    // Process the priority queue
    while (!pq.isEmpty()) {
        // Get the minimum element from the priority queue
        auto current = pq.extractMin();
        // Get the sum, i, j from the tuple
        long long sum = get<0>(current);
        int i = get<1>(current);
        int j = get<2>(current);

        // Insert the sum into the map
        seen[sum].emplace_back(i, j);


        // If j < n, insert the next (i^3 + (j+1)^3, i, j+1)
        if (j < n) {
            pq.insert(std::make_tuple(static_cast<long long>(i) * i * i + (j + 1) * (j + 1) * (j + 1), i, j + 1));
        }

        // If the sum has multiple pairs, print all distinct (a^3 + b^3 = c^3 + d^3)
        if (seen[sum].size() > 1) {
            for (auto& pair1 : seen[sum]) {
                for (auto& pair2 : seen[sum]) {
                    // Only print if pair1 is lexicographically smaller than pair2
                    if (pair1 < pair2) {
                        std::cout << sum << " = " << pair1.first << "^3 + " << pair1.second
                            << "^3 = " << pair2.first << "^3 + " << pair2.second << "^3\n";
                        uniqueCount++; // Increment unique count for each unique pair found
                    }
                }
            }
        }
    }

    // Print the total number of unique pairs found
    std::cout << "Total unique pairs found: " << uniqueCount << std::endl;


    return 0;
}
