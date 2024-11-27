#ifndef ALGORITHM__HPP
#define ALGORITHM__HPP

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>

namespace com
{
    namespace yamadalab
    {
        namespace gitcha
        {
            int wrs_random(const std::vector<int>& weights);
            bool pity_random(int base_chance, int max_fails, int current_fails);
        }
    }
}

#endif