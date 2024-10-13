#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "dependencies/Autocomplete.cpp"  // Assumes Autocomplete class is implemented in Autocomplete.cpp


int main(int argc, char* argv[]) {
    if (argc < 3) {  // Expect two arguments: filename and number of results
        std::cerr << "Usage: " << argv[0] << " <filename> <maxResults>" << std::endl;
        return 1; // Exit with an error
    }

    std::string filename = argv[1]; // Get the filename from the first argument
    int maxResults = std::stoi(argv[2]);  // Convert the third argument to an integer


    std::ifstream infile(filename);

    // If the file cannot be opened, print an error message and return 1
    if (!infile) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    // Read the number of terms from the file
    int n; infile >> n;

    // Initialize a vector to store the terms
    std::vector<Term> terms;

    // Read each term from the file and add it to the vector
    for (int i = 0; i < n; i++) {
        long weight;
        std::string query;
        infile >> weight >> std::ws; // Read the weight and consume any whitespace
        std::getline(infile, query); // Read the query
        terms.emplace_back(query, weight); // Add the term to the vector
    }

    // Create an Autocomplete object with the terms
    Autocomplete autocomplete(terms);

    std::string prefix; // Variable to store the prefix entered by the user
    // Prompt the user to enter a prefix and display the results
    std::cout << "Enter a prefix to search (or type '!q' to quit):" << std::endl;
    while (true) {
        // Print the prompt(in green color) 
        std::cout << "\n\033[1;32m" << "> " << "\033[0m";
        std::getline(std::cin, prefix); // Read the prefix from the user

        // Check if the user wants to exit the program
        if (prefix == "!q") {
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            break;
        }

        // Get the results for the prefix
        std::vector<Term> results = autocomplete.allMatches(prefix);
        // Print the number of matches in yellow color
        std::cout << "\033[1;33m" << results.size() << " matches \033[0m" << std::endl;
        // Print the first maxResults results
        for (size_t i = 0; i < std::min(results.size(), static_cast<size_t>(maxResults)); i++) {
            std::cout << results[i].toString() << "\n";
        }
    }


    return 0; // Return 0 to indicate success
}