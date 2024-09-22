/*
    Clients:
        Write a client program to solve each of the following problems. You may only declare one
        variable in your client, and it must be of type Deque or RandomizedQueue.

        (a) Given a command line parameter k, read in a sequence of strings from standard input, and print
        out a subset of exactly k of them, uniformly at random

            ```
            > cat distinct.txt
            A B C D E F G H I
            > Permutation 3 < distinct.txt
            C
            G
            A
            > Permutation 3 < distinct.txt
            E
            F
            G
            ```
            ```
            > cat duplicates.txt
            AA BB BB BB BB BB CC CC
            > Permutation 8 < duplicates.txt
            BB
            AA
            BB
            CC
            BB
            BB
            CC
            BB
            ```

*/

#include <iostream>
#include <string>
#include "RandomizedQueue.cpp"  // Include the RandomizedQueue class implementation

// Main function to solve the problem
int main(int argc, char* argv[]) {
    // Ensure that a command line argument (k) is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <k>" << std::endl;
        return 1;
    }

    // Get the value of k from command line (convert string to int)
    int k = std::stoi(argv[1]);

    // Create an instance of RandomizedQueue of type std::string
    RandomizedQueue<std::string> rq;

    // Read strings from standard input and add them to the randomized queue
    std::string item;
    while (std::cin >> item) {
        rq.enqueue(item);
    }

    // If k is greater than the number of items, throw an error
    if (k > rq.size()) {
        std::cerr << "Error: k is greater than the number of available strings" << std::endl;
        return 1;
    }

    // Dequeue and print k random strings
    for (int i = 0; i < k; ++i) {
        std::cout << rq.dequeue() << std::endl;
    }

    return 0;
}
