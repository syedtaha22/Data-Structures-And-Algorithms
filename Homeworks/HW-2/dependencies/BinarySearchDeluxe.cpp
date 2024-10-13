#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <cmath>

class BinarySearchDeluxe {
public:
    // Returns the index of the first key in the sorted array that is equal to the search key.
    template <typename Key>
    static int firstIndexOf(const std::vector<Key>& a, const Key& key, std::function<bool(const Key&, const Key&)> comparator) {
        if (a.empty()) throw std::invalid_argument("Array is empty"); // Throw exception if array is empty

        int lo = 0;
        int hi = a.size() - 1;
        int result = -1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (!comparator(a[mid], key) && !comparator(key, a[mid])) {
                result = mid;
                hi = mid - 1; // search in the left half to find the first occurrence
            }
            else if (comparator(a[mid], key)) {
                lo = mid + 1; // search right half
            }
            else {
                hi = mid - 1; // search left half
            }
        }
        return result;
    }

    // Returns the index of the last key in the sorted array that is equal to the search key.
    template <typename Key>
    static int lastIndexOf(const std::vector<Key>& a, const Key& key, std::function<bool(const Key&, const Key&)> comparator) {
        if (a.empty()) throw std::invalid_argument("Array is empty");

        int lo = 0;
        int hi = a.size() - 1;
        int result = -1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (!comparator(a[mid], key) && !comparator(key, a[mid])) {
                result = mid;
                lo = mid + 1; // search in the right half to find the last occurrence
            }
            else if (comparator(a[mid], key)) {
                lo = mid + 1; // search right half
            }
            else {
                hi = mid - 1; // search left half
            }
        }
        return result;
    }

    // Unit testing (required)
    static void test() {
        std::vector<int> sortedArray = { 1, 2, 2, 2, 3, 4, 5 };

        auto comparator = [](const int& a, const int& b) -> bool {
            return a < b;
            };

        // Test firstIndexOf
        std::cout << "First index of 2: " << firstIndexOf<int>(sortedArray, 2, comparator) << std::endl; // Expected: 1
        std::cout << "First index of 3: " << firstIndexOf<int>(sortedArray, 3, comparator) << std::endl; // Expected: 4
        std::cout << "First index of 5: " << firstIndexOf<int>(sortedArray, 5, comparator) << std::endl; // Expected: 6

        // Test lastIndexOf
        std::cout << "Last index of 2: " << lastIndexOf<int>(sortedArray, 2, comparator) << std::endl; // Expected: 3
        std::cout << "Last index of 3: " << lastIndexOf<int>(sortedArray, 3, comparator) << std::endl; // Expected: 4
        std::cout << "Last index of 5: " << lastIndexOf<int>(sortedArray, 5, comparator) << std::endl; // Expected: 6
    }
};

// int main() {
//     // Run unit test
//     BinarySearchDeluxe::test();
//     return 0;
// }
