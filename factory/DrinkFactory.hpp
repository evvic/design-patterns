// Concrete factory and facilitator of HotDrinkFactory
#include "HotDrink.hpp"
#include "HotDrinkFactory.hpp"
#include <map>

using namespace std;

class DrinkFactory
{
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
    DrinkFactory()
    {
        // how is this polymorphism?
        // what does make_unique do/return?
        hot_factories["coffee"] = make_unique<CoffeeFactory>();
        hot_factories["tea"] = make_unique<TeaFactory>();
        hot_factories["hotchocolate"] = make_unique<HotChocolateFactory>();
    }

    // Polymorphism is at play because the compiler does not know the exact
    // type of factory at compile time (Could be TeaFactory or CoffeeFactory)
    // Compiler only knows all Factoires contain a make() and return a 
    // unique_ptr<HotDrink>
    unique_ptr<HotDrink> make_drink(const string& name)
    {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};