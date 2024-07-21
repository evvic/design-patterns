#include "PersonBuilder.hpp"
#include "PersonAddressBuilder.hpp"
#include "PersonJobBuilder.hpp"

// PersonBuilderBase::PersonBuilderBase(Person& person) : person(person) {}

PersonAddressBuilder PersonBuilderBase::lives() const
{
    return PersonAddressBuilder{person};
}

PersonJobBuilder PersonBuilderBase::works() const
{
    return PersonJobBuilder{person};
}

// PersonBuider::PersonBuider() : PersonBuilderBase(p) {}
