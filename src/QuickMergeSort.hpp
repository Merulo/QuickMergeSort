#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

//main switches used for controlling the flow
static auto PIVOTSAMPLINGSIZE = 7;
static auto INSERTIONSORTSWITCH = 32;

//swaps two values if not sorted
template <class RandomIt, class Compare>
void swap_two_values(RandomIt i1, RandomIt i2, Compare comp)
{
    if (comp(*i2, *i1)) 
    {
        std::iter_swap(i1, i2);
    }
}

template <class RandomIt, class Compare>
void insertion_sort(RandomIt first, RandomIt last, Compare comp)
{
    for (RandomIt it = first; it != last; ++it) 
    {
        std::rotate(std::upper_bound(first, it, *it, comp), it, std::next(it));
    }
}

//standard partiton using last element as pivot
template <class RandomIt, class Compare>
RandomIt partition_pivot_at_end(RandomIt first, RandomIt last, Compare comp)
{
    std::iter_swap(first, last - 1);
    RandomIt pivot = last - 1;
    RandomIt i = first - 1;
    for (; first != last - 1; first++) 
    {
        if (comp(*first, *pivot)) 
        {
            i++;
            std::iter_swap(i, first);
        }
    }
    std::iter_swap(i + 1, last - 1);
    return i + 1;
}

//calculates which part is best for merge_sort and which for quick_merge_sort
//TODO: make it simpler
template <class Type>
Type calculate_best(Type v1, Type v2)
{
    Type result_v1 = v1 > v2 / 2 ? 0 : v1;
    Type result_v2 = v2 > v1 / 2 ? 0 : v2;
    Type best = std::max(result_v1, result_v2);

    return best == 0 ? std::max(v1, v2) : best;
}

//merges two ranges and puts results in buffer
template <class RandomIt, class Compare>
void merge_buffer(RandomIt first1, RandomIt last1, RandomIt first2, RandomIt last2, RandomIt buffer, Compare comp)
{
    while (first1 != last1)
    {
        if (first1 == first2 || first2 == last2)
        {
            std::swap_ranges(first1, last1, buffer);
            return;
        }
        if (comp(*first1, *first2))
        {
            std::iter_swap(first1, buffer);
            first1++;
        }
        else
        {
            std::iter_swap(first2, buffer);
            first2++;
        }
        buffer++;
    }
}

//merge sort using internal buffer
template <class RandomIt, class Compare>
void merge_sort(RandomIt first, RandomIt last, RandomIt buffer, Compare comp)
{
    if (std::distance(first, last) <= INSERTIONSORTSWITCH)
    {
        return insertion_sort(first, last, comp);
    }

    auto middle = first + (last - first) / 2;
    merge_sort(first, middle, buffer, comp);
    merge_sort(middle, last, buffer, comp);

    RandomIt buffer_end = std::swap_ranges(first, middle, buffer);
    merge_buffer(buffer, buffer_end, middle, last, first, comp);
}

//quickXsort implemented as QuickMergeSort
template <class RandomIt, class Compare = std::less<typename RandomIt::value_type> >
void quick_merge_sort(RandomIt first, RandomIt last, Compare comp = Compare())
{
    //for small n's use sorting network
    if (std::distance(first, last) <= INSERTIONSORTSWITCH)
    {
        return insertion_sort(first, last, comp);
    }
    //find good pivot as median of PIVOTSAMPLINGSIZE
    insertion_sort(first, first + PIVOTSAMPLINGSIZE, comp);
    auto done = (PIVOTSAMPLINGSIZE - 1) / 2;
    //swap values bigger than pivot to the end of data set
    std::swap_ranges(first + done + 1, first + PIVOTSAMPLINGSIZE, last - done);
    //partition by the given pivot
    auto middle = partition_pivot_at_end(first + done, last - done, comp);
    //calculate partition sizes
    auto I_1 = std::distance(first, middle);
    auto I_2 = std::distance(middle, last);
    //choose optimal sub data set for merge_sort
    if (calculate_best(I_1, I_2) == I_1)
    {
        merge_sort(first, middle, middle, comp);
        quick_merge_sort(middle, last, comp);
    }
    else
    {
        merge_sort(middle, last, first, comp);
        quick_merge_sort(first, middle, comp);
    }
}
