#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <vector>
#include <deque>
#include <iostream>
#include <utility>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>

class PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);
        ~PmergeMe();
};
void print_arr(std::vector<int> arr);
std::vector<int> insertnumbers(std::string &ref);
std::vector<std::pair<int,int> > make_pairs(std::vector<int> numbers);
std::vector<int> Jacobsthal(int n);
std::vector<int> Insert_order(std::vector<int> Jacob, int size);
std::vector<int> binary_insert(std::vector<int>& pend, std::vector<std::pair<int,int> >& sorted_winners);
std::vector<int> algo(std::vector<int> numbers);
void sort(std::string &str);

void print_arr_deq(std::deque<int> arr);
std::deque<int> insertnumbers_deq(std::string &ref);
std::deque<std::pair<int,int> > make_pairs_deq(std::deque<int>
numbers);
std::deque<int> Jacobsthal_deq(int n);
std::deque<int> Insert_order_deq(std::deque<int> Jacob, int size);
std::deque<int> binary_insert_deq(std::deque<int>& pend, std::deque <std::pair<int,int> >& sorted_winners);
std::deque<int> algo_deq(std::deque<int> numbers);
void sort_deq(std::string &str);
#endif