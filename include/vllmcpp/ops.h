#pragma once
#include <span>
#include <vector>

namespace vllmcpp
{
    std::vector<float> softmax(std::span<const float> logits);
} // namespace vllmcpp
