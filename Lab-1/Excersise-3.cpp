/*
    Write a function EvaluatePostfix() that that takes a postfix expression as string, evaluates it, and
    returns the value. For simplicity, we assume that the input expression contains only the following operators:
        1) addition(+),
        2) subtraction(-),
        3) mutiply(*),
        4) divide(/), and
        5) exponentiation(^),
    and the operands are single-digit positive integers.

        - Example 1:
            Input: 1 2 3 4 5 * + 6 * * +
            Output: 277
        - Example 2:
            Input: 7 16 16 16 * * * 5 16 16 * * 3 16 * 1 + + +
            Output: 30001
        - Example 3:
            Input: 7 16 * 5 + 16 * 3 + 16 * 1 +
            Output: 30001
*/

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>

int EvaluatePostfix(const std::string &expression)
{
    std::stack<int> operands;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        // If the token is a number, push it onto the stack
        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1))
        {
            operands.push(std::stoi(token));
        }
        // If the token is an operator, perform the corresponding operation
        else
        {
            // Ensure there are at least two operands in the stack
            if (operands.size() < 2)
            {
                throw std::runtime_error("Insufficient operands for the operation");
            }

            int operand2 = operands.top();
            operands.pop();
            int operand1 = operands.top();
            operands.pop();

            // Perform the operation based on the operator
            switch (token[0])
            {
            case '+':
                operands.push(operand1 + operand2);
                break;
            case '-':
                operands.push(operand1 - operand2);
                break;
            case '*':
                operands.push(operand1 * operand2);
                break;
            case '/':
                if (operand2 == 0)
                {
                    throw std::runtime_error("Division by zero");
                }
                operands.push(operand1 / operand2);
                break;
            default:
                throw std::runtime_error("Invalid operator");
            }
        }
    }

    // After processing all tokens, there should be exactly one operand left in the stack
    if (operands.size() != 1)
    {
        throw std::runtime_error("Invalid expression");
    }

    return operands.top();
}

int main()
{
    try
    {
        std::cout << "1 2 3 4 5 * + 6 * * +  = " << EvaluatePostfix("1 2 3 4 5 * + 6 * * +") << std::endl;
        std::cout << "7 16 16 16 * * * 5 16 16 * * 3 16 * 1 + + + = " << EvaluatePostfix("7 16 16 16 * * * 5 16 16 * * 3 16 * 1 + + +") << std::endl;
        std::cout << "7 16 * 5 + 16 * 3 + 16 * 1 + = " << EvaluatePostfix("7 16 * 5 + 16 * 3 + 16 * 1 +") << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}