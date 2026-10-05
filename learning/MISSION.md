# Mission: How inference engines work — by rebuilding vLLM's core in C++

## Why
I want to work at the level of inference-engine internals — the memory management,
batching, and low-level C++ that decide whether an LLM server is fast or not. Rebuilding
vLLM's core (paged KV cache, block manager, continuous-batching scheduler) is the vehicle:
building it is how I actually learn it, not just reading about it.

## Success looks like
- I can implement a KV cache, a paged block manager, and a continuous-batching scheduler
  from scratch in C++, and explain the trade-off each one makes.
- I can open vLLM's `vllm/v1/core/...` source and map it, line for line, onto my own code.
- I can write low-level numeric kernels (softmax, RMSNorm, RoPE) that stay correct on edge
  cases, and I have tests that catch the silent-wrong-answer bugs.
- I finish at least phases 1–3 of this repo's plan.

## Constraints
- Learning by building inside this repo (C++20, Eigen, CMake, ctest), one phase at a time.
- Prefer plain everyday words over jargon; explain a new term the first time it appears.
- No GPU yet — pure CPU float32. Speed is not the goal; understanding is.

## Out of scope (for now)
- Training or fine-tuning models.
- Production deployment and ops.
- CUDA / GPU kernel programming.
- Model-architecture research (new attention variants).
