#include "benchmark/benchmark.h"

#include <set>
#include <vector>
#include <random>

static void bit_vector_push_back(benchmark::State &state) {

  while (state.KeepRunning()) {
    std::vector<bool> v;
    v.reserve(state.range(0));
    for (int i = 0, i_end = state.range(0); i < i_end; i++) {
      v.push_back(i);
    }
  }
}
BENCHMARK(bit_vector_push_back)->Range(8, 8 << 10);

static void bit_vector_access(benchmark::State &state) {

  while (state.KeepRunning()) {
    std::vector<bool> v;
    state.PauseTiming();
    for (int i = 0, i_end = state.range(0); i < i_end; i++) {
      const bool random_bit = rand() % 2;
      v.push_back(random_bit);
    }
    state.ResumeTiming();
    for (int i = 0, i_end = state.range(0); i < i_end; i++) {
      benchmark::DoNotOptimize(v[i]);
    }
  }
}
BENCHMARK(bit_vector_access)->Range(8, 8 << 10);

BENCHMARK_MAIN();
