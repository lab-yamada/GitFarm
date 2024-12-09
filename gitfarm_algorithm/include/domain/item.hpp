#ifndef DOMAIN_ITEM__HPP
#define DOMAIN_ITEM__HPP

#include <memory>
#include <string>

namespace com
{
    namespace yamadalab
    {
        namespace gitfarm
        {
            class Item
            {
            private:
                std::string id_;
                int weight_;
                double probability_;
                int fail_count_;

            public:
                explicit Item();
                virtual ~Item();
                std::string get__id() const;
                void set__id(const std::string &id);
                int get__weight() const;
                void set__weight(const int &weight);
                double get__probability() const;
                void set__probability(const double &probability);
                int get__fail_count() const;
                void set__fail_count(const int &fail_count);

            public:
                using SharedPtr = std::shared_ptr<Item>;
            };
        }
    }
}

#endif