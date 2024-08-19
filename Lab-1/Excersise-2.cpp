/*
    Write a function InfixToPostfix() that converts an infix arithmetic expression given as string and
    returns the equivalent expression as string in postfix.
    For simplicity, we assume that the input expression contains paranthesis, only the following operators:
        1) addition(+),
        2) subtraction(-),
        3) mutiply(*),
        4) divide(/), and
        5) exponentiation(^),
    and the operands are singledigit positive integers.

        - Example 1:
            Input: ( 2 + ( ( 3 + 4 )* ( 5 * 6 )))
            Output: 2 3 4 + 5 6 * * +
        - Example 2:
            Input: ( ( ( 5 + ( 7 * ( 1 + 1 )))* 3 )+ ( 2 * ( 1 + 1 )))
            Output: 5 7 1 1 + * + 3 * 2 1 1 + * +
*/

#include <iostream>
#include <stack>
#include <string>
#include <cctype>

// Function to return the precedence of operators
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0; // For non-operator characters, return 0 precedence
}

// Function to convert an infix expression to a postfix expression
std::string InfixToPostfix(const std::string &infix)
{
    std::stack<char> operators; // Stack to hold operators and parentheses
    std::string postfixExp;     // Resulting postfix expression

    for (size_t i = 0; i < infix.length(); ++i)
    {
        char c = infix[i];

        // Skip spaces in the input expression
        if (c == ' ')
            continue;

        // If the character is a digit, add it to the postfix expression
        if (isdigit(c))
        {
            while (i < infix.length() && isdigit(infix[i]))
            {
                postfixExp += infix[i];
                ++i;
            }
            postfixExp += ' '; // Add a space to separate numbers in the postfix expression
            --i;               // Adjust for the outer loop increment
        }
        // If the character is '(', push it onto the stack
        else if (c == '(')
        {
            operators.push(c);
        }
        // If the character is ')', pop from the stack to the postfix expression until '(' is found
        else if (c == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                postfixExp += operators.top();
                postfixExp += ' ';
                operators.pop();
            }
            if (!operators.empty() && operators.top() == '(')
                operators.pop(); // Remove the '(' from the stack
        }
        // If the character is an operator, handle operator precedence and push to stack
        else
        {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c))
            {
                postfixExp += operators.top();
                postfixExp += ' ';
                operators.pop();
            }
            operators.push(c); // Push the current operator onto the stack
        }
    }

    // Pop any remaining operators from the stack to the postfix expression
    while (!operators.empty())
    {
        postfixExp += operators.top();
        postfixExp += ' ';
        operators.pop();
    }

    // Return the final postfix expression
    return postfixExp;
}

int main()
{
    // Test cases for the InfixToPostfix function
    std::cout << "( 2 + ( ( 3 + 4 )* ( 5 * 6 ))) : " << InfixToPostfix("( 2 + ( ( 3 + 4 )* ( 5 * 6 )))") << std::endl;
    std::cout << "( ( ( 5 + ( 7 * ( 1 + 1 )))* 3 )+ ( 2 * ( 1 + 1 ))) : " << InfixToPostfix("( ( ( 5 + ( 7 * ( 1 + 1 )))* 3 )+ ( 2 * ( 1 + 1 )))") << std::endl;

    return 0;
}