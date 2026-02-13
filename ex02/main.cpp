#include "PmergeMe.hpp"

int check_valid(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (!std::isdigit(str[i]) && !std::isspace(str[i]))
            return 0;
    }
    return 1;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " 3 1 4 2 5" << std::endl;
        return 1;
    }
    std::string input_str;
    for (int i = 1; i < argc; i++)
    {
        input_str += argv[i];
        input_str += " "; 
    }
    std::clock_t start = std::clock();
    sort(input_str);
    std::clock_t end = std::clock();
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken by vector sorting: " << time_taken << " seconds" << std::endl;

    start = std::clock();
    sort_deq(input_str);
    end = std::clock();
    time_taken = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken by deque sorting: " << time_taken << " seconds" << std::endl;

    return 0;
}