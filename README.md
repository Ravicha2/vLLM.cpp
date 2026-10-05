# vLLM.cpp

A hands-on project for learning how large language models are served: the inference-engine
internals, the system design, and the low-level C++ that make it fast.

The method is to rebuild vLLM's core from scratch in C++ — paged attention, the block
manager, and the continuous-batching scheduler — one phase at a time. Reading vLLM's source
tells you what it does; rebuilding it is what makes the design stick.

The four things this is meant to build:

- **Serving LLMs.** What happens between an incoming request and a streamed token: batching,
  memory, throughput.
- **Inference engines.** The KV cache, PagedAttention, the scheduler, and how the pieces fit
  together.
- **System design.** The trade-off behind each piece: why one buffer per sequence falls
  apart, why blocks are better, when sharing a prefix pays off.
- **Low-level programming.** Numeric kernels in C++20 (softmax, RMSNorm, RoPE), and the
  tests that catch the silent-wrong-answer bugs.

```sh
cmake -S . -B build && cmake --build build
ctest --test-dir build --output-on-failure
./build/vllmcpp_demo
```

Start with [`docs/00-overview.md`](docs/00-overview.md), which maps every file here to the
vLLM source module it mirrors. Teaching material — the mission, lessons, and glossary — lives
in [`learning/`](learning/).

Currently at **phase 0** — the build skeleton. No engine yet.
