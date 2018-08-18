# QuickMergeSort (with pivot sampling)
This implementation of QuickXSort was created to check in practice the results presented by [this](https://arxiv.org/pdf/1803.05948.pdf) article.

## Benefits
1. This algorithm uses around 20% less comparisons than std::sort,
2. It requires o(n) space (recursion calls),
3. Average case is O(nlogn).

## Drawbacks
1. Not stable, (impossible to implement with this method)
2. Worst case is O(n^2),
3. Requires high number of swaps.

## Usage
In theory, this should be faster than std::sort when comparison operations are expensive and swaps are cheap.

## General information
To compile use make with g++ supporting -std=c++17
To sort objects with this method simply call:
```cpp
quick_merge_sort(Iterator begin, Iterator end, Comparison comp);
```
Default comparison is specifed as std::less
