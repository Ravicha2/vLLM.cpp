# Phase 3 — continuous batching

The scheduler. This is what makes vLLM a serving engine rather than a forward pass.

## Reference files

| vLLM | C++ |
|---|---|
| `vllm/v1/core/sched/scheduler.py` — `Scheduler` | `src/scheduler.cpp` |
| `vllm/v1/core/sched/request_queue.py` — FCFS / priority queues | `include/vllmcpp/request_queue.h` |
| `vllm/v1/core/sched/output.py` — `SchedulerOutput` | `include/vllmcpp/scheduler.h` |
| `vllm/v1/engine/core.py` — `EngineCore.step` | `src/engine.cpp` |
| `vllm/v1/worker/gpu_model_runner.py` — `execute_model` | `src/model_runner.cpp` |

## Key idea

From vLLM's own source comment: *there is no decoding phase nor prefill phase.* Each
request just tracks `num_computed_tokens`; every step the scheduler tops it up. A request
stops being a prefill the moment it catches up — no re-queue, no phase switch, no barrier.

The step loop is `schedule() → execute_model() → update_from_output()`. Chunked prefill is
just `min(num_new_tokens, budget)`. Preemption frees a request's blocks and resets its
count to zero — recompute, never swap.

## Verify

A short request submitted *after* a long one finishes *first*. That one assertion is what
"continuous batching" means.
