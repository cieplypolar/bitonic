#include "insertion.hpp"
#include "bitonic.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

signed main() {
  size_t n;
  std::cin >> n;
  std::vector<long long> v(n);
  for (auto& num : v)
    std::cin >> num;

  std::vector<long long> stl_sort_v(v), bitonic_plain_v(v), bitonic_insertion_v(v), bitonic_omp_v(v), bitonic_thread_v(v);

  /*------------------------------------------------------------------------------------------*/
  auto start_time = std::chrono::high_resolution_clock::now();
  sort(stl_sort_v.begin(), stl_sort_v.end());
  auto end_time = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  std::cout << "STL sort time: " << duration.count() << " milliseconds" << std::endl;

  /*------------------------------------------------------------------------------------------*/
  start_time = std::chrono::high_resolution_clock::now();
  bitonic_sort_plain(bitonic_plain_v.data(), bitonic_plain_v.size());
  end_time = std::chrono::high_resolution_clock::now();

  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  std::cout << "Bitonic sort plain time: " << duration.count() << " milliseconds" << std::endl;

  /*------------------------------------------------------------------------------------------*/
  start_time = std::chrono::high_resolution_clock::now();
  bitonic_sort_with_insertion(bitonic_insertion_v.data(), bitonic_insertion_v.size());
  end_time = std::chrono::high_resolution_clock::now();

  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  std::cout << "Bitonic sort with insertion time: " << duration.count() << " milliseconds" << std::endl;

  /*------------------------------------------------------------------------------------------*/
  start_time = std::chrono::high_resolution_clock::now();
  bitonic_sort_OMP(bitonic_omp_v.data(), bitonic_omp_v.size());
  end_time = std::chrono::high_resolution_clock::now();

  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  std::cout << "Bitonic sort with OMP time: " << duration.count() << " milliseconds" << std::endl;

   /*------------------------------------------------------------------------------------------*/
  start_time = std::chrono::high_resolution_clock::now();
  bitonic_sort_threads(bitonic_thread_v.data(), bitonic_thread_v.size());
  end_time = std::chrono::high_resolution_clock::now();

  duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  std::cout << "Bitonic sort with threads time: " << duration.count() << " milliseconds" << std::endl;
  return 0;
}