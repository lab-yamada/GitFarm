#include "domain/item.hpp"

com::yamadalab::gitfarm::Item::Item()
    : id_(""),
    weight_(0)
{

}

com::yamadalab::gitfarm::Item::~Item()
{

}

std::string com::yamadalab::gitfarm::Item::get__id() const
{
    return this->id_;
}

void com::yamadalab::gitfarm::Item::set__id(const std::string &id)
{
    this->id_ = id;
}

int com::yamadalab::gitfarm::Item::get__weight() const
{
    return this->weight_;
}

void com::yamadalab::gitfarm::Item::set__weight(const int &weight)
{
    this->weight_ = weight;
}