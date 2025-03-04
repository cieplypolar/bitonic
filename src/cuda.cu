#include "moderngpu/transform.hxx"
#include "moderngpu/memory.hxx"
#include "moderngpu/context.hxx"
#include <vector>
#include <iostream>
#include <chrono>
#include <algorithm>
using namespace std;

int find_geq_pow_2(int n) {
  int res = 1;
  while (res < n) res <<= 1;
  return res;
}

void gpusort(int n, long long* dev_a) {
  mgpu::standard_context_t context(false, 0);
  if (n <= 1) return;
  int m = find_geq_pow_2(n);
  mgpu::mem_t<long long> v_mem = mgpu::fill(std::numeric_limits<long long>::max(), m, context);
  long long *v = v_mem.data();
  mgpu::dtod(v, dev_a, n);

  for (int k = 2; k <= m; k <<= 1) { // loop subtask size
    for (int half = k >> 1; half > 0; half >>= 1) { // merging
      mgpu::transform(
        []MGPU_DEVICE(int index, int k, int half, long long *ar) {
          int j = index + half;
          if ((index & half) == 0) {
            if ((index & k) == 0) { //ascending
              if (ar[index] > ar[j]) {
                long long tmp = ar[index];
                ar[index] = ar[j];
                ar[j] = tmp;
              }
            } else {
              if (ar[index] < ar[j]) {
                long long tmp = ar[index];
                ar[index] = ar[j];
                ar[j] = tmp;
              }
            }
          }
        },
        m,
        context,
        k,
        half,
        v
      );
    }
  }

  mgpu::dtod(dev_a, v, n);
}


int main() {
  int n; std::cin >> n;
  std::vector<long long> v(n);
  for (auto &e : v) {
    std::cin >> e;
  }
  long long* dev_a;
  cudaMalloc(&dev_a, n * sizeof(long long));
  cudaMemcpy(dev_a, v.data(), n * sizeof(long long), cudaMemcpyHostToDevice);
  
  auto start_time = std::chrono::high_resolution_clock::now();
  gpusort(n, dev_a);
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
  std::cout << "CUDA sort time: " << duration.count() << " milliseconds" << std::endl;
  
  std::vector<long long> sorted(n);
  cudaMemcpy(sorted.data(), dev_a, n * sizeof(long long), cudaMemcpyDeviceToHost);
  std::sort(v.begin(), v.end());
  bool ok = true;
  for (size_t i = 0; i < n; ++i) {
    if (v[i] != sorted[i]) ok = false;
  }
  if (ok) {
    std::cout << "OK - bitonic sort on " << n << " elements\n";
  } else {
    std::cout << "Error - bitonic sort on " << n << " elements\n";
  }
}