#ifndef GITFARM_ALGORITHM__HPP
#define GITFARM_ALGORITHM__HPP

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
#include "domain/user.hpp"

constexpr double PITY_WEIGHT = 0.00001;
constexpr int PITY_MAX_WEIGHT = 100;

namespace com::yamadalab::gitfarm
{
    class Algorithm final
    {
    private:
        std::vector<Item> items_;
        User::SharedPtr user_ = nullptr;
        [[nodiscard]] bool is_ready_to_draw() const;
        void weight_items_by_grade();
        void weight_items_by_pity();
        [[nodiscard]] Item::SharedPtr weight_random_select() const;
        static bool pity_select(const int &weight, const int &fail_count);

    public:
        explicit Algorithm();
        virtual ~Algorithm();
        [[nodiscard]] std::vector<Item> get__items() const;
        void set__items(const std::vector<Item> &items);
        [[nodiscard]] User::SharedPtr get__user() const;
        void set__user(const User::SharedPtr &user);
        Item::SharedPtr draw();

    public:
        using SharedPtr = std::shared_ptr<Algorithm>;

    };
}

#endif
