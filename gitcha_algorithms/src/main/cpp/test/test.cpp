#include "algorithm/pity.hpp"
#include "algorithm/wrs.hpp"

void pity_test()
{
    int base_chance = 5;
    int max_fails = 10;
    int current_fails = 0;

    for (int attempt = 1; attempt <= 20; ++attempt)
    {
        bool success = pity_random(base_chance, max_fails, current_fails);
        std::cout << "Attempt " << attempt << ": " << (success ? "Success!" : "Fail") << std::endl;

        if (success)
        {
            current_fails = 0;
        }
        else
        {
            ++current_fails;
        }
    }
}

void wrs_test()
{
    std::vector<std::string> items = {"A", "B", "C", "D"};
    std::vector<int> weights = {10, 20, 30, 40};

    int index = wrs_random(weights);

    std::cout << "Selected item: " << items[index] << std::endl;
}

int main(int argc, const char *const *argv)
{
    
    wrs_test();
    return 0;
}