#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>
#include <iomanip>

class Term {
public:
    std::string query;
    long weight;

    // Constructor: Initializes a term with the given query string and weight.
    Term(std::string query, long weight) {
        if (query.empty()) {
            throw std::invalid_argument("Query cannot be empty");
        }
        if (weight < 0) {
            throw std::invalid_argument("Weight cannot be negative");
        }
        this->query = query;
        this->weight = weight;
    }

    // Compare two terms in lexicographic order by query (natural order).
    bool operator<(const Term& other) const {
        return this->query < other.query;
    }

    // Compares the two terms in descending order by weight.
    // Return a comparator that compares two terms in descending order by weight.
    static std::function<bool(const Term&, const Term&)> byReverseWeightOrder() {
        return [](const Term& a, const Term& b) {
            return a.weight > b.weight;
            };
    }

    // Returns a comparator that compares two Term objects by the first r characters 
    // of their query strings in lexicographic order (i.e., dictionary order).
    static std::function<bool(const Term&, const Term&)> byPrefixOrder(int r) {
        return [r](const Term& a, const Term& b) {
            std::string prefixA = a.query.substr(0, std::min(static_cast<int>(a.query.length()), r));
            std::string prefixB = b.query.substr(0, std::min(static_cast<int>(b.query.length()), r));
            return prefixA < prefixB;
            };
    }

    // Returns a string representation of the term: "weight query".
    std::string toString() const {
        return std::to_string(weight) + "\t" + query;
    }

    // Unit testing (required)
    static void test() {
        Term t1("apple", 500);
        Term t2("application", 300);
        Term t3("app", 700);

        std::cout << "Testing term creation and toString():" << std::endl;
        std::cout << t1.toString() << std::endl; // Expected: "500	apple"
        std::cout << t2.toString() << std::endl; // Expected: "300	application"
        std::cout << t3.toString() << std::endl; // Expected: "700	app"

        std::cout << "\nTesting natural order (operator<):" << std::endl;
        std::cout << (t1 < t2) << std::endl; // Expected: 1 (true), "apple" < "application"
        std::cout << (t2 < t1) << std::endl; // Expected: 0 (false), "application" > "apple"

        std::cout << "\nTesting byReverseWeightOrder comparator:" << std::endl;
        auto weightComp = Term::byReverseWeightOrder();
        std::cout << weightComp(t1, t2) << std::endl; // Expected: 1 (true), 500 > 300
        std::cout << weightComp(t2, t1) << std::endl; // Expected: 0 (false), 300 < 500

        std::cout << "\nTesting byPrefixOrder(3) comparator:" << std::endl;
        auto prefixComp = Term::byPrefixOrder(3);
        std::cout << prefixComp(t1, t3) << std::endl; // Expected: 0 (false), "app" > "app" (apple vs app with r=3)
        std::cout << prefixComp(t1, t2) << std::endl; // Expected: 0 (false), "app" > "app" (apple vs application with r=3)
    }
};

// int main() {
//     Term::test(); // Run unit tests
//     return 0;
// }
