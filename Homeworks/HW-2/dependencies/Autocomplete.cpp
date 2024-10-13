#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Term.cpp"  // Assumes Term class is implemented in Term.cpp
#include "BinarySearchDeluxe.cpp"  // Assumes BinarySearchDeluxe is implemented

class Autocomplete {
private:
    std::vector<Term> terms;

public:
    // Initializes the data structure from the given array of terms.
    Autocomplete(const std::vector<Term>& terms) {
        if (terms.empty()) {
            throw std::invalid_argument("Term list cannot be empty");
        }
        this->terms = terms;

        // Sort terms lexicographically for binary search
        std::sort(this->terms.begin(), this->terms.end());
    }

    // Returns all terms that start with the given prefix, in descending order of weight.
    std::vector<Term> allMatches(const std::string& prefix) {
        if (prefix.empty()) {
            throw std::invalid_argument("Prefix cannot be empty");
        }

        // Create a comparator based on the prefix length
        auto prefixComp = Term::byPrefixOrder(prefix.length());

        // Create a dummy term with the prefix
        Term prefixTerm(prefix, 0);

        // Use BinarySearchDeluxe to find the first and last indices
        int firstIndex = BinarySearchDeluxe::firstIndexOf(terms, prefixTerm, prefixComp);
        int lastIndex = BinarySearchDeluxe::lastIndexOf(terms, prefixTerm, prefixComp);

        // Handle case when no matches are found
        if (firstIndex == -1 || lastIndex == -1 || firstIndex > lastIndex) {
            return {}; // Return an empty vector if no matches
        }

        // Collect all terms that match the prefix
        std::vector<Term> matches;
        for (int i = firstIndex; i <= lastIndex; ++i) {
            if (terms[i].query.substr(0, prefix.length()) == prefix) {
                matches.push_back(terms[i]);
            }
        }

        // Sort matches in descending order of weight
        std::sort(matches.begin(), matches.end(), Term::byReverseWeightOrder());

        return matches;
    }

    // Returns the number of terms that start with the given prefix.
    int numberOfMatches(const std::string& prefix) {
        return allMatches(prefix).size();
    }

    // Unit testing (required)
    static void test() {
        std::vector<Term> terms = {
            Term("apple", 500), Term("app", 700), Term("application", 300),
            Term("ape", 200), Term("apex", 100)
        };

        Autocomplete autocomplete(terms);

        std::cout << "Testing allMatches(\"app\"):" << std::endl;
        auto results = autocomplete.allMatches("app");
        for (const auto& term : results) {
            std::cout << term.toString() << std::endl;
        }

        std::cout << "\nTesting numberOfMatches(\"ap\"):" << std::endl;
        std::cout << autocomplete.numberOfMatches("ap") << std::endl;  // Expected: 5
    }
};


// // Main function to test the Autocomplete class
// int main() {
//     // Test the Autocomplete class
//     Autocomplete::test();
//     return 0;
// }