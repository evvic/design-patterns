#pragma once

#include <string>
#include "PersonBuilder.hpp"

class PersonBuilder;

class Person
{
    // address
    std::string street_address, post_code, city;

    // employment
    std::string company_name, position;

    int annual_income{0};

    static PersonBuilder create();

    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
};
