#ifndef GITFARM_DOMAIN_ITEM__HPP
#define GITFARM_DOMAIN_ITEM__HPP

#include <memory>
#include <string>

#define GRADE_S "S"
#define GRADE_A "A"
#define GRADE_B "B"
#define GRADE_C "C"
#define GRADE_D "D"

#define WEIGHT_S 0.00000001
#define WEIGHT_A 0.1
#define WEIGHT_B 1
#define WEIGHT_C 2
#define WEIGHT_D 3

namespace com::yamadalab::gitfarm
{
    class Item final
    {
    private:
        std::string id_;
        std::string grade_;
        double weight_;

    public:
        explicit Item();
        virtual ~Item();
        std::string get__id() const;
        void set__id(const std::string &id);
        std::string get__grade() const;
        void set__grade(const std::string &grade);
        double get__weight() const;
        void set__weight(const double &weight);

    public:
        using SharedPtr = std::shared_ptr<Item>;
        using UniquePtr = std::unique_ptr<Item>;

    };
}

#endif
