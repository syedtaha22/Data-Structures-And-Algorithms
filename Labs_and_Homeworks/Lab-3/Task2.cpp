/*
    Task 2:
    Anagrams: In this exercise, we design an O(N log N) algorithm to read in a list of words
    and print out all anagrams. For example, the strings "comedian" and "demoniac" are anagrams
    of each other. Assume there are N words and each word contains at most 20 letters.

    (a) Begin by generating a list of random words that contains anagrams.
    The following code generates a random word of length L:

        std::string random_word(int L) {
            std::string s;
            for (int i = 0; i < L; ++i) {
                s.push_back('a' + std::random_device()() % 26);
            }
            return s;
        }

    For each word generated, we can shuffle the characters to generate an anagram.
    The following code shuffles the characters of a string `s`:

        shuffle(s.begin(), s.end(),
                std::default_random_engine(std::random_device()()));

    Generate a list of N = 100,000 words, where each word has a length of at most 20.
    Ensure that the list contains anagrams.

    (b) Design an O(N^2) algorithm.

    (c) Improve the algorithm to O(N log N).
    We will make use of the `std::sort` function from the C++ Standard Library.
    To sort a container, use the following syntax:

        std::sort(container.begin(), container.end());

    Now, follow these steps to solve the problem:

    1. Sort each word in the list of words.
    2. Sort the entire list of words.

    After completing the above steps, all anagrams will be next to each other and
    can be counted in linear time.
*/

// Include the necessary headers
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// a) Function to generate a random word of length L
std::string random_word(int L) {
    std::string s;
    for (int i = 0; i < L; ++i) {
        s.push_back('a' + std::random_device()() % 26);
    }
    return s;
}

// b) O(N^2) algorithm to find anagrams
void findAnagramsN2(const std::vector<std::string>& words) {
    int N = words.size(); // Get the number of words in the list

    std::cout << "Anagrams found using O(N^2) algorithm:\n" << std::endl;
    // Loop over each word in the list
    for (int i = 0; i < N; ++i) {
        std::string sortedWord = words[i]; // Copy the word to sort
        std::sort(sortedWord.begin(), sortedWord.end()); // Sort the word


        // Loop over the remaining words to compare with the current word
        for (int j = i + 1; j < N; ++j) {
            std::string sortedNextWord = words[j]; // Copy the next word to sort
            std::sort(sortedNextWord.begin(), sortedNextWord.end()); // Sort the next word

            // Check if the sorted words are equal (anagrams)
            if (sortedWord == sortedNextWord) {
                std::cout << words[i] << " and " << words[j] << " are anagrams." << std::endl;
            }
        }
    }
}

// c) O(N log N) algorithm to find anagrams
void findAnagramsNLogN(const std::vector<std::string>& words) {
    std::vector<std::string> sortedWords = words; // Copy the list of words to sort

    // 1. Sort each word in the list
    for (std::string& word : sortedWords) {
        std::sort(word.begin(), word.end());
    }

    // 2. Sort the entire list of words
    std::sort(sortedWords.begin(), sortedWords.end());

    int N = sortedWords.size(); // Get the number of words in the sorted list

    std::cout << "Anagrams found using O(N log N) algorithm:\n" << std::endl;
    // Loop over the sorted list to find anagrams
    for (int i = 0; i < N - 1; ++i) {
        // Check if the current word is an anagram of the next word
        if (sortedWords[i] == sortedWords[i + 1]) {
            std::cout << words[i] << " and " << words[i + 1] << " are anagrams." << std::endl;
        }
    }
}



// Main function to generate random words, and compare time for O(N^2) and O(N log N) algorithms
int main() {
    int N = 10; // Number of words
    int L = 20; // Maximum length of each word

    std::cout << "Generating a list of " << N << " words with a maximum length of " << L << " characters...\n" << std::endl;

    std::vector<std::string> words; // Vector to store the list of words

    // Generate N random words and shuffle them to create anagrams
    for (int i = 0; i < N; ++i) {
        std::string word = random_word(L); // Generate a random word
        std::string anagram = word; // Copy the word to shuffle
        std::shuffle(anagram.begin(), anagram.end(), std::default_random_engine(std::random_device()())); // Shuffle the characters
        words.push_back(anagram); // Add the anagram to the list of words
        words.push_back(word); // Add the original word to the list of words
        // shuffle the list of words and anagrams
        std::shuffle(words.begin(), words.end(), std::default_random_engine(std::random_device()()));
    }

    // Measure the time taken by the O(N^2) algorithm
    auto startN2 = std::chrono::high_resolution_clock::now(); // Start the timer
    findAnagramsN2(words); // Find anagrams using the O(N^2) algorithm
    auto endN2 = std::chrono::high_resolution_clock::now(); // Stop the timer

    // Add an newline for spacing
    std::cout << std::endl;

    // Measure the time taken by the O(N log N) algorithm
    auto startNLogN = std::chrono::high_resolution_clock::now(); // Start the timer
    findAnagramsNLogN(words); // Find anagrams using the O(N log N) algorithm
    auto endNLogN = std::chrono::high_resolution_clock::now(); // Stop the timer

    // Calculate the duration of the O(N^2) algorithm in seconds
    std::chrono::duration<double> durationN2 = endN2 - startN2;

    // Calculate the duration of the O(N log N) algorithm in seconds
    std::chrono::duration<double> durationNLogN = endNLogN - startNLogN;

    // Add an newline for spacing
    std::cout << std::endl;

    // Output the time taken by each algorithm
    std::cout << "O(N^2) algorithm took " << durationN2.count() << " seconds." << std::endl;
    std::cout << "O(N log N) algorithm took " << durationNLogN.count() << " seconds." << std::endl;

    return 0;
}