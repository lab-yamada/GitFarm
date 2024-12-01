#ifndef ALGORITHM__HPP
#define ALGORITHM__HPP

#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "domain/item.hpp"

constexpr int PITY_WEIGHT = 1;

namespace com
{
    namespace yamadalab
    {
        namespace gitfarm
        {
            class Algorithm
            {
            private:
                std::vector<com::yamadalab::gitfarm::Item> items_;

            public:
                explicit Algorithm();
                virtual ~Algorithm();
                std::vector<com::yamadalab::gitfarm::Item> get__items();
                void set__items(const std::vector<com::yamadalab::gitfarm::Item> &items);
                com::yamadalab::gitfarm::Item wrs_draw(const std::vector<com::yamadalab::gitfarm::Item>& items);
                bool pity_draw(int probability, int fail_count);

            public:
                using SharedPtr = std::shared_ptr<Algorithm>;

            };
        }
    }
}

#endif