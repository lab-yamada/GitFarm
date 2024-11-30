#include "algorithm/algorithm.hpp"
#include <memory>
#include <vector>
#include <utility>
#include <iostream> 

com::yamadalab::gitfarm::Algorithm::SharedPtr algo = std::make_shared<com::yamadalab::gitfarm::Algorithm>();

void wrs_test()
{
    std::vector<std::pair<std::string, std::pair<double, int>>> items =
    {
        {"Item1", {5.1, 3}},
        {"Item2", {0.2, 5}},
        {"Item3", {0.3, 7}},
        {"Item4", {0.4, 9}},
        {"Item5", {0.5, 1}},
        {"Item6", {0.6, 2}},
        {"Item7", {0.7, 3}},
        {"Item8", {0.8, 4}},
        {"Item9", {0.9, 5}},
        {"Item10", {1.0, 6}},
        {"Item11", {1.1, 1}},
        {"Item12", {1.2, 2}},

    };

    const std::string &result = algo->draw(items);
    printf("Item : %s\n", result.c_str());
}

int main(int argc, const char *const *argv)
{
    wrs_test();
    return 0;
}