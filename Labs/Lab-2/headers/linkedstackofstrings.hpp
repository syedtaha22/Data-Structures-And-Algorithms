#pragma once

#include <iostream>
#include <string>

using std::string;

class LinkedStackOfStrings {
private:
    struct Node {
        string item;
        Node* next;
    };

    Node* first;

public:
    LinkedStackOfStrings() : first{ nullptr } { }

    ~LinkedStackOfStrings() {
        while (first != nullptr) {
            Node* next = first->next;
            delete first;
            first = next;
        }
    }

    void push(const string& item) {
        Node* oldfirst = first;          // save pointer to current first node
        first = new Node;                // create new node
        first->item = item;              // set data of new node
        first->next = oldfirst;          // set next of new node to old first node
        // first = new Node {item, oldfirst}; // equivalently in C++11
    }

    string pop() {
        string item = std::move(first->item);     // store data from first node
        Node* oldfirst = first;        // store pointer to the first node
        //auto [item, oldfirst] = *first;  // equivalently in C++17
        first = first->next;           // update first
        delete oldfirst;               // delete oldfirst node
        return item;                   // return item
    }

    bool empty() const {
        return first == nullptr;
    }

};

