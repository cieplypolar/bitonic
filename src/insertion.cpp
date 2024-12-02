#include "insertion.hpp"
#include <algorithm>
#include <functional>

void insertion_sort(
  long long* ar,
  size_t n)
{
  for (auto it = ar; it != ar + n; it++) {         
    auto const insertion_point = std::upper_bound(ar, it, *it); 
    std::rotate(insertion_point, it, it+1);         
  } 
}