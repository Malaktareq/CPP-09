#include <iostream>
#include <vector>
#include <chrono>

void print_arr( std::vector <int>arr)
{
    for(unsigned long i =0; i< arr.size();i++)
        std::cout << arr.at(i) << " ";
    std::cout << std::endl;
}
void merge (std::vector <int>&arr ,std::vector <int>&leftarr, std::vector <int>&rightarr)
{
    int leftsize = leftarr.size();
    int rightsize = rightarr.size();
    int i=0;
    int j=0;
    int k=0;

    while ( i < leftsize && j < rightsize)
    {
        if (leftarr.at(i) <= rightarr.at(j))
        {
            arr.at(k) = leftarr.at(i);
            i++;
        }
        else
        {
            arr.at(k) = rightarr.at(j);
            j++;
        }
        k++;
    }
    for (; i < leftsize; i++)
    {
       arr.at(k) = leftarr.at(i);
       k++;
    }
    for (; j < rightsize; j++)
    {
       arr.at(k) = rightarr.at(j);
       k++;
    }
}
void mergeSort(std::vector <int>&arr)
{
    int length = arr.size();
    if (length < 2)
        return;
    int mid = arr.size() / 2;
    std::vector <int>leftarr(mid);
    std::vector <int>rightarr(arr.size() - mid);

    for (int i = 0 ; i < mid; i++)
        leftarr.at(i) = arr.at(i);
    for (int i = mid ; i < length;i++)
        rightarr.at(i - mid) = arr.at(i);
    mergeSort(leftarr);
    mergeSort(rightarr);

    merge(arr,leftarr,rightarr);

}

int main()
{
     auto start = std::chrono::high_resolution_clock::now();
    srand(time(NULL));
    std::vector <int>arr(1000);
    
    for (unsigned long i =0; i < arr.size(); i++ )
        arr.at(i) = rand() % 1000;
    print_arr(arr);
    mergeSort(arr);
    print_arr(arr);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    return (0);
}