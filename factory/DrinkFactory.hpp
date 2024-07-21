// Concrete factory and facilitator of HotDrinkFactory
#include "HotDrink.hpp"
#include "HotDrinkFactory.hpp"
#include <map>
#include <functional>

using namespace std;

// Object Oriented Polymorphic approach
class DrinkFactory
{
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;
public:
    DrinkFactory()
    {
        hot_factories["coffee"] = make_unique<CoffeeFactory>();
        hot_factories["tea"] = make_unique<TeaFactory>();
        hot_factories["hotchocolate"] = make_unique<HotChocolateFactory>();
    }

    // Polymorphism is at play because the compiler does not know the exact
    // type of factory at compile time (Could be TeaFactory or CoffeeFactory)
    // Compiler only knows all Factoires contain a make() and return a 
    // unique_ptr<HotDrink>
    unique_ptr<HotDrink> make_drink(const string& name, const int volume=100)
    {
        auto drink = hot_factories[name]->make();
        drink->prepare(volume);
        return drink;
    }
};

// Functional approach
class FunctionalDrinkFactory
{
    map<string, function<unique_ptr<HotDrink>(int volume)>> factories;
public:
    FunctionalDrinkFactory()
    {
        factories["tea"] = [](const int volume) {
            auto tea = make_unique<Tea>();
            tea->prepare(volume);
            return tea;
        };
    }

    unique_ptr<HotDrink> make_drink(const string& name, const int volume=100)
    {
        return factories[name](volume);
    }
};