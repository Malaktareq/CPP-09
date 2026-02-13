#include "PmergeMe.hpp"

void print_arr(std::vector<int> arr)
{
    for (size_t i = 0; i < arr.size(); i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}
std::vector<int> insertnumbers(std::string &ref)
{
    std::vector<int> numbers;
    std::stringstream ss(ref);
    int n;
    while (ss >> n)
        numbers.push_back(n);
    return (numbers);
}

void sort(std::string &str)
{
    std::vector<int> numbers = insertnumbers(str);

    std::cout << "Before sorting: ";
    print_arr(numbers);

    std::vector<int> sorted = algo(numbers);

    std::cout << "After sorting: ";
    print_arr(sorted);
}

std::vector<std::pair<int,int> > make_pairs(std::vector<int> numbers)
{
    std::vector<std::pair<int,int> > pairs;

    for (size_t i = 0; i < numbers.size(); i += 2)
    {
        if (i + 1 < numbers.size())
        {
            if (numbers[i] < numbers[i + 1])
                std::swap(numbers[i], numbers[i + 1]);

            pairs.push_back(std::make_pair(numbers[i], numbers[i + 1]));
        }
        else
            pairs.push_back(std::make_pair(numbers[i], -1));
    }
    return pairs;
}
std::vector<int> Jacobsthal(int n)
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

std::vector<int> Insert_order(std::vector<int> Jacob, int size)
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


struct ComparePairs {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
        return a.first < b.first;
    }
};

std::vector<int> binary_insert(std::vector<int>& pend, std::vector<std::pair<int,int> >& sorted_winners)
{
    std::vector<int> jacob = Jacobsthal(pend.size());
    std::vector<int> order = Insert_order(jacob, pend.size());
    std::vector<std::pair<int,int> >::iterator pos;
    std::vector<std::pair<int,int> >::iterator it;
    std::vector<int> main_chain;
    
    int add_pos = sorted_winners.size(); 

    for (size_t i = 0; i < order.size(); i++)
    {
        int idx = order[i] - 1; 
        if (idx >= (int)pend.size())
            continue;
        int loser = pend[idx];
        if (loser == -1) 
            continue;
        for(int j = 0; j < (int)sorted_winners.size(); j++)
        {
            if (sorted_winners[j].second == loser)
            {
                add_pos = j;
                break;
            }
        }
        it = sorted_winners.begin() + add_pos;
        std::pair<int,int> new_pair(loser, -1);
        pos = std::lower_bound(sorted_winners.begin(), it, new_pair, ComparePairs());
        sorted_winners.insert(pos, new_pair);
    }
    for (size_t i = 0; i < sorted_winners.size(); i++)
        main_chain.push_back(sorted_winners[i].first);
        
    return main_chain;
}

std::vector<int> algo(std::vector<int> numbers)
{
    if (numbers.size() <= 1) 
        return numbers;
    std::vector<std::pair<int,int> > pairs = make_pairs(numbers);
    std::vector<int> winners;
    for (size_t i = 0; i < pairs.size(); i++) 
        winners.push_back(pairs[i].first); 
    std::vector<int> sorted_winners_ints = algo(winners); 
    std::vector<bool> used(pairs.size(), false);
    std::vector<std::pair<int,int> > chain;
    std::vector<int> pend;

    for (size_t i = 0; i < sorted_winners_ints.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (!used[j] &&pairs[j].first == sorted_winners_ints[i])
            {
                chain.push_back(pairs[j]);
                pend.push_back(pairs[j].second);
                used[j] = true;
                break;
            }
        }
    }
    if (!pend.empty())
    {
        int b1 = pend[0];
        pend.erase(pend.begin());
        if (b1 != -1)
            chain.insert(chain.begin(), std::make_pair(b1, -1));
    }
    return binary_insert(pend, chain);
}


std::deque<int> insertnumbers_deq(std::string &ref)
{
    std::deque<int> numbers;
    std::stringstream ss(ref);
    int n;
    while (ss >> n)
        numbers.push_back(n);
    return (numbers);
}
void sort_deq(std::string &str)
{
    std::deque<int> numbers = insertnumbers_deq(str);
    std::deque<int> sorted = algo_deq(numbers);
}

std::deque<std::pair<int,int> > make_pairs_deq(std::deque<int> numbers)
{
    std::deque<std::pair<int,int> > pairs;

    for (size_t i = 0; i < numbers.size(); i += 2)
    {
        if (i + 1 < numbers.size())
        {
            if (numbers[i] < numbers[i + 1])
                std::swap(numbers[i], numbers[i + 1]);

            pairs.push_back(std::make_pair(numbers[i], numbers[i + 1]));
        }
        else
            pairs.push_back(std::make_pair(numbers[i], -1));
    }
    return pairs;
}
std::deque<int> Jacobsthal_deq(int n)
{
    std::deque<int> jacobsthal;
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

std::deque<int> Insert_order_deq(std::deque<int> Jacob, int size)
{
    std::deque<int> order;
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

std::deque<int> binary_insert_deq(std::deque<int>& pend, std::deque<std::pair<int,int> >& sorted_winners)
{
    std::deque<int> jacob = Jacobsthal_deq(pend.size());
    std::deque<int> order = Insert_order_deq(jacob, pend.size());
    std::deque<std::pair<int,int> >::iterator pos;
    std::deque<std::pair<int,int> >::iterator it;
    std::deque<int> main_chain;
    
    int add_pos = sorted_winners.size(); 

    for (size_t i = 0; i < order.size(); i++)
    {
        int idx = order[i] - 1; 
        if (idx >= (int)pend.size())
            continue;
        int loser = pend[idx];
        if (loser == -1) 
            continue;
        for(int j = 0; j < (int)sorted_winners.size(); j++)
        {
            if (sorted_winners[j].second == loser)
            {
                add_pos = j;
                break;
            }
        }
        it = sorted_winners.begin() + add_pos;
        std::pair<int,int> new_pair(loser, -1);
        pos = std::lower_bound(sorted_winners.begin(), it, new_pair, ComparePairs());
        sorted_winners.insert(pos, new_pair);
    }
    for (size_t i = 0; i < sorted_winners.size(); i++)
        main_chain.push_back(sorted_winners[i].first);
        
    return main_chain;
}

std::deque<int> algo_deq(std::deque<int> numbers)
{
    if (numbers.size() <= 1) 
        return numbers;
    std::deque<std::pair<int,int> > pairs = make_pairs_deq(numbers);
    std::deque<int> winners;
    for (size_t i = 0; i < pairs.size(); i++) 
        winners.push_back(pairs[i].first); 
    std::deque<int> sorted_winners_ints = algo_deq(winners); 

    std::deque<std::pair<int,int> > chain;
    std::deque<int> pend;

    for (size_t i = 0; i < sorted_winners_ints.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (pairs[j].first == sorted_winners_ints[i])
            {
                chain.push_back(pairs[j]);
                pend.push_back(pairs[j].second);
                break;
            }
        }
    }
    if (!pend.empty())
    {
        int b1 = pend[0];
        pend.erase(pend.begin());
        if (b1 != -1)
            chain.insert(chain.begin(), std::make_pair(b1, -1));
    }
    return binary_insert_deq(pend, chain);
}

PmergeMe::PmergeMe()
{

}
PmergeMe::PmergeMe(const PmergeMe& other) 
{ 
    (void)other; 
}
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    (void)other;
    return *this;
}
PmergeMe::~PmergeMe() {}

