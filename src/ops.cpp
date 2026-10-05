#include "../include/vllmcpp/ops.h"
#include <algorithm>
#include <cmath>
#include <numeric>

namespace vllmcpp {
std::vector<float> softmax(std::span<const float> logits) {
    std::vector<float> out(logits.begin(), logits.end());
    if (out.empty()) return out;
    float m = *std::max_element(out.begin(), out.end());
    float sum = 0.f;
    for (float& v : out) {
        v = std::exp(v-m);
        sum += v;
    }
    for (float& v : out) {
        v /= sum;
    }
    return out;
}
}