#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(const RPN& other)
{
    *this = other;
}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
    {
        _stack = other._stack;
    }
    return *this;
}

RPN::~RPN()
{
}
int check_input(const std::string& expression)
{
    for (unsigned int i =0 ; i < expression.length();i++)
    {
        if (expression[i] == ' ')
            continue;
        else if (isdigit(expression[i]))
            continue;
        else if (expression[i] == '*' || expression[i] == '+' || expression[i] == '/' || expression[i] == '-')
            continue;
        else 
            return 1;
    }
    return 0;
}
void RPN::evaluate(const std::string& expression)
{
    if (check_input(expression))
    {
        std::cerr << "Error: Invalid character in expression" << std::endl;
        return ;
    }
    for (unsigned int i =0 ; i < expression.length();i++)
    {
        if (expression[i] == ' ')
            continue;
        else if (isdigit(expression[i]))
            _stack.push(expression[i] - '0');
        else 
        {
            if (_stack.size() < 2)
            {
                std::cerr << "Error: Invalid expression" << std::endl;
                return;
            }
            else
            {
                int value =  _stack.top();
                _stack.pop();
                int second_value = _stack.top();
                _stack.pop();
                switch (expression[i])
                {
                    case '*':
                        _stack.push(value * second_value);
                        break;
                    case '+':
                        _stack.push(value + second_value);
                        break;
                    case '/':
                        if (value == 0)
                            throw std::runtime_error("error : divide by zero !!");
                        _stack.push(second_value / value );
                        break;
                    case '-':
                        _stack.push(second_value - value);
                        break;
                    default:
                        std::cerr << "Error: Invalid operator" << std::endl;
                        return ;
                }
            } 
        }
    }
    if (_stack.size() != 1)
    {
        std::cerr << "Error: Invalid expression" << std::endl;
        return ;
    }
    std::cout << _stack.top() << std::endl;
}