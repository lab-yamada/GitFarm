#ifndef DOMAIN_ITEM__HPP
#define DOMAIN_ITEM__HPP

#include <memory>
#include <string>

namespace com
{
    namespace yamadalab
    {
        namespace gitcha
        {
            class Item
            {
            private:
                std::string id_;
                int weight_;

            public:
                explicit Item();
                virtual ~Item();
                std::string get__id() const;
                void set__id(const std::string &id);
                int get__weight() const;
                void set__weight(const int &weight);

            public:
                using SharedPtr = std::shared_ptr<Item>;
            };
        }
    }
}

#endif