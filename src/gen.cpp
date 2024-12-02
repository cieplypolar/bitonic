#include <iostream>
#include <limits>
#include <random>
#include <vector>

signed main() {
  size_t n;
  std::cin >> n;

  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<long long> dist(
    std::numeric_limits<long long>::min(),
    std::numeric_limits<long long>::max()
  );
  std::vector<long long> numbers(n);

  for (size_t i = 0; i < n; i++)
    numbers[i] = dist(gen);

  std::cout << n << '\n';
  for (size_t i = 0; i < n; ++i) {
    if (i > 0) std::cout << ' ';
    std::cout << numbers[i];
  }
  std::cout << n << '\n';

  return 0;
}
