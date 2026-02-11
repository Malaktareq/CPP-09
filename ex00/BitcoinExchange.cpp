#include "BitcoinExchange.hpp"

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
    {
            for (std::set<std::pair<std::string, float*> >::iterator it =
            other._inputValues.begin(); it != other._inputValues.end(); ++it)
            {
                float* value = NULL;
                if (it->second != NULL)
                {
                    value = new float(*(it->second));
                    if (value == NULL)
                    {
                        std::cout << "Error: Memory allocation failed." << std::endl;
                        return *this;
                    }
                }
                _inputValues.insert(std::make_pair(it->first, value));
                delete it->second;
            }
        _exchangeRates = other._exchangeRates;
    }
    return *this;
}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    *this = other;
}

void BitcoinExchange::getExchangeRate(const std::string& data) 
{
    std::string line;
    std::ifstream inputfile(data.c_str());

    if (!inputfile.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return ;
    }
    while (std::getline(inputfile, line))
    {
        size_t commaPos = line.find(',');
        if (commaPos != std::string::npos)
        {
            std::string date = line.substr(0, commaPos);
            float rate = static_cast<float>(strtod(line.substr(commaPos + 1).c_str(), NULL));
            _exchangeRates.insert(std::pair<std::string, float>(date, rate));
        }
    }
}

int check_date_format(const std::string& date)
{
    int countdashes = 0;
    if (date.length() != 10)
        return 1;
    for (size_t i = 0; i < date.length(); ++i)
    {
        if (!isdigit(date[i]) && date[i] != '-')
        {
            std::cout << i << " char: " << date[i] << std::endl;
            return 1;
        }
        if (date[i] == '-')
            countdashes++;
    }
    if (countdashes != 2)
        return 1;
    else if (!(date[4] == '-' && date[7] == '-' ))
        return 1;
    if (atoi(date.substr(5,2).c_str()) == 2 && atoi(date.substr(0,4).c_str()) % 4 == 0 && atoi(date.substr(8,2).c_str()) > 29)
    {
        return 1;
    }
    else if ((atoi(date.substr(5,2).c_str()) % 2  ||atoi(date.substr(5,2).c_str()) == 8 )
    && atoi(date.substr(8,2).c_str()) > 31)
        return 1;
    else if (atoi(date.substr(5,2).c_str()) == 2 && atoi(date.substr(0,4).c_str()) % 4 && atoi(date.substr(8,2).c_str()) > 28)
        return 1;
    else if ((atoi(date.substr(5,2).c_str()) % 2 == 0 && atoi(date.substr(5,2).c_str()) != 8)
    && atoi(date.substr(8,2).c_str()) > 30)
        return 1;
    else if (atoi(date.substr(5,2).c_str()) > 12 || atoi(date.substr(5,2).c_str()) == 0)
        return 1;
    else if (atoi(date.substr(8,2).c_str()) == 0)
        return 1;
    return 0;
}

void BitcoinExchange::printExchangeRates()
{
    std::set<std::pair<std::string, float*> >::iterator it;
    it = _inputValues.begin();
    while (it != _inputValues.end())
    {
        if (it->second == NULL)
            std::cout << "Error: bad input => " << it->first << std::endl;
        else if (check_date_format(it->first))
            std::cout << "Error: Invalid date format: " << it->first << std::endl;
        else if (*it->second < 0)
            std::cout << "Error: not a positive number." << std::endl;
        else if (*it->second > 1000)
            std::cout << "Error: too large a number." << std::endl;
        else
        {
            if (it->first < _exchangeRates.begin()->first)
            {
                std::cout << "Error: date is to early => " << it->first << std::endl;
                ++it;
                continue ;
            }
            std::map<std::string,float>::iterator value;
            value = _exchangeRates.lower_bound(it->first);
            if (value->first != it->first)
                --value;
            std::cout << it->first << " => " << *(it->second) << " => " << *(it->second) * value->second << std::endl;
        }
        ++it;
    }
}

void BitcoinExchange::parseinput(const std::string& input)
{
    std::string line;
    std::ifstream inputfile(input.c_str());

    if (!inputfile.is_open())
    {
        std::cout << "Error opening file!" << std::endl;
        return ;
    }
    if(!std::getline(inputfile, line))
    {
        std::cout << "Error: empty file" << std::endl;
        return ;
    }
    if (line != "date | value")
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return ;
    }
    while (std::getline(inputfile, line))
    {
        if (line.empty())
            continue ;
        size_t barPos = line.find('|');
        if (line[barPos + 1] == '\0')
        {
             _inputValues.insert(std::make_pair(line, (float *)NULL));
            continue ;
        }
        if (barPos != std::string::npos)
        {
            int flag = 0;
            std::string date = line.substr(0, barPos -1);
            for (size_t i = barPos + 1; i < line.length(); ++i)
            {
                if (!isdigit(line[i]) && line[i] != ' ' && line[i] != '.' && line[i] != '-')
                {
                    flag = 1;
                    _inputValues.insert(std::make_pair(line, (float *)NULL));
                    break;
                }
            }
            if (flag)
                continue ;
            float rate = static_cast<float>(strtod(line.substr(barPos + 1).c_str(), NULL));
            float* value = new float(rate);
            if (value == NULL)
            {
                std::cout << "Error: Memory allocation failed." << std::endl;
                return ;
            }
            _inputValues.insert(std::make_pair(date,value));
        }
        else
        {
            _inputValues.insert(std::make_pair(line, (float *)NULL));
        }
    }
}

BitcoinExchange::BitcoinExchange()
{
}
BitcoinExchange::BitcoinExchange(std::string data, std::string input)
{
    getExchangeRate(data);
    parseinput(input);
    printExchangeRates();
}


BitcoinExchange::~BitcoinExchange()
{
    std::set<std::pair<std::string, float*> >::iterator it;
    it = _inputValues.begin();
    while (it != _inputValues.end())
    {
        if (it->second != NULL)
            delete it->second;
        ++it;
    }
}