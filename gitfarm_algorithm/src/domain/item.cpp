#include "domain/item.hpp"

namespace com::yamadalab::gitfarm
{
	Item::Item()
	: id_("")
	, weight_(0.0)
	{
	}

	Item::~Item() = default;

	std::string Item::get__id() const
	{
		return this->id_;
	}

	void Item::set__id(const std::string &id)
	{
		this->id_ = id;
	}

	std::string Item::get__grade() const
	{
		return this->grade_;
	}

	void Item::set__grade(const std::string &grade)
	{
		this->grade_ = grade;
	}

	double Item::get__weight() const
	{
		return this->weight_;
	}

	void Item::set__weight(const double &weight)
	{
		this->weight_ = weight;
	}
}