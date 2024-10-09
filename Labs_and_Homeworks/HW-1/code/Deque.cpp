/*

    Dequeue:
        A double-ended queue or deque (pronounced "deck") is a generalization of a stack and a queue
        that supports adding and removing items from either the front or the back of the collection. Create a
        generic data type Deque that implements the following API:

        ```cpp
        template <typename Item>
        class Deque {
        public:
            // Construct an empty deque
            Deque();
            // Deallocate memory
            ~Deque();
            // Is the deque empty?
            bool empty() const;
            // Return the number of items on the deque
            int size() const;
            // Add the item to the front
            void push_front(const Item& item);
            // Add the item to the back
            void push_back(const Item& item);
            // Remove and return the item from the front
            Item pop_front();
            // Remove and return the item from the back
            Item pop_back();
            // unit testing
            static void unit_test();
        };
        ```

        Corner cases:
            Throw a std::runtime_error if the client calls either pop_front or pop_back when
            the deque is empty.

        Unit testing:
            Your Dequeue::unit_test() method must call directly every public constructor and
            method to help verify that they work as prescribed (e.g., by printing results to standard output).

        Performance requirements:
            Your implementation must achieve the following worst-case performance
            requirements:
                1) A deque containing n items must use at most 16n bytes of memory, not including the memory for
                the items themselves.
                2) Each deque operation (including construction) must take constant time.
*/



#include <iostream>
// Include the <stdexcept> header to use std::runtime_error
#include <stdexcept>

// Deque class template
template <typename dataType>
class Deque {
private:
    // Node structure for doubly linked list
    struct Node {
        dataType data; // Data of the node
        Node* next; // Pointer to the next node
        Node* prev; // Pointer to the previous node
        // Node constructor
        Node(const dataType& item) : data(item), next(nullptr), prev(nullptr) {}
    };

    Node* head;  // Pointer to the first node (front)
    Node* tail;  // Pointer to the last node (back)
    int count;   // Number of items in the deque

public:
    // Construct an empty deque
    Deque() : head(nullptr), tail(nullptr), count(0) {}

    // Deallocate memory
    ~Deque() {
        // While head is not nullptr, delete the node and move to the next node
        while (head != nullptr) {
            // Store the current head node
            Node* temp = head;
            // Move head to the next node
            head = head->next;
            // Delete the current node
            delete temp;
        }
    }

    // Is the deque empty?
    bool empty() const {
        // If count is 0, the deque is empty
        return count == 0;
    }

    // Return the number of items on the deque
    int size() const {
        // Return the count
        return count;
    }

    // Add the item to the front
    void push_front(const dataType& item) {
        // Create a new node with the item
        Node* new_node = new Node(item);
        // If the deque is empty
        if (empty()) {
            // Set head and tail to the new node
            head = tail = new_node;
        }
        // Otherwise
        else {
            // Set the new node's next to head
            new_node->next = head;
            // Set head's previous to the new node
            head->prev = new_node;
            // Set head to the new node
            head = new_node;
        }
        // Increment the count
        ++count;
    }

    // Add the item to the back
    void push_back(const dataType& item) {
        // Create a new node with the item
        Node* new_node = new Node(item);
        // If the deque is empty
        if (empty()) {
            // Set head and tail to the new node
            head = tail = new_node;
        }
        // Otherwise
        else {
            // Set the new node's previous to tail
            new_node->prev = tail;
            // Set tail's next to the new node
            tail->next = new_node;
            // Set tail to the new node
            tail = new_node;
        }
        // Increment the count
        ++count;
    }

    // Remove and return the item from the front
    dataType pop_front() {
        // If the deque is empty, throw an exception
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }
        // Store the old head node
        Node* old_head = head;
        // Store the data of the old head node
        dataType item = old_head->data;
        // Move head to the next node
        head = head->next;
        // If head is not nullptr
        if (head != nullptr) {
            // Set head's previous to nullptr
            head->prev = nullptr;
        }
        // Otherwise
        else {
            // Set tail to nullptr (If the deque is now empty)
            tail = nullptr;
        }
        // Delete the old head node
        delete old_head;
        // Decrement the count
        --count;
        // Return the data of the old head node
        return item;
    }

    // Remove and return the item from the back
    dataType pop_back() {
        // If the deque is empty, throw an exception
        if (empty()) {
            throw std::runtime_error("Deque is empty");
        }
        // Store the old tail node
        Node* old_tail = tail;
        // Store the data of the old tail node
        dataType item = old_tail->data;
        // Move tail to the previous node
        tail = tail->prev;
        // If tail is not nullptr
        if (tail != nullptr) {
            // Set tail's next to nullptr
            tail->next = nullptr;
        }
        // Otherwise
        else {
            // Set head to nullptr (If the deque is now empty)
            head = nullptr;
        }
        // Delete the old tail node
        delete old_tail;
        // Decrement the count
        --count;
        // Return the data of the old tail node
        return item;
    }

    // Unit testing
    static void unit_test() {
        // Create a deque of integers
        Deque<int> deque;

        // Test empty()
        std::cout << "Is empty? " << (deque.empty() ? "Yes" : "No") << std::endl;

        // Test push_front() and push_back()
        deque.push_front(10); // 10
        deque.push_back(20); // 10 20
        deque.push_front(5); // 5 10 20

        // Current Deque: 5 10 20

        // Test size()
        std::cout << "Size after 3 pushes: " << deque.size() << std::endl;

        // Test pop_front() and pop_back()
        std::cout << "Pop front: " << deque.pop_front() << std::endl; // 10 20
        std::cout << "Pop back: " << deque.pop_back() << std::endl; // 10
        // Test size()
        std::cout << "Size after 2 pops: " << deque.size() << std::endl;

        // Test push_back() and pop_front()
        deque.push_back(30); // 10 30
        std::cout << "Pop front: " << deque.pop_front() << std::endl; // 30
        std::cout << "Is empty? " << (deque.empty() ? "Yes" : "No") << std::endl; // No

        // Pop 30 to empty the deque
        std::cout << "Pop back: " << deque.pop_back() << std::endl; // empty
        std::cout << "Is empty? " << (deque.empty() ? "Yes" : "No") << std::endl; // Yes

        // Test exception
        try {
            deque.pop_front();  // Should throw exception
        }
        catch (const std::runtime_error& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }

        /*
            Expected output:
                Is empty? Yes
                Size after 3 pushes: 3
                Pop front: 5
                Pop back: 20
                Size after 2 pops: 1
                Pop front: 10
                Is empty? No
                Pop back: 30
                Is empty? Yes
                Caught exception: Deque is empty
        */
    }
};

// Commented out to avoid conflicts with other files using the Deque class
// Uncomment the following line to test the Deque class

// int main() {
//     Deque<int>::unit_test();
//     return 0;
// }
