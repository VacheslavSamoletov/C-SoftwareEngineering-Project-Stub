#include <benchmark/benchmark.h>

#include <cstddef>

#include "gbm.hpp"

static void BM_GenerateGbmPath(benchmark::State& state) {
    const auto n_steps = static_cast<std::size_t>(state.range(0));
    for (auto _ : state) {
        benchmark::DoNotOptimize(mc::generate_gbm_path(100.0, 0.05, 0.2, 1.0, n_steps, 42));
    }
    state.SetItemsProcessed(state.iterations() * state.range(0));
}

BENCHMARK(BM_GenerateGbmPath)->Arg(252)->Arg(10000)->Arg(1000000)->Unit(benchmark::kMicrosecond);
