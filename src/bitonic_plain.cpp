#include "bitonic.hpp"
#include "bitonic_utils.hpp"
#include <vector>
#include <algorithm>
#include <limits>

void bit_merge(
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
  bit_merge(ar, left, mid, n/2, dir);
  bit_merge(ar, mid, right, n/2, dir);
}

void bit_sort(
  long long* ar,
  size_t left,
  size_t right,
  size_t n,
  int dir)
{
  if (n == 1) return;
  size_t mid = (left + right) / 2;
  bit_sort(ar, left, mid, n/2, ASC);
  bit_sort(ar, mid, right, n/2, DESC);
  bit_merge(ar, left, right, n, dir);
}

void bitonic_sort_plain(
  long long* ar,
  size_t n)
{
  if (n <= 1) return;
  size_t m = find_geq_pow_2(n);
  std::vector<long long> v(m, std::numeric_limits<long long>::max());
  std::copy(ar, ar + n, v.begin());
  bit_sort(v.data(), 0, m, m, ASC);
  std::copy(v.begin(), v.begin() + n, ar);
}