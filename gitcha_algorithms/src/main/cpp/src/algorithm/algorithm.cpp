#include "algorithm/algorithm.hpp"

com::yamadalab::gitcha::Algorithm::Algorithm()
{
    this->logger_ = std::make_shared<com::yamadalab::gitcha::Logger>();
}

com::yamadalab::gitcha::Algorithm::~Algorithm()
{

}

com::yamadalab::gitcha::Item com::yamadalab::gitcha::Algorithm::wrs_draw(const std::vector<com::yamadalab::gitcha::Item>& items)
{
    com::yamadalab::gitcha::Item result_item;

    int total_weight = 0;

    for (const com::yamadalab::gitcha::Item& item : items)
    {
        total_weight += item.get__weight();
    }

    this->logger_->info("WRS, total_weight : %d", total_weight);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, total_weight - 1);
    int random_val = dist(gen);

    this->logger_->info("WRS, random_val : %d", random_val);

    int current_weight = 0;
    for (const com::yamadalab::gitcha::Item& item : items)
    {
        current_weight += item.get__weight();

        if (random_val < current_weight)
        {
            this->logger_->info("!!!!!!!! WRS, Selected : [%s] !!!!!!!!", item.get__id().c_str());
            result_item = item;
            return result_item;
        }
    }

    this->logger_->info("WRS, current_weight : %d", current_weight);

    throw std::runtime_error("wrs_random: No item selected, check weights and input data");
}

bool com::yamadalab::gitcha::Algorithm::pity_draw(int probability, int fail_count)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    int current_chance = probability + (fail_count * 10);
    current_chance = std::min(current_chance, 100);

    std::uniform_int_distribution<> dist(1, 100);
    int roll = dist(gen);

    return roll <= current_chance;
}

std::string com::yamadalab::gitcha::Algorithm::draw(const std::vector<std::pair<std::string, std::pair<double, int>>> &raw_items)
{
    std::string draw_result_id = "";

    if (raw_items.empty())
    {
        draw_result_id = "9999";
        return draw_result_id;
    }

    com::yamadalab::gitcha::Item::SharedPtr item = std::make_shared<com::yamadalab::gitcha::Item>();
    std::vector<com::yamadalab::gitcha::Item> filtered_items;

    try
    {
        for (const std::pair<std::string, std::pair<double, int>> &raw_item : raw_items)
        {
            const std::string &id = raw_item.first;
            item->set__id(id);

            const std::pair<double, int> &raw_item_info = raw_item.second;
            const double &probability = raw_item_info.first;
            const int &fail_count = raw_item_info.second;

            const bool &is_pity = this->pity_draw(probability, fail_count);

            int weight = 0;

            if (is_pity == true)
            {
                this->logger_->info("Draw, Pity Weight : %s", id.c_str());
                weight = probability + PITY_WEIGHT;
            }
            else
            {
                weight = probability;
            }

            item->set__weight(weight);
            filtered_items.push_back(*item);
            this->logger_->info("Draw, Item: id = %s, probability = %f, weight = %d, fail_count = %d", id.c_str(), probability, weight, fail_count);
        }

        const com::yamadalab::gitcha::Item &drawed_item = this->wrs_draw(filtered_items);
        draw_result_id = drawed_item.get__id();
    }
    catch (const std::runtime_error &re)
    {
        this->logger_->info("Draw, %s", re.what());
        draw_result_id = "5000";
    }
    catch (const std::exception &e)
    {
        this->logger_->info("Draw, %s", e.what());
        draw_result_id = "5000";
    }

    return draw_result_id;
}