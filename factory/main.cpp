#include <iostream>
#include <memory>
#include <map>
#include "DrinkFactory.hpp"
#include "HotDrinkFactory.hpp"
using namespace std;

unique_ptr<HotDrink> make_drink(string type)
{
    unique_ptr<HotDrink> drink;
    if (type == "tea")
    {
        drink = make_unique<Tea>();
        drink->prepare(200);
    }
    else 
    {
        drink = make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}

int main()
{
    auto d = make_drink("coffee");

    // Object Oriented Polymporphic approach
    DrinkFactory df;
    df.make_drink("coffee");
    df.make_drink("tea");
    df.make_drink("hotchocolate");
    df.make_drink("hotchocolate");

    // Functional approach
    FunctionalDrinkFactory fdf;
    fdf.make_drink("tea");

    getchar(); // wait
    return 0;
}
