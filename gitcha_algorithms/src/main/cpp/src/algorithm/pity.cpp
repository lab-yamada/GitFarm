#include "algorithm/pity.hpp"

bool pity_random(int base_chance, int max_fails, int current_fails)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int currentChance = base_chance + (current_fails * 10);
    currentChance = std::min(currentChance, 100);

    std::uniform_int_distribution<> dist(1, 100);
    int roll = dist(gen);

    return roll <= currentChance;
}