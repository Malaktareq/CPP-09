#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include <sstream>

class PmergeMe{
    private:
        // std::vector<std::pair<int,int> > v;
    public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator =(const PmergeMe& other);
    ~PmergeMe();
    void sort(std::string &str);
    std::vector<int>& PmergeMe::insertnumbers(std::string &ref);
};

#endif