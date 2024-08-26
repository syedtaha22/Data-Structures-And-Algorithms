#pragma once
#include <string>
#include <stdexcept>
using std::string;

class ResizingArrayStackOfStrings {
private:
    int N; // denotes the number of elements in the stack
    int capacity; // denotes the capacity of the stack
    string* s;

public:
    ResizingArrayStackOfStrings() : N{ 0 }, capacity{ 1 }, s{ new string[capacity] } {
    }

    ~ResizingArrayStackOfStrings() {
        delete[] s;
    }

    void push(const string& item) {
        if (N == capacity) resize(2 * capacity); // double the capacity if the stack is full
        s[N++] = item;  // same as a[N] = item; N++;
    }

    string pop() {
        if (N == 0) throw std::out_of_range("Stack is empty"); // stack must not be empty
        if (N > 0 && N == capacity / 4) resize(capacity / 2); // halve the capacity if the stack is 1/4 full
        return std::move(s[--N]);  // 
    }

    bool empty() { return N == 0; }

    int size() { return N; }

private:
    void resize(int newcap) {
        string* copy = new string[newcap];
        for (int i = 0; i < N && i < newcap; ++i)
            copy[i] = std::move(s[i]);
        delete[] s;
        s = copy;
        capacity = newcap;
    }

};
