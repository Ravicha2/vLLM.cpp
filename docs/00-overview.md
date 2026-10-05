# vLLM.cpp — overview

A C++ rebuild of the machinery that makes vLLM vLLM: the paged KV cache, the block
manager, and the continuous-batching scheduler. Built to be read alongside the real vLLM
source, not instead of it.

Python vLLM is at <https://github.com/vllm-project/vllm>. Paths below are relative to that
repo.

## The source map

This is the spine of the project. Each phase's doc extends its own row.

| vLLM (Python) | vLLM.cpp | Phase |
|---|---|---|
| `vllm/v1/core/kv_cache_utils.py` — `KVCacheBlock`, `FreeKVCacheBlockQueue`, block hashing | `include/vllmcpp/block_pool.h` | 2 |
| `vllm/v1/core/block_pool.py` — `BlockPool` | `include/vllmcpp/block_pool.h` | 2 |
| `vllm/v1/core/single_type_kv_cache_manager.py` — per-request blocks, copy-on-write | `include/vllmcpp/kv_cache.h` | 2 |
| `vllm/v1/worker/block_table.py` — block table, slot mapping | `src/attention.cpp` (the gather loop) | 2 |
| `vllm/v1/core/sched/scheduler.py` — `Scheduler` | `src/scheduler.cpp` | 3 |
| `vllm/v1/core/sched/request_queue.py` — FCFS / priority queues | `include/vllmcpp/request_queue.h` | 3 |
| `vllm/v1/core/sched/output.py` — `SchedulerOutput` | `include/vllmcpp/scheduler.h` | 3 |
| `vllm/v1/engine/core.py` — `EngineCore.step` | `src/engine.cpp` | 3 |
| `vllm/v1/worker/gpu_model_runner.py` — `execute_model` | `src/model_runner.cpp` | 3 |

## Build

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/vllmcpp_demo
```

Eigen 3.4.0 is fetched and pinned by hash at configure time. Nothing else is needed beyond
a C++20 compiler and CMake 3.24+.

## Phase docs

- `00-overview.md` — this file
- `01-baseline.md` — the naive engine: contiguous KV cache, one sequence at a time
- `02-paged-attention.md` — blocks, the free list, hashing, copy-on-write
- `03-scheduler.md` — the continuous-batching step loop
- `04-real-model.md` — real weights, real tokenizer
- `05-prefix-caching.md` — reusing shared prefixes (optional)
