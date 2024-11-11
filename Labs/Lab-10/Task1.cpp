/*
    Task 1:
        A sparse vector is a vector in which most of the elements are zero. To save space, we can store only the
        non-zero elements.

        Implement a sparse vector using a symbol table of index-value pairs so that the memory is proportional
        to the number of nonzeros. The set and get operations should take log(n) time in the worst case; taking
        the dot product of two vectors should take time proportional to the number of nonzero entries in both.
        Implement Svector class with the following methods:

        - void set(int i, double x): set the ith entry to x
        - double get(int i): return the ith entry
        - double dot(const Svector& that): return the dot product of this vector with that vector
        - double norm(): return the Euclidean norm ∥x∥ of the vector x, where ∥x∥ = √(x1^2 + x2^2 + ... + xn^2)
        - Svector add(const Svector& that): return the sum of this vector with that vector
        - void scale(double alpha): return the product of this vector with a scalar

        You may use std::unordered_map for the symbol table.
*/

#include <iostream>
#include <unordered_map>
#include <cmath>

class Svector {
    std::unordered_map<int, double> data;

public:
    // Set the value of i to x
    void set(const int& i, const double& x) {
        // If x is not zero, set the value of i to x
        if (x != 0.0) data[i] = x;
        else data.erase(i); // If x is zero, remove the value of i
    }

    // Get the value of i
    double get(const int& i) const {
        auto it = data.find(i);
        if (it != data.end()) {
            return it->second;
        }
        return 0.0; // If i is not found, return 0
    }

    // Calculate the dot product of this vector with that vector
    double dot(const Svector& that) const {
        double product = 0; // Initialize the product to 0
        for (auto& [key, value] : data) {
            product += value * that.get(key); // Add the product of the values of this vector and that vector
        }
        return product; // Return the product
    }

    // Calculate the Euclidean norm of the vector
    double norm() const {
        double e_norm = 0; // Initialize the euclidean norm to 0
        for (const auto& [key, value] : data) {
            e_norm += value * value; // Add the square of the value to the euclidean norm
        }
        return std::sqrt(e_norm); // Return the square root of the euclidean norm
    }

    // Add this vector with that vector
    Svector add(const Svector& that) const {
        Svector result; // Create a new vector to store the result
        for (auto& [key, value] : data) {
            result.set(key, value); // Copy the values of this vector to the result
        }
        for (auto& [key, value] : that.data) {
            result.set(key, result.get(key) + value); // Add the values of that vector to the result
        }
        return result; // Return the result
    }

    // Scale the vector by alpha
    void scale(const double& alpha) {
        for (auto& [key, value] : data) {
            data[key] = value * alpha;
        }
    }

    // Print the vector
    void print() const {
        for (const auto& [key, value] : data) {
            std::cout << key << ": " << value << std::endl;
        }
    }
};

// Example usage - code from ChatGPT
int main() {
    Svector vec1;
    vec1.set(1, 3.5);
    vec1.set(3, 4.0);
    vec1.set(5, 2.2);

    Svector vec2;
    vec2.set(1, 1.5);
    vec2.set(2, 4.5);
    vec2.set(3, 0.0); // This will not be stored

    std::cout << "Vector 1:" << std::endl;
    vec1.print();

    std::cout << "Vector 2:" << std::endl;
    vec2.print();

    std::cout << "Dot product: " << vec1.dot(vec2) << std::endl;
    std::cout << "Norm of vector 1: " << vec1.norm() << std::endl;

    Svector sum = vec1.add(vec2);
    std::cout << "Sum of vector 1 and vector 2:" << std::endl;
    sum.print();

    vec1.scale(2.0);
    std::cout << "Vector 1 after scaling by 2:" << std::endl;
    vec1.print();

    return 0;
}