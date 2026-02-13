#include <iostream>
#include <vector>
#include <chrono>
#include "PmergeMe.hpp"
void print_arr( std::vector <int>arr)
{
    for(unsigned long i =0; i< arr.size();i++)
        std::cout << arr.at(i) << " ";
    std::cout << std::endl;
}

std::vector<std::pair<int,int> > PmergeMe::make_pairs(std::vector<int> numbers)
{
    std::vector<std::pair<int,int> > pairs;
    for (size_t i = 0; i < numbers.size(); i += 2)
    {
        if (i + 1 < numbers.size())
        {
            if (numbers[i] > numbers[i + 1])
                std::swap(numbers[i], numbers[i + 1]);
            pairs.push_back(std::make_pair(numbers[i], numbers[i + 1]));
        }
        else
            pairs.push_back(std::make_pair(-1, numbers[i]));   
    }
    return pairs;
}
std::vector<int> PmergeMe::Jacobsthal(int n)
{
    std::vector<int> jacobsthal;
    int num;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    num = 1;
    for (int i = 2; num < n; i++)
    {
        num = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
        jacobsthal.push_back(num);
    }
    return jacobsthal;
}

std::vector<int> PmergeMe::Insert_order(std::vector<int> Jacob, int size)
{
    std::vector<int> order;
    order.push_back(1);
    for (size_t i = 2; i < Jacob.size(); i++)
    {
        int current;
        if (Jacob[i] < size)
            current = Jacob[i];
        else
            current = size;
        for(int j = current; j > Jacob[i - 1]; j--)
            order.push_back(j);
    }
    return order;
}
std::vector<int> PmergeMe::insertnumbers(std::string &ref)
{
    std::vector<int> numbers;
    std::stringstream ss(ref);
    int n;
    while (ss >> n)
        numbers.push_back(n);
    return (numbers);
}
void PmergeMe::binary_insert(std::vector<std::pair<int,int> >& main_chain ,std::vector<std::pair<int,int> > main2_chain, std::vector<int> order)
{
    std::vector<int>::reverse_iterator it;
    std::vector<std::pair<int,int> >::iterator it2;

    it = order.rbegin();
    if (main2_chain[*it - 1].second == main_chain[*it].first)
        std::swap(main_chain[*it - 1], main_chain[*it]);
    it++;
    while (!order.empty())
    {
        int place = *it - 1;
        if(main2_chain[*it - 1].second ==  main_chain[*it].first)
            place = *it;
        for(int i = 0 ; i < *it ; i++)
        {
           it2 = std::lower_bound(main_chain.begin(), main_chain.end(), main2_chain[*it - 1].second);
           swap(main_chain[place], *it2);
        }
        it++;
    }
}
void PmergeMe::algo(std::vector<std::pair<int,int> >& pairs)
{
    std::vector<int> main_chain;
    std::vector<std::pair<int,int> >::iterator it;

    int len;
    if (pairs.empty())
        return;
    it = pairs.begin();
    for (; it != pairs.end(); ++it)
    {
        if (it->first != -1)
            main_chain.push_back(it->first);
    }
    len = main_chain.size() / 2;
    if (main_chain.size() % 2)
        len = main_chain.size() / 2 + 1;
    algo(pairs);
    binary_insert(pairs, make_pairs(main_chain), Insert_order(Jacobsthal(len), len));

}
void PmergeMe::sort(std::string &str)
{
    std::vector<int> numbers;
    std::vector<std::pair<int,int> > pairs;
    numbers = insertnumbers(str);
    pairs = make_pairs(numbers);
    std::cout << "Before sorting: ";
    for (size_t i = 0; i < numbers.size(); i++)
        std::cout << numbers[i] << " ";
    std::cout << std::endl;
    algo(pairs);
    std::cout << "After sorting: ";
    for (size_t i = 0; i < pairs.size(); i++)
        std::cout << pairs[i].first << " ";
    std::cout << std::endl;
     for (size_t i = 0; i < pairs.size(); i++)
        std::cout << pairs[i].second << " ";
        std::cout << std::endl;
}
int main()
{
    srand(time(NULL));
    std::vector <int>arr(10);
    
    for (unsigned long i =0; i < arr.size(); i++ )
        arr.at(i) = rand() % 10;
    print_arr(arr);
    mergeSort(arr);
    print_arr(arr);

    return (0);
}