# Phase 5 — prefix caching (optional)

The block hashing built in Phase 2 is dead code until something uses it. This phase wires
it into the scheduler so requests sharing a system prompt reuse the same physical blocks
instead of each recomputing the same prefix.

## Reference files

| vLLM | C++ |
|---|---|
| `vllm/v1/core/kv_cache_utils.py` — `get_request_block_hasher`, chained hashes | already built in Phase 2 |
| `vllm/v1/core/kv_cache_manager.py` — `get_computed_blocks` | `kv_cache.h` |
| `vllm/v1/core/sched/scheduler.py` — the pre-admission cache lookup | `src/scheduler.cpp` |

## Key idea

Before admitting a waiting request, hash its prompt blocks and ask the pool whether it
already holds them. A hit means those blocks are pinned by reference count and the request
skips computing them.

## Verify

Two requests sharing a long system prompt report a cache hit and skip the shared prefill.
Print the hit rate rather than asserting a specific number.
