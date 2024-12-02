#include "bitonic_utils.hpp"
#include <algorithm>

size_t find_geq_pow_2(size_t n) {
  size_t res = 1;
  while (res < n) res <<= 1;
  return res;
}

void bitonic_swap(long long* ar, size_t i, size_t j, int dir) {
  if (dir == ASC) {
    if (ar[i] > ar[j]) std::swap(ar[i], ar[j]);
  } else {
    if (ar[i] < ar[j]) std::swap(ar[i], ar[j]);
  }
}