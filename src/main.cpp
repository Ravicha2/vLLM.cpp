// Phase 0 demo: shows the toolchain works end to end. Phase 1 replaces this
// with the naive engine's generate loop.

#include <iostream>

#include <Eigen/Dense>

#include "vllmcpp/version.h"

int main() {
  Eigen::MatrixXf w = Eigen::MatrixXf::Random(4, 4);
  Eigen::VectorXf x = Eigen::VectorXf::Ones(4);

  std::cout << "vllmcpp — phase " << vllmcpp::kPhase << "\n"
            << "Eigen is linked: w * x = " << (w * x).transpose() << "\n"
            << "next: Phase 1, naive GPT + contiguous KV cache\n";
  return 0;
}
