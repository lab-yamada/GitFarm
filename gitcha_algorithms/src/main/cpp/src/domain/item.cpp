#include "domain/item.hpp"

com::yamadalab::gitcha::Item::Item()
    : id_(""),
    weight_(0)
{

}

com::yamadalab::gitcha::Item::~Item()
{

}

std::string com::yamadalab::gitcha::Item::get__id() const
{
    return this->id_;
}

void com::yamadalab::gitcha::Item::set__id(const std::string &id)
{
    this->id_ = id;
}

int com::yamadalab::gitcha::Item::get__weight() const
{
    return this->weight_;
}

void com::yamadalab::gitcha::Item::set__weight(const int &weight)
{
    this->weight_ = weight;
}