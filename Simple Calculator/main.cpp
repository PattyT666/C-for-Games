#include <iostream>
#include <limits>

double getNumberFromUser(const std::string& prompt)
{
    double value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cout << "ERROR: That’s not a number. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            return value;
        }
    }
}

char getOperatorFromUser()
{
    char op;
    while (true)
    {
        std::cout << "Enter an operator (+, -, *, /): ";
        std::cin >> op;

        if (op == '+' || op == '-' || op == '*' || op == '/')
        {
            return op;
        }
        else
        {
            std::cout << "ERROR: Invalid operator. Try again.\n";
        }
    }
}

int main()
{
    double num1 = getNumberFromUser("Enter first number: ");
    char op = getOperatorFromUser();
    double num2 = getNumberFromUser("Enter second number: ");

    if (op == '/' && num2 == 0)
    {
        std::cout << "ERROR: Division by zero is not allowed.\n";
        return 1;
    }

    double result;

    switch (op)
    {
    case '+': result = num1 + num2; break;
    case '-': result = num1 - num2; break;
    case '*': result = num1 * num2; break;
    case '/': result = num1 / num2; break;
    default: std::cout << "Something went wrong.\n"; return 1;
    }

    std::cout << "Result: " << result << std::endl;
    return 0;
}