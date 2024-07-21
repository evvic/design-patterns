#pragma once
/******************************************
 * This header contains the corresponding
 * family of objects that inherit from
 * HotDrink.
 * 
 * In ___ there will be a corresponding
 * family of factories to construct these
 * objects.
 *
 ******************************************/
#include <iostream>
#include <memory>

using namespace std;



struct HotDrink
{
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink
{
    void prepare(int volume) override
    {
        cout << "Take tea bag, boil water, pour " << volume << " ml into cup, steep, enjoy!" << endl;
    }
};

struct Coffee : HotDrink
{
    void prepare(int volume) override
    {
        cout << "Grind coffee beans, boil water, pour " << volume << " ml into cup, add milk, enjoy!" << endl;
    }
};

struct HotChocolate : HotDrink
{
    void prepare(int volume) override
    {
        cout << "Boil milk. pour " << volume << " ml into cup, add chocolate, enjoy!" << endl;
    }
};