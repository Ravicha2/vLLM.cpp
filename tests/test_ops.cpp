#include <cmath>
#include <span>
#include <vector>

#include "vllmcpp/ops.h"
#include "check.h"

int main() {
    std::vector<float> z{1.f, 2.f, 3.f};
    auto p = vllmcpp::softmax(std::span<const float>(z));
    float sum = 0.f;
    for (float x : p) {
        sum += x;
    }
    CHECK(std::abs(sum - 1.f) < 1e-5f);
    CHECK(p[2] > p[1] && p[1] > p[0]);
}