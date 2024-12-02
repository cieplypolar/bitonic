#ifndef BITONIC
#define BITONIC

#include <cstddef>

void bitonic_sort_plain(
  long long* ar,
  size_t n
);

void bitonic_sort_with_insertion(
  long long* ar,
  size_t n
);

void bitonic_sort_OMP(
  long long* ar,
  size_t n
);

void bitonic_sort_threads(
  long long* ar,
  size_t n
);

#endif /*BITONIC*/