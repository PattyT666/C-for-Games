#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <map>
#include <cctype>

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

double applyOperator(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            throw std::runtime_error("Division by zero!");
        }
        return a / b;
    default: throw std::runtime_error("Unknown operator");
    }
}

std::vector<std::string> tokenize(const std::string& expr) {
    std::vector<std::string> tokens;
    std::stringstream ss;
    for (size_t i = 0; i < expr.length(); ++i) {
        char c = expr[i];
        if (std::isspace(c)) continue;
        if (std::isdigit(c) || c == '.') {
            ss.str("");
            while (i < expr.length() && (std::isdigit(expr[i]) || expr[i] == '.')) {
                ss << expr[i++];
            }
            --i;
            tokens.push_back(ss.str());
        }
        else if (isOperator(c) || c == '(' || c == ')') {
            tokens.push_back(std::string(1, c));
        }
        else {
            throw std::runtime_error("Invalid character in expression.");
        }
    }
    return tokens;
}

std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens) {
    std::vector<std::string> output;
    std::stack<char> ops;

    for (const std::string& token : tokens) {
        if (std::isdigit(token[0]) || (token[0] == '.' && token.length() > 1)) {
            output.push_back(token);
        }
        else if (token.length() == 1 && isOperator(token[0])) {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token[0])) {
                output.push_back(std::string(1, ops.top()));
                ops.pop();
            }
            ops.push(token[0]);
        }
        else if (token == "(") {
            ops.push('(');
        }
        else if (token == ")") {
            while (!ops.empty() && ops.top() != '(') {
                output.push_back(std::string(1, ops.top()));
                ops.pop();
            }
            if (ops.empty()) throw std::runtime_error("Mismatched parentheses.");
            ops.pop(); // remove '('
        }
    }

    while (!ops.empty()) {
        if (ops.top() == '(' || ops.top() == ')') throw std::runtime_error("Mismatched parentheses.");
        output.push_back(std::string(1, ops.top()));
        ops.pop();
    }

    return output;
}

double evaluatePostfix(const std::vector<std::string>& postfix) {
    std::stack<double> stack;

    for (const std::string& token : postfix) {
        if (std::isdigit(token[0]) || token.find('.') != std::string::npos) {
            stack.push(std::stod(token));
        }
        else if (token.length() == 1 && isOperator(token[0])) {
            if (stack.size() < 2) throw std::runtime_error("Invalid expression.");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            double result = applyOperator(a, b, token[0]);
            stack.push(result);
        }
    }

    if (stack.size() != 1) throw std::runtime_error("Invalid expression.");
    return stack.top();
}

int main() {
    std::string expression;
    std::cout << "Enter a math expression (e.g., 3 + 5 * 2 - (4 / 2)): ";
    std::getline(std::cin, expression);

    try {
        auto tokens = tokenize(expression);
        auto postfix = infixToPostfix(tokens);
        double result = evaluatePostfix(postfix);
        std::cout << "Result: " << result << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }

    return 0;
}