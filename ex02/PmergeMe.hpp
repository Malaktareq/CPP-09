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
    void sort(std::string &str);
    std::vector<int> PmergeMe::insertnumbers(std::string &ref);
    std::vector<std::pair<int,int> > make_pairs(std::vector<int> numbers);
    void algo(std::vector<std::pair<int,int> >& pairs);
    std::vector<int> PmergeMe::Insert_order(std::vector<int> Jacob, int size);
    std::vector<int> PmergeMe::Jacobsthal(int n);
    void binary_insert(std::vector<std::pair<int,int> >& main_chain ,std::vector<std::pair<int,int> > main2_chain, std::vector<int> order);
};

#endif