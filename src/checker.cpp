#include "insertion.hpp"
#include "bitonic.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <functional>

bool check_sort(
  const std::vector<long long>& v,
  std::function<void(long long*, size_t)> sort_to_test) {
  std::vector<long long> test_v(v), stl_sort_v(v);

  sort_to_test(test_v.data(), test_v.size());
  sort(stl_sort_v.begin(), stl_sort_v.end());

  for (size_t i = 0; i < v.size(); ++i) {
    if (test_v[i] != stl_sort_v[i]) return false;
  }
  return true;
}

signed main() {
  size_t n;
  std::cin >> n;
  std::vector<long long> v(n);
  for (auto& num : v)
    std::cin >> num;

  /*------------------------------------------------------------------------------------------*/  
  if (check_sort(v, insertion_sort)) {
    std::cout << "OK - Insertion sort\n";
  } else {
    std::cout << "Error - Insertion sort\n";
  }

  /*------------------------------------------------------------------------------------------*/
  if (check_sort(v, bitonic_sort_plain)) {
    std::cout << "OK - Bitonic sort plain\n";
  } else {
    std::cout << "Error - Bitonic sort plain\n";
  }

  /*------------------------------------------------------------------------------------------*/
  if (check_sort(v, bitonic_sort_with_insertion)) {
    std::cout << "OK - Bitonic sort insertion\n";
  } else {
    std::cout << "Error - Bitonic sort insertion\n";
  }

  /*------------------------------------------------------------------------------------------*/
  if (check_sort(v, bitonic_sort_OMP)) {
    std::cout << "OK - Bitonic sort OMP\n";
  } else {
    std::cout << "Error - Bitonic sort OMP\n";
  }

  /*------------------------------------------------------------------------------------------*/
  if (check_sort(v, bitonic_sort_threads)) {
    std::cout << "OK - Bitonic sort threads\n";
  } else {
    std::cout << "Error - Bitonic sort threads\n";
  }

  return 0;
}