#pragma once

#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

#include "QuickMergeSort.hpp"

//prints data with given label
template <class RandomIt>
void print(RandomIt first, RandomIt last, std::string label = "")
{
    if (!label.empty())
    {
        std::cout << label << " :";
    }

    for (; first != last; first++)
    {
        std::cout << *first << " ";
    }
    std::cout << "\n";
}


template <class Container, class Compare = std::less<typename Container::value_type>>
bool shuffle_sort_test(Container& container, const std::string& label, Compare comp = Compare()){
    auto begin = std::begin(container);
    auto end = std::end(container);

    std::cout<<"Shuffling "<<label<<"\n";
    std::random_shuffle(begin, end);
    std::cout<<"Sorting "<<label<<"\n";
    quick_merge_sort(begin, end);

    std::cout<<"Testing "<<label<<"\n";
    if (!std::is_sorted(begin, end))
    {
        std::cout<<"Sorting "<<label<<" failed\n";
        return false;
    }
    
    std::cout<<"Testing "<<label<<" succeeded\n";
    return true;
}
