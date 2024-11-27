#include "algorithm/algorithm.hpp"

int com::yamadalab::gitcha::wrs_random(const std::vector<int>& weights)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> dist(weights.begin(), weights.end());

    return dist(gen);
}

bool com::yamadalab::gitcha::pity_random(int base_chance, int max_fails, int current_fails)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int current_chance = base_chance + (current_fails * 10);
    current_chance = std::min(current_chance, 100);

    std::uniform_int_distribution<> dist(1, 100);
    int roll = dist(gen);

    return roll <= current_chance;
}