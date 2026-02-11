#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <cmath>
#include <set>
#include <utility>
class BitcoinExchange
{
    private:
        std::set<std::pair<std::string, float*> > _inputValues;
        std::map<std::string, float> _exchangeRates;
        void parseinput(const std::string& input);
        void getExchangeRate(const std::string& data) ;
        void printExchangeRates();
    public:
        BitcoinExchange();
        BitcoinExchange(std::string data, std::string input);
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
};

#endif