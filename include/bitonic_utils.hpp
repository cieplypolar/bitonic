#ifndef BITONIC_UTILS
#define BITONIC_UTILS

#include <cstddef>

#define ASC 1
#define DESC 0

size_t find_geq_pow_2(size_t n);
void bitonic_swap(long long* ar, size_t i, size_t j, int dir);

#endif /*BITONIC_UTILS*/