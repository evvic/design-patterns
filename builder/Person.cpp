#include "Person.hpp"
#include "PersonBuilder.hpp"

PersonBuilder Person::create()
{
    return PersonBuilder();
}
