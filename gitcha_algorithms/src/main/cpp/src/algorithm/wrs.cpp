#include "algorithm/wrs.hpp"

int wrs_random(const std::vector<int>& weights)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> dist(weights.begin(), weights.end());

    return dist(gen);
}