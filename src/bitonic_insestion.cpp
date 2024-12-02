#include "bitonic.hpp"
#include "bitonic_utils.hpp"
#include "insertion.hpp"
#include <vector>
#include <algorithm>
#include <limits>

size_t INSRT_CONST = 128;

void bit_merge_insertion(
  long long* ar,
  size_t left,
  size_t right,
  size_t n,
  int dir)
{
  if (n == 1) return;
  size_t mid = (left + right) / 2;
  size_t half = n / 2;
  for (size_t i = 0; i < half; ++i)
    bitonic_swap(ar, left + i, mid + i, dir);
  bit_merge_insertion(ar, left, mid, n/2, dir);
  bit_merge_insertion(ar, mid, right, n/2, dir);
}

void bit_sort_insertion(
  long long* ar,
  size_t left,
  size_t right,
  size_t n,
  int dir)
{
  if (n <= INSRT_CONST) {
    insertion_sort(ar + left, n);
    if (dir == DESC) std::reverse(ar + left, ar + left + n); 
    return;
  }
  size_t mid = (left + right) / 2;
  bit_sort_insertion(ar, left, mid, n/2, ASC);
  bit_sort_insertion(ar, mid, right, n/2, DESC);
  bit_merge_insertion(ar, left, right, n, dir);
}

void bitonic_sort_with_insertion(
  long long* ar,
  size_t n)
{
  if (n <= 1) return;
  size_t m = find_geq_pow_2(n);
  std::vector<long long> v(m, std::numeric_limits<long long>::max());
  std::copy(ar, ar + n, v.begin());
  bit_sort_insertion(v.data(), 0, m, m, ASC);
  std::copy(v.begin(), v.begin() + n, ar);
}

