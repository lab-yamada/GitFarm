#include "domain/user.hpp"

namespace com::yamadalab::gitfarm
{
	User::User()
	: id_(""),
	fail_count_(0)
	{
	}

	User::~User() = default;

	std::string User::get__id() const
	{
		return this->id_;
	}

	void User::set__id(const std::string &id)
	{
		this->id_ = id;
	}

	int User::get__fail_count() const
	{
		return this->fail_count_;
	}

	void User::set__fail_count(const int &fail_count)
	{
		this->fail_count_ = fail_count;
	}
}