#include "bitonic.hpp"
#include "bitonic_utils.hpp"
#include "insertion.hpp"
#include <vector>
#include <algorithm>
#include <limits>
#include <thread>

extern size_t INSRT_CONST;
static size_t THREADS = 16; /* this should be 2^k */
static size_t THREAD_BOUND = 512;

void bit_merge_thread(
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
  bit_merge_thread(ar, left, mid, n/2, dir);
  bit_merge_thread(ar, mid, right, n/2, dir);
}

void bit_sort_thread(
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
  bit_sort_thread(ar, left, mid, n/2, ASC);
  bit_sort_thread(ar, mid, right, n/2, DESC);
  bit_merge_thread(ar, left, right, n, dir);
}

void bitonic_sort_threads(
  long long* ar,
  size_t n)
{
  if (n <= 1) return;
  size_t m = find_geq_pow_2(n);
  std::vector<long long> v(m, std::numeric_limits<long long>::max());
  std::copy(ar, ar + n, v.begin());

  if (m >= THREAD_BOUND) {
    for (size_t block_size = m / THREADS, num_of_working_threads = THREADS, phase = 0; block_size <= m; block_size <<= 1, num_of_working_threads >>= 1, phase++) {
      std::vector<std::thread> thread_pool(num_of_working_threads);

      if (phase == 0) {
        for (size_t i = 0; i < num_of_working_threads; ++i) {
          size_t dir = !(i & 1);
          thread_pool[i] =
            std::thread(
              bit_sort_thread,
              v.data(),
              i * block_size,
              (i + 1) * block_size,
              block_size,
              dir);
        }
      } else {
        for (size_t i = 0; i < num_of_working_threads; ++i) {
          size_t dir = !(i & 1);
          thread_pool[i] =
            std::thread(
              bit_merge_thread,
              v.data(),
              i * block_size,
              (i + 1) * block_size,
              block_size,
              dir);
        }
      }

      for (size_t i = 0; i < num_of_working_threads; ++i)
        thread_pool[i].join();

    }
  } else {
    bit_sort_thread(v.data(), 0, m, m, ASC);
  }
  std::copy(v.begin(), v.begin() + n, ar);
}

