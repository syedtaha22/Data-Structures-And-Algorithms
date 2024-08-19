/*
    Josephus problem:
        In the Josephus problem from antiquity, n people are in dire straits and agree to the
        following strategy to reduce the population. They arrange themselves in a circle
        (at positions numbered from 0 to n − 1) and proceed around the circle, eliminating every
        m-th person until only one person is left. Legend has it that Josephus figured out where
        to sit to avoid being eliminated. Using circular linked list, write a program that takes
        two integer inputs m and n and prints the order in which people are eliminated
        (and thus would show Josephus where to sit in the circle).

        - Example 1:
            Input: n = 5 and m = 2
            Output: 1, 3, 0, 4, 2
        - Example 2:
            Input: n = 7 and m = 3
            Output: 2, 5, 1, 6, 4, 0, 3

        Solution: Use a circular linked list to store the positions of the people. Do m − 1 times: Find the m-th
        person in the list, and remove it.
*/

#include <iostream>

// Node structure to represent each person in the circle
struct Node
{
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};

// Function to create a circular linked list with n nodes
Node *createCircularList(int n)
{
    Node *head = new Node(0);
    Node *current = head;

    // Create the remaining nodes and link them in a circular manner
    for (int i = 1; i < n; ++i)
    {
        current->next = new Node(i);
        current = current->next;
    }
    current->next = head; // Make the list circular by pointing the last node to the head

    return head;
}

// Function to solve the Josephus problem
void josephus(int n, int m)
{
    Node *head = createCircularList(n);
    Node *current = head;
    Node *prev = nullptr;

    std::cout << "Order of elimination: ";

    while (n > 0)
    {
        // Move m-1 steps forward in the circular list
        for (int i = 1; i < m; ++i)
        {
            prev = current;
            current = current->next;
        }

        // Remove the m-th person from the circle
        std::cout << current->data;
        if (n > 1)
        {
            std::cout << ", ";
        }

        prev->next = current->next;
        delete current;
        current = prev->next;

        --n; // Decrease the number of people in the circle
    }

    std::cout << std::endl;
}

int main()
{
    int n, m;

    // Input values for n and m
    std::cout << "Enter the number of people (n): ";
    std::cin >> n;
    std::cout << "Enter the step size (m): ";
    std::cin >> m;

    // Solve the Josephus problem and print the result
    josephus(n, m);

    return 0;
}
