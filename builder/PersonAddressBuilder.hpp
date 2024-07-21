#pragma once
#include <string>
#include "PersonBuilder.hpp"

// inherit from PersonBuilderBase so the person object is not replicated
class PersonAddressBuilder : public PersonBuilderBase
{
    // simply always typing out PersonAddressBuilder
    typedef PersonAddressBuilder Self;
public:
    explicit PersonAddressBuilder(Person& person) : PersonBuilderBase(person) {}

    Self& at(std::string street_address)
    {
        person.street_address = street_address;
        return *this;
    }

    Self& with_postcode(std::string post_code)
    {
        person.post_code = post_code;
        return *this;
    }

    Self& in(std::string city)
    {
        person.city = city;
        return *this;
    }
};
