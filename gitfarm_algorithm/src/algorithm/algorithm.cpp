#include "algorithm/algorithm.hpp"

com::yamadalab::gitfarm::Algorithm::Algorithm()
{
}

com::yamadalab::gitfarm::Algorithm::~Algorithm()
{

}

std::vector<com::yamadalab::gitfarm::Item> com::yamadalab::gitfarm::Algorithm::get__items()
{
    return this->items_;
}

void com::yamadalab::gitfarm::Algorithm::set__items(const std::vector<com::yamadalab::gitfarm::Item> &items)
{
    this->items_ = items;
}

com::yamadalab::gitfarm::Item com::yamadalab::gitfarm::Algorithm::wrs_draw(const std::vector<com::yamadalab::gitfarm::Item>& items)
{
    com::yamadalab::gitfarm::Item result_item;

    int total_weight = 0;

    for (const com::yamadalab::gitfarm::Item& item : items)
    {
        total_weight += item.get__weight();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, total_weight - 1);
    int random_val = dist(gen);

    int current_weight = 0;
    for (const com::yamadalab::gitfarm::Item& item : items)
    {
        current_weight += item.get__weight();

        if (random_val < current_weight)
        {
            result_item = item;
            return result_item;
        }
    }

    throw std::runtime_error("wrs_random: No item selected, check weights and input data");
}

bool com::yamadalab::gitfarm::Algorithm::pity_draw(int probability, int fail_count)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int current_chance = probability + (fail_count * 10);
    current_chance = std::min(current_chance, 100);

    std::uniform_int_distribution<> dist(1, 100);
    int roll = dist(gen);

    return roll <= current_chance;
}