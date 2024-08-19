/*
    Write a Stack client that reads a string of parentheses, square brackets, and curly braces from standard
    input and uses a stack to determine whether they are properly balanced.

    For example:
     Your program should print true for [()]{}{[()()]()} and false for [(]).
*/

#include <iostream>
#include <stack>

// Class to check if an expression has balanced braces
class isBalanced
{
public:
    // Overloaded operator() to allow the object to be called like a function
    bool operator()(const std::string &expression) const
    {
        std::stack<char> braceStack; // Stack to keep track of opening braces

        // Loop through each character in the expression
        for (char c : expression)
        {
            // If the character is an opening brace, push it onto the stack
            if (c == '{' || c == '[' || c == '(')
            {
                braceStack.push(c);
            }
            // If the character is a closing brace
            else if (c == '}' || c == ']' || c == ')')
            {
                // If the stack is empty, it means there's an unmatched closing brace
                if (braceStack.empty())
                {
                    return false; // Expression is not balanced
                }

                // Get the top element from the stack (last opened brace)
                char top = braceStack.top();
                braceStack.pop(); // Remove the top element from the stack

                // Check if the closing brace matches the last opened brace
                if ((c == '}' && top != '{') || (c == ']' && top != '[') || (c == ')' && top != '('))
                {
                    return false; // Mismatched opening and closing braces
                }
            }
        }

        // If the stack is empty, all opening braces had matching closing braces
        // Otherwise, there are unmatched opening braces left
        return braceStack.empty();
    }
};

int main()
{
    // Test the isBalanced function with different expressions
    std::cout << "[()]{}{[()()]()} : " << isBalanced()("[()]{}{[()()]()}") << std::endl;
    std::cout << "[(]) : " << isBalanced()("[(])") << std::endl;

    return 0;
}