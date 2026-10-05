#pragma once

#include <cstdio>
#include <cstdlib>

// CHECK, not assert: the default build type is Release, where NDEBUG makes
// <cassert> a no-op and every test would silently pass.
#define CHECK(cond)                                                      \
  do {                                                                   \
    if (!(cond)) {                                                       \
      std::fprintf(stderr, "CHECK failed: %s\n  at %s:%d\n", #cond,      \
                   __FILE__, __LINE__);                                  \
      std::exit(1);                                                      \
    }                                                                    \
  } while (0)
