// Phase 0: prove the toolchain, not the engine. If this passes, then C++20
// compiles, Eigen is fetched and linked, our own include path resolves, and
// ctest runs. Phase 1 starts testing actual behaviour.

#include <span>
#include <vector>

#include <Eigen/Dense>

#include "vllmcpp/version.h"

#include "check.h"

int main() {
  CHECK(vllmcpp::kPhase == 0);

  // C++20 is really on (std::span), not just requested in CMake.
  std::vector<float> buf{1.f, 2.f, 3.f};
  std::span<float> view{buf};
  CHECK(view.size() == 3);

  // Eigen is really linked and computes.
  Eigen::Matrix2f a;
  a << 1.f, 2.f,
       3.f, 4.f;
  Eigen::Vector2f x(1.f, 1.f);
  Eigen::Vector2f y = a * x;
  CHECK(y.isApprox(Eigen::Vector2f(3.f, 7.f)));

  return 0;
}
