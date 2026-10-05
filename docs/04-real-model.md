# Phase 4 — a real model

Everything so far runs on random weights. This phase makes it real: actual weights, an
actual tokenizer, and a chat template.

## Files

| C++ | holds |
|---|---|
| `src/model_loader.cpp` | reads weights into `model.h` structures |
| `src/tokenizer.cpp` | encode / decode |
| `src/engine.cpp` | grows a server loop around the Phase 3 step |

## Key idea

Model and weight format are **pinned here**, against measured CPU speed, not guessed
earlier. If Eigen's matmul is the bottleneck, the escape hatch is macOS's built-in
Accelerate (`cblas_sgemm`) — one shim function, no new dependency.

## Verify

Generated tokens must match a Python reference (`transformers` or `llama.cpp`) given the
same prompt and greedy sampling. This catches a port that runs but has quietly misread a
weight layout.
