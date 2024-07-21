#pragma once
#include "Person.hpp"

class PersonJobBuilder;
class PersonAddressBuilder;

class PersonBuilderBase
// contains protected reference to the person being built up
{
protected:
    Person& person;
    explicit PersonBuilderBase(Person& person) : person(person) {}

public:
    // PersonBuilderBase(Person& person);

    operator Person() const 
    {
        return std::move(person);
    }

    // builder facets

    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};

class PersonBuider : public PersonBuilderBase
{
  
public:
    Person p;
    PersonBuider() : PersonBuilderBase(p) {};

};