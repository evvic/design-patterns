#pragma once
#include "HotDrink.hpp"

// Abstract Factory
// The HotDrinkFactory struct is declared as abstract using a pure virtual function make()
// This enforces that derived structs (like TeaFactory and CoffeeFactory) 
// must implement how to create a specific HotDrink object.
struct HotDrinkFactory
{
    virtual unique_ptr<HotDrink> make() const = 0;
};

// Concrete Factories based off abstract factory
struct TeaFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Tea>();
    }
};

struct CoffeeFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<Coffee>();
    }
};

struct HotChocolateFactory : HotDrinkFactory
{
    unique_ptr<HotDrink> make() const override
    {
        return make_unique<HotChocolate>();
    }
};
