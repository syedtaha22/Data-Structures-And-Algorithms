/*
    Task 1: Set implementation using ordered-array.

        Implement the set data type using an ordered array. That is, you maintain the N keys in the set in
        ascending order in an array.

        Implement the following operations with the specified time complexity:

        add(key)       -  add the key to the set             -  O(N)
        contains(key)  -  is the key in the set?             -  O(log N)
        ceiling(key)   -  smallest key in set ≥ given key    -  O(log N)
        rank(key)      -  number of keys in set < given key  -  O(log N)
        select(i)      -  ith largest key in the set         -  O(1)
        min()          -  minimum key in the set             -  O(1)
        delete(key)    -  delete the given key from the set  -  O(N)
*/


#include <iostream>
#include <vector>

class OrderedSet {
private:
    // Vector to store the keys in ascending order
    std::vector<int> arr;

    // Binary search to find the position of the key or where it should be inserted
    // Returns the position where the key is or should be inserted
    int binarySearch(int key, bool& found) {
        int left = 0, right = arr.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == key) {
                found = true;
                return mid; // Key found, return its position
            }
            if (arr[mid] < key) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        found = false;
        return left; // Return insertion position if key not found
    }

public:
    // Add the key to the set O(N)
    void add(int key) {
        // If the array is empty, add the key and return
        if (arr.empty()) {
            arr.push_back(key);
            return;
        }

        // Use binarySearch to check if the key is already in the set
        bool found = false;
        int pos = binarySearch(key, found); // O(log N)

        if (found) return; // Key is already present, so no need to add

        // Manually shift elements to insert the key - O(N)
        arr.push_back(0); // Increase size by 1
        for (int i = arr.size() - 1; i > pos; i--) {
            arr[i] = arr[i - 1]; // Shift elements to the right
        }
        arr[pos] = key; // Insert key at the correct position
    }

    // Check if the key is in the set O(log N)
    bool contains(int key) {
        bool found = false;
        binarySearch(key, found); // O(log N)
        return found;
    }

    // Find the smallest key >= given key O(log N)
    int ceiling(int key) {
        bool found = false;
        int pos = binarySearch(key, found); // O(log N)

        // If the key is found, return it
        if (found) return arr[pos];

        // If the insertion point is within bounds, return the next key
        return pos < arr.size() ? arr[pos] : -1; // -1 if no ceiling exists
    }

    // Return the number of keys less than the given key O(log N)
    int rank(int key) {
        bool found = false;
        int pos = binarySearch(key, found); // O(log N)
        return pos; // The position is the number of elements less than the key
    }

    // Select the ith largest key O(1)
    int select(int i) {
        if (i >= 0 && i < arr.size()) {
            return arr[i];
        }
        return -1; // Invalid index
    }

    // Get the minimum key O(1)
    int min() {
        return arr.empty() ? -1 : arr[0];
    }

    // Delete the given key from the set O(N)
    void deleteKey(int key) {
        bool found = false;
        int pos = binarySearch(key, found); // O(log N)

        if (!found) return; // Key not found

        // Manually shift elements to delete the key - O(N)
        for (int j = pos; j < arr.size() - 1; j++) {
            arr[j] = arr[j + 1]; // Shift elements to the left
        }
        arr.pop_back(); // Remove last element as it has been shifted
    }

    // Unit Test
    static void unitTest() {
        // Declare and initialize the ordered set
        OrderedSet os;
        os.add(5); os.add(3); // 3, 5
        os.add(8); os.add(1); // 1, 3, 5, 8
        os.add(7); os.add(5); // 1, 3, 5, 7, 8

        std::cout << "Contains 3? " << os.contains(3) << "\n"; // 1 (true)
        std::cout << "Ceiling of 4: " << os.ceiling(4) << "\n"; // 5
        std::cout << "Rank of 7: " << os.rank(7) << "\n"; // 3
        std::cout << "Select 2nd element: " << os.select(2) << "\n"; // 5
        std::cout << "Min element: " << os.min() << "\n"; // 1

        os.deleteKey(5);
        std::cout << "Contains 5 after deletion? " << os.contains(5) << "\n"; // 0 (false)
    }
};

int main() {
    OrderedSet::unitTest(); // Run the unit test
    return 0;
}
