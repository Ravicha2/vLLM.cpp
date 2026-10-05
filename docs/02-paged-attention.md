# Phase 2 — PagedAttention

The heart of vLLM. Instead of one buffer per sequence, every sequence shares a pool of
fixed-size blocks and holds a table saying which blocks are its own.

## Reference files

| vLLM | C++ |
|---|---|
| `vllm/v1/core/kv_cache_utils.py` — `KVCacheBlock`, `FreeKVCacheBlockQueue`, block hashing | `include/vllmcpp/block_pool.h` |
| `vllm/v1/core/block_pool.py` — `BlockPool` | `include/vllmcpp/block_pool.h` |
| `vllm/v1/core/single_type_kv_cache_manager.py` — per-request blocks, copy-on-write | `include/vllmcpp/kv_cache.h` |
| `vllm/v1/worker/block_table.py` — block table, slot mapping | `src/attention.cpp` (the gather loop) |

## Key idea

One line carries the whole design:

```
slot = block_table[req][position / block_size] * block_size + (position % block_size)
```

Attention scatters new K/V to that slot and gathers history by walking the block table.
That extra hop through a table is the trick — K/V no longer has to be contiguous.

Supporting pieces: blocks are 16 tokens; a free list orders them LRU; a block's hash is
chained from its parent's, which is how two requests sharing a prefix land on the same
blocks. The hash is cleared when a block is handed out and never when it's freed.

## Verify

Paged output must equal naive output (Phase 1) to within float epsilon. That equality is
the correctness proof for the entire project. Also: two requests sharing a prefix must
resolve to the same physical block ids.
