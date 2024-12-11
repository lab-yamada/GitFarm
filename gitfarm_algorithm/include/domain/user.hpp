#ifndef GITFARM_DOMAIN_USER__HPP
#define GITFARM_DOMAIN_USER__HPP

#include <memory>
#include <string>

namespace com::yamadalab::gitfarm
{
    class User final
    {
    private:
        std::string id_;
        int fail_count_;

    public:
        explicit User();
        virtual ~User();
        std::string get__id() const;
        void set__id(const std::string &id);
        int get__fail_count() const;
        void set__fail_count(const int &fail_count);

    public:
        using SharedPtr = std::shared_ptr<User>;
        using UniquePtr = std::unique_ptr<User>;

    };
}

#endif
