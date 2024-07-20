#pragma once
#include "Person.hpp"

class PersonJobBuilder;
class PersonAddressBuilder;

class PersonBuilderBase
// contains protected reference to the person being built up
{
protected:
    Person& person;
public:
    PersonBuilderBase(Person& person);
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};

class PersonBuider : public PersonBuilderBase
{
private:
    Person p;
public:
    PersonBuider();

};