# Phase 1 — the baseline (naive engine)

Build the thing vLLM replaces, first. Contiguous KV cache, one sequence at a time, no
scheduler. Slow and memory-hungry on purpose: it's the yardstick every later phase gets
measured against.

## Files

| C++ | holds |
|---|---|
| `include/vllmcpp/tensor.h` | thin Eigen-backed Tensor |
| `include/vllmcpp/ops.h` | matmul, softmax, RMSNorm, RoPE, SiLU |
| `include/vllmcpp/model.h` | Llama-style decoder block |
| `include/vllmcpp/sampler.h` | greedy, temperature, top-p |
| `src/kv_cache_naive.cpp` | contiguous per-sequence KV buffer |

No vLLM file maps here — this is the "before" picture.

## Key idea

A sequence's K/V sits in one contiguous buffer sized for the maximum length, used or not.
Attention reads it directly. Simple and correct, and it falls apart the moment you want
many sequences at once.

## Verify

Incremental decode (one token at a time, growing the cache) must equal a full recompute of
the same prefix. Catches RoPE and position-index bugs, which are the classic
silent-wrong-answer failures.
