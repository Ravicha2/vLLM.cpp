# vLLM.cpp Learning Resources

## Knowledge

- [Paper: _Efficient Memory Management for Large Language Model Serving with PagedAttention_ — Kwon et al., SOSP 2023 (arXiv:2309.06180)](https://arxiv.org/abs/2309.06180)
  The paper that introduced vLLM and PagedAttention. Use for: why KV cache memory is the
  bottleneck, the block/table design, and the throughput numbers the whole project is
  chasing. Primary source — prefer it over blog summaries.
- [vLLM docs: Architecture Overview](https://docs.vllm.ai/en/latest/design/arch_overview/)
  Official description of the engine's moving parts. Use for: the map from a request to the
  scheduler/engine-core, before reading source.
- [vLLM source — `vllm-project/vllm`](https://github.com/vllm-project/vllm)
  The reference implementation this repo mirrors. Use for: the `vllm/v1/core/` modules named
  in `docs/00-overview.md` — `kv_cache_utils.py`, `block_pool.py`, `sched/scheduler.py`.
- [vLLM blog: "Anatomy of a High-Throughput LLM Inference System"](https://vllm.ai/blog/2025-09-05-anatomy-of-vllm)
  Team-written systems overview of scheduling, paged attention, and continuous batching.
  Use for: the big-picture trade-offs between phases.
- [Blog: _KV Caching Explained_ — not-lain (Hugging Face)](https://huggingface.co/blog/not-lain/kv-caching)
  Clear walkthrough of why K/V are cached at decode time. Use for: grounding Phase 1's
  "why recompute is wasteful" before you write the cache.
- [Reference: _LogSumExp_ — Wikipedia](https://en.wikipedia.org/wiki/LogSumExp)
  The identity behind the numerically-stable softmax. Use for: understanding *why*
  subtracting the max is mathematically free, and what to do when you need `log(softmax)`.
- [Reference: `exp`, `expf` — cppreference](https://en.cppreference.com/w/c/numeric/math/exp)
  Behaviour of the C exponential, including overflow to infinity. Use for: verifying the
  float-overflow threshold that Lesson 0001 turns on.

## Wisdom (Communities)

- [vLLM GitHub Discussions](https://github.com/vllm-project/vllm/discussions)
  Maintainers and contributors answer design questions here. Use for: "why is it built this
  way?" questions that the source alone doesn't answer.
- [r/LocalLLaMA](https://www.reddit.com/r/LocalLLaMA/)
  Practitioners running and benchmarking real serving stacks. Use for: sanity-checking
  throughput/memory intuitions against the real world.

## Gaps

- No trusted resource yet on writing ML numerics in **C++ specifically** (C++ float
  behaviour, testing silent-wrong-answer bugs). Candidate: search for a numerical-methods
  or HPC text during a later session.
- No resource on building a batching **scheduler** from first principles (the material is
  mostly inside vLLM's own source). Candidate: read `sched/scheduler.py` directly in Phase 3.
