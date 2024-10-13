/*
    Clients:
        Write a client program to solve each of the following problems. You may only declare one
        variable in your client, and it must be of type Deque or RandomizedQueue.

        (b) Read in a DNA sequence from standard input using std::cin >> ch, where ch is declared as char
        variable. Determine whether the string represents a Watson-Crick complemented palindrome (the
        string equals its reverse when you replace each base with its complement: A-T, C-G).

        Palindromes in DNA have have many important biological roles. For example, tumor cells frequently
        amplify their genes by forming DNA palindromes.

        Here are some examples of Watson-Crick complemented palindromes:
            -   ACGT as its reverse is TGCA and replacing A with T, C with G, G with C, and T with A, we get the
                original string.
            -   ACGTACGT
            -   ACGTACGTACGTACGTACGT
*/


#include <iostream>
#include <sstream>
#include <string>
#include "Deque.cpp"  // Include the Deque class implementation

// Function to get the Watson-Crick complement of a DNA base
char complement(char base) {
    switch (base) {
    case 'A': return 'T';
    case 'T': return 'A';
    case 'C': return 'G';
    case 'G': return 'C';
    default: return '\0';  // Invalid base (should not occur in valid DNA sequences)
    }
}

// Function to check if the DNA sequence is a Watson-Crick complemented palindrome
bool is_watson_crick_palindrome(const std::string& dna) {
    Deque<char> deque;  // The only allowed variable of type Deque

    // Load DNA sequence into deque
    for (char ch : dna) {
        deque.push_back(ch);
    }

    // Compare characters from both ends
    while (deque.size() > 1) {
        char front = deque.pop_front();  // Get the front character
        char back = deque.pop_back();    // Get the back character

        // Check if the complement of the front character matches the back character
        if (complement(front) != back) {
            return false;  // Not a palindrome if they don't match
        }
    }

    return true;  // All characters matched, it's a palindrome
}

int main() {
    std::string line;

    // Read input from standard input (could be redirected from a file)
    while (std::getline(std::cin, line)) {
        // Ignore everything after '#' (if any)
        std::string dna_sequence = line.substr(0, line.find('#'));

        // Remove any trailing whitespace from the DNA sequence
        dna_sequence.erase(dna_sequence.find_last_not_of(" \n\r\t") + 1);

        // Only check non-empty sequences
        if (!dna_sequence.empty()) {
            if (is_watson_crick_palindrome(dna_sequence)) {
                std::cout << dna_sequence << " is a Watson-Crick complemented palindrome." << std::endl;
            }
            else {
                std::cout << dna_sequence << " is NOT a Watson-Crick complemented palindrome." << std::endl;
            }
        }
    }

    return 0;
}
