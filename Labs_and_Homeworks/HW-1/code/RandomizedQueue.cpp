/*
    Randomized queue:
        A randomized queue is similar to a stack or queue, except that the item removed is chosen
        uniformly at random among items in the collection. Create a generic data type RandomizedQueue
        that implements the following API:

            ```cpp
            template<typename Item>
            class RandomizedQueue {
            public:
                // construct an empty randomized queue
                RandomizedQueue();
                // deallocate memory
                ~RandomizedQueue();
                // is the randomized queue empty?
                bool empty() const;
                // return the number of items on the randomized queue
                int size() const;
                // add the item
                void enqueue(const Item& item);
                // remove and return a random item
                Item dequeue();
                // return a random item (but do not remove it)
                Item sample();
                // unit testing (required)
                static void unit_test();
            };
            ```

        Corner cases:
            Throw a std::runtime_error if the client calls either sample() or dequeue() whem the
            randomized queue is empty.

        Unit testing:
            Your RandomizedQueue::unit_test() method must call directly every public constructor
            and method to help verify that they work as prescribed (e.g., by printing results to standard output).

        Performance requirements:
            Your implementation must achieve the following worst-case performance requirements:
                -   A randomized queue containing n items must use at most 16n bytes of memory, not including the
                    memory for the items themselves.
                -   Each randomized queue operation must take constant amortized time. That is, starting from an
                    empty randomized queue, any intermixed sequence of m such operations must take Θ(m) time in
                    the worst case.
*/

#include <iostream>
// Include the <stdexcept> header to use std::runtime_error
#include <stdexcept> 
// Include the <random> header to use std::random_device, std::mt19937, std::uniform_int_distribution
#include <random> 


// RandomizedQueue class template
template<typename Item>
class RandomizedQueue {
private:
    Item* data;       // dynamically allocated array for storing items
    int capacity;     // total capacity of the data array
    int count;        // current number of items in the queue

    // Helper function to resize the array when necessary
    void resize(int new_capacity) {
        // Allocate a new array with the new capacity
        Item* new_data = new Item[new_capacity];
        // Copy the items from the old array to the new array
        for (int i = 0; i < count; ++i) {
            new_data[i] = data[i];
        }

        delete[] data; // Delete the old array
        data = new_data; // Update the data array
        capacity = new_capacity; // Update the capacity
    }

    // Helper function to generate a random index
    int random_index() const {
        // Throw an error if the queue is empty
        if (count == 0) throw std::runtime_error("RandomizedQueue is empty");

        // Use std::random_device to generate a random seed
        std::random_device rd;
        // Use std::mt19937 as the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis(0, count - 1); // Uniform distribution from 0 to count - 1
        return dis(gen); // Return a random index
    }

public:
    // Construct an empty randomized queue
    RandomizedQueue() : data(nullptr), capacity(0), count(0) {
        resize(2); // start with a small capacity
    }

    // Deallocate memory
    ~RandomizedQueue() { delete[] data; }

    // Is the randomized queue empty?
    bool empty() const { return count == 0; }

    // Return the number of items in the randomized queue
    int size() const { return count; }

    // Add the item
    void enqueue(const Item& item) {
        // If the array is full, resize it
        if (count == capacity) {
            resize(2 * capacity); // double the capacity when full
        }
        data[count++] = item; // add the item and increment count
    }

    // Remove and return a random item
    Item dequeue() {
        // Throw an error if the queue is empty
        if (empty()) {
            throw std::runtime_error("Cannot dequeue from an empty queue");
        }
        // Get a random index
        int rand_index = random_index();
        // Get the item at the random index
        Item item = data[rand_index];
        // Move the last item to the random index
        data[rand_index] = data[--count]; // fill the gap with the last item
        if (count > 0 && count == capacity / 4) {
            resize(capacity / 2); // shrink the array if necessary
        }
        return item;
    }

    // Return a random item (but do not remove it)
    Item sample() const {
        // Throw an error if the queue is empty
        if (empty()) {
            throw std::runtime_error("Cannot sample from an empty queue");
        }
        // Get a random index 
        // and return the item at that index
        return data[random_index()];
    }

    // Unit testing (required)
    static void unit_test() {
        // Create a RandomizedQueue of integers
        RandomizedQueue<int> rq;


        std::cout << "Enqueue 1, 2, 3, 4..." << std::endl;
        rq.enqueue(1); // 1
        rq.enqueue(2); // 1 2
        rq.enqueue(3); // 1 2 3
        rq.enqueue(4); // 1 2 3 4

        // Current RandomizedQueue: 1 2 3 4

        // Test sample()
        // Should return a random item
        std::cout << "Random sample: " << rq.sample() << std::endl;

        // Test size()
        // Should return the number of items in the queue i.e. 4
        std::cout << "Size: " << rq.size() << std::endl;

        // Test dequeue()
        // Should remove and return a random item
        std::cout << "Dequeue random item: " << rq.dequeue() << std::endl;

        // Test size() after dequeue
        // Should return the number of items in the queue i.e. 3
        std::cout << "Size after dequeue: " << rq.size() << std::endl;

        // Test enqueue()
        std::cout << "Enqueue 5, 6..." << std::endl;

        // Assuming that 1 was dequeued
        rq.enqueue(5); // 2 3 4 5 
        rq.enqueue(6); // 2 3 4 5 6

        // Get another randome sample
        std::cout << "Random sample: " << rq.sample() << std::endl;
        // Check the Size
        // Should be 5
        std::cout << "Size: " << rq.size() << std::endl;

        // Dequeue all items
        std::cout << "Dequeue random items until empty..." << std::endl;
        // Dequeue all items
        while (!rq.empty()) {
            std::cout << "Dequeued: " << rq.dequeue() << std::endl;
        }

        // Test exception handling
        // Deque is Empty, So it should throw an exception
        try {
            rq.dequeue(); // Should throw an error
        }
        catch (const std::runtime_error& e) {
            std::cout << "Caught expected exception: " << e.what() << std::endl;
        }

        // Try Sampling Empty Queue
        // Should throw an exception
        try {
            rq.sample(); // Should throw an error
        }
        catch (const std::runtime_error& e) {
            std::cout << "Caught expected exception: " << e.what() << std::endl;
        }

        // Expected output:
        // Enqueue 1, 2, 3, 4...
        // Random sample: 3 (or any random number)
        // Size: 4
        // Dequeue random item: 2 (or any random number)
        // Size after dequeue: 3
        // Enqueue 5, 6...
        // Random sample: 5 (or any random number)
        // Size: 5
        // Dequeue random items until empty...
        // Dequeued: 3 (or any random number)
        // Dequeued: 4 (or any random number)
        // Dequeued: 5 (or any random number)
        // Dequeued: 6 (or any random number)
        // Dequeued: 1 (or any random number)
        // Caught expected exception: RandomizedQueue is empty
        // Caught expected exception: RandomizedQueue is empty
    }
};


// Commented out to avoid conflicts with other files using RandomizedQueue

// int main() {
//     // Call the unit_test() method of RandomizedQueue
//     RandomizedQueue<int>::unit_test();
//     return 0;
// }
