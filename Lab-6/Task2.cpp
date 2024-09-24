/*******************************************************************
    Task 2:
        Dynamic-median finding:
            Design a data type that supports insert in logarithmic time, find the median in
            constant time, and remove the median in logarithmic time.

            Hint:

            Keep the median key in v; use a max-oriented heap for keys less than the key of v;
            use a minoriented heap for keys greater than the key of v. To insert, add the new key
            into the appropriate heap, replace v with the key extracted from that heap.
 *******************************************************************/

#include <iostream>
#include <stdexcept>
#include <random>
#include <ctime>

 // Resizing Array Class
class ResizingArray {
private:
    // Array to store elements
    int* arr;
    // Capacity of the array
    int capacity;
    // Number of elements in the array
    int n;

    // Resize the array to the new capacity
    void resize(int newCapacity) {
        // Create a new array with the new capacity
        int* newArr = new int[newCapacity];

        for (int i = 0; i < n; i++) {
            // Copy the elements from the old array to the new array
            newArr[i] = arr[i];
        }
        // Delete the old array
        delete[] arr;
        // Update the array with the new array
        arr = newArr;
        // Update the capacity
        capacity = newCapacity;
    }

public:
    // Initialize the array with a default capacity of 2
    ResizingArray() : capacity(2), n(0) {
        // Create a new array with the default capacity
        arr = new int[capacity];
    }

    // Destructor to free the memory allocated for the array
    ~ResizingArray() { delete[] arr; }

    // Add a new element to the array
    void add(int value) {
        // If the array is full, resize it to double the capacity
        if (n == capacity) resize(2 * capacity);
        // Add the new element to the array
        arr[n++] = value;
    }

    // Remove the last element from the array
    int removeLast() {
        // If the array is empty, throw an exception
        if (n == 0) throw std::out_of_range("Array is empty");
        // Get the last element from the array
        int value = arr[--n];
        // Check if the array is less than 1/4 full, resize it to half the capacity
        if (n > 0 && n == capacity / 4) {
            resize(capacity / 2);
        }
        // Return the removed element
        return value;
    }

    // Get the number of elements in the array
    int size() { return n; }

    // Overload the [] operator to access elements in the array
    int& operator[](int index) {
        // If the index is out of range, throw an exception
        if (index < 0 || index >= n) {
            throw std::out_of_range("Index out of range");
        }
        // Return the element at the given index
        return arr[index];
    }
};

// Priority Queue Parent Class
class PriorityQueue {
protected:
    // Resizing Array to store elements
    ResizingArray pq;

    // Helper functions to get parent
    int parent(int k) { return (k - 1) / 2; }
    // Helper functions to get left child
    int leftChild(int k) { return 2 * k + 1; }
    // Helper functions to get right child
    int rightChild(int k) { return 2 * k + 2; }

    // Swim function to correct heap order from bottom to top
    void swim(int k) {
        // while index is not root and
        // the current element is not in it's correct position
        // based on the comparison function
        // swap the current element with the parent
        while (k > 0 && compare(pq[parent(k)], pq[k])) {
            std::swap(pq[parent(k)], pq[k]);
            k = parent(k);
        }
    }

    // Sink function to correct heap order from top to bottom
    void sink(int k) {
        // while the left child is less than the heap size
        while (leftChild(k) < pq.size()) {
            // Get the left child index
            int j = leftChild(k);
            // If the right child is less than the heap size and
            // the right child is higher priority than the left child
            // based on the comparison function
            // update the index to the right child
            if (rightChild(k) < pq.size() && compare(pq[j], pq[rightChild(k)])) {
                j = rightChild(k);
            }
            // If the current element is higher priority than the child
            // based on the comparison function
            // break
            if (!compare(pq[k], pq[j])) break;
            // Otherwise, swap the current element with the child
            std::swap(pq[k], pq[j]);
            // Update the current index
            k = j;
        }
    }

    // Pure virtual function to compare parent and child
    virtual bool compare(int parent, int child) = 0;
public:
    // Check if the heap is empty
    bool isEmpty() { return pq.size() == 0; }

    // Get the size of the heap
    int size() { return pq.size(); }

    // Insert a new element into the heap
    void insert(int value) {
        // Add the new element to the array
        pq.add(value);
        // Have it swim to it's correct position
        swim(pq.size() - 1);
    }

    int removeTop() {
        // If the heap is empty, throw an exception
        if (pq.size() == 0) {
            throw std::out_of_range("Heap is empty");
        }
        // Get the top element from the heap
        int top = pq[0];
        // Swap the top element with the last element
        pq[0] = pq.removeLast();
        // Have it sink to it's correct position
        sink(0);
        // Return the top element
        return top;
    }

    // Get the top element of the heap without removing it
    int top() {
        // If the heap is empty, throw an exception
        if (pq.size() == 0) {
            throw std::out_of_range("Heap is empty");
        }
        // Return the top element
        return pq[0];
    }
};

// Max Heap Child Class
class MaxHeap : public PriorityQueue {
protected:
    // Overriden compare function to compare parent and child
    bool compare(int parent, int child) override {
        // Return true if parent is less than child
        return parent < child;
    }
};

// Min Heap Child Class
class MinHeap : public PriorityQueue {
protected:
    // Overriden compare function to compare parent and child
    bool compare(int parent, int child) override {
        // Return true if parent is greater than child
        return parent > child;
    }
};

// 
class DynamicMedian {
private:
    // Max heap to store the smaller half of the elements
    MaxHeap maxHeap;
    // Min heap to store the greater half of the elements
    MinHeap minHeap;

public:
    // Constructor to initialize the median value
    // Initialize the median value to 0
    DynamicMedian() {}

    // Insert a new element into the heaps
    void insert(int value) {
        // If the max-heap is empty or the value is less than the top of the max-heap
        // insert the value into the max-heap
        if (maxHeap.isEmpty() || maxHeap.top() >= value) { maxHeap.insert(value); }
        // Otherwise, insert the value into the min-heap
        else minHeap.insert(value);

        // If the max-heap size is greater than the min-heap size by more than 1
        // Odd number of elements, move the top of the max-heap to the min-heap
        // to balance the heaps
        if (maxHeap.size() > minHeap.size() + 1) { minHeap.insert(maxHeap.removeTop()); }

        // if the min-heap size is greater than the max-heap size
        // Even number of elements, move the top of the min-heap to the max-heap
        // to ensure median is the top of the max-heap
        else if (minHeap.size() > maxHeap.size()) { maxHeap.insert(minHeap.removeTop()); }

    }

    // Get the median value
    float findMedian() {
        // If both heaps are empty, throw an exception
        if (maxHeap.isEmpty() && minHeap.isEmpty()) {
            throw std::runtime_error("No elements in the data structure.");
        }
        // If the heaps are of equal size, return the average of the top elements
        if (maxHeap.size() == minHeap.size()) {
            return (static_cast<float>(maxHeap.top()) + static_cast<float>(minHeap.top())) / 2.0f;
        }
        // Else the median is always the top of the max-heap
        return maxHeap.top();
    }

    bool isEmpty() { return maxHeap.isEmpty() && minHeap.isEmpty(); }

    // Remove the median Value:
    void removeMedian() {
        // If the heaps are empty, throw an exception
        if (maxHeap.isEmpty() && minHeap.isEmpty()) {
            throw std::runtime_error("No median to remove.");
        }
        // If the heaps are of equal size, remove the top elements from the min heap
        if (maxHeap.size() == minHeap.size()) {
            minHeap.removeTop();
        }
        // Else remove the top element from the max-heap, as 
        // it is always the median value
        else maxHeap.removeTop();
    }
};

int main() {
    srand(time(0));
    DynamicMedian dm;

    std::cout << "Inserting 10 random elements into the data structure" << std::endl;
    std::cout << "Elements: ";
    for (size_t i = 1; i <= 10; i++) {
        int random = rand() % 100 + 1; // [1, 100]
        dm.insert(random); // [1, 100]
        std::cout << random << " ";
    }
    std::cout << std::endl;


    std::cout << "Median: " << dm.findMedian() << std::endl;

    std::cout << "Removing the median..." << std::endl;
    dm.removeMedian();
    std::cout << "Median after removal: " << dm.findMedian() << std::endl;

    return 0;
}
