# QuickMergeSort (with pivot sampling)
This implementation of QuickXSort was created to check in practice the results presented by [this](https://arxiv.org/pdf/1803.05948.pdf) article.

## Benefits
This algorithm uses around 20% less comparisons than std::sort,
It requires o(n) space (recursion calls),
Average case is O(nlogn).

## Drawbacks
Not stable, (impossible to implement with this method)
Worst case is O(n^2),
Requires high number of swaps.

## Usage
In theory, this should be faster than std::sort when comparison operations are expensive and swaps are cheap.

## General information
To compile use make with g++ supporting -std=c++17
To sort objects with this method simply call:
```cpp
quick_merge_sort(Iterator begin, Iterator end, Comparison comp);
```
Default comparison is specifed as std::less
