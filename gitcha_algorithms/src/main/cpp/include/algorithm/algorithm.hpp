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

#include "utils/logger.hpp"
#include "domain/item.hpp"

constexpr int PITY_WEIGHT = 1;

namespace com
{
    namespace yamadalab
    {
        namespace gitcha
        {
            class Algorithm
            {
            private:
                com::yamadalab::gitcha::Logger::SharedPtr logger_;

                com::yamadalab::gitcha::Item wrs_draw(const std::vector<com::yamadalab::gitcha::Item>& items);
                bool pity_draw(int probability, int fail_count);

            public:
                explicit Algorithm();
                virtual ~Algorithm();
                std::string draw(const std::vector<std::pair<std::string, std::pair<double, int>>> &items);

            public:
                using SharedPtr = std::shared_ptr<Algorithm>;

            };
        }
    }
}

#endif