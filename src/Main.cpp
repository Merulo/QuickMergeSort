#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Utills.hpp"

int main()
{
    std::vector<int> data(1000);
    auto begin = std::begin(data);
    auto end = std::end(data);
    std::iota(begin, end, 0);

    if ( !shuffle_sort_test(data, "ascending unique values")){
        return 1;
    }

    auto comp = [](int rhs, int lhs) {
        return rhs > lhs;
    };

    if ( !shuffle_sort_test(data, "descending unique values", comp)){
        return 1;
    }

    //shuffle to randomly replace 50% of data with 0's
    std::random_shuffle(begin, end); 
    std::fill(begin + data.size() / 2, end, 0);

    if ( !shuffle_sort_test(data, "descending not unique values", comp)){
        return 1;
    }

    //shuffle and trim data
    std::random_shuffle(begin, end); 
    data.resize(25);
    end = std::end(data);

    print(begin, end);
    if ( !shuffle_sort_test(data, "ascending unique trimmed values")){
        return 1;
    }
    print(begin, end);

    return 0;
}