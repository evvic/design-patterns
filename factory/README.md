# Factory

- A component responsible solely for the wholesale (not piecewise) creation of objects
- Takes complete care of object creation
- A static method that creates objects
- A factory can be external or reside inside the object as an inner class
- Hierarchies of factories can be used to create related objects

The factory pattern can be split into 2 sub patterns based of the Gang of Four book:
1. Factory Method
2. Abstract Factory

## Motivation
- Object creation logic becomes too convoluted
- Constructor is not descriptive
    - The name of the constructor is the class name so creating object based off a class name can be misleading or unintuitive
- Cannot overload with same sets of arguments with different names
    - i.e. can't have 2 constructors that both take 1 int
    - Can turn into optional parameter hell
- Single statements for object creation means outsourcing to factories

## Creation Pattern Differences
- The builder is where you construct an object in steps

## Factory Method
- A separate function or separate class
- Constructor-like call to deal with different options
- Also include inner factory

### Example
How to distinguish the Point class is for cartesian (x, y) or polar (rho, theta) coordinates?
#### Non-factory
```c++
enum class PointType {
    cartesian,
    polar
};
struct Point {
    Point(float a, float b, PointType type = PointType::cartesian) {
        if (type == PointType::cartesian) // handle cartesian point logic
        else // handle polar coordinate logic
    }
    float a, b;
};
```
- The above method does not use factory pattern and it can be hard for someone to understand when `Point` is referring to polar or aartessian coordinates
- The following snippet will show the `Point` class restructured following the **factory method** design
#### Factory Method
```c++
enum class PointType {
    cartesian,
    polar
};
class Point {
    Point(float x, float y) : x(x), y(y) {}
public:
    float x, y;
    static Point NewCartesian(float x, float y) return {x, y};
    static Point NewPolar(float r, float theta) {
        return {x, y};
    }
};
```
- Implementing the factory method has the Point class constructor private
- and to create a Point (whether catesian or polar) has to be done like so:
```c++
auto p = Point::NewPolar(5, 90);
```

## Inner factory
- Inner classes have access to the private members of the outter class
- Someone reading the code might not easily understand that the separate factory class should be used as the API to the desired class
- Nesting the factory class inside the desired class makes it clear you use factory to construct an object

#### Example Inner Factory
```c++
enum class PointType {
    cartesian,
    polar
};
class Point {
    Point(float x, float y) : x(x), y(y) {}
    float x, y;
    class PointFactory {
        PointFactory() {}
    public:
        static Point NewCartesian(float x, float y) return {x, y};
        static Point NewPolar(float r, float theta) {
            return {x, y};
        }
    };
public:
    static PointFactory Factory;
};
```
- Note the constructor and member variables are private
- It would be clear to a programmer to use PointFactory to Create a Point
   - It is the only public method
```c++
auto p = Point::Factory.NewCartesian(5, 5);
```

## Abstract Factory
- Can create hierarchy of factories using Abstract factory

### Example Drink Factory [`main.cpp`](main.cpp)
```cpp
struct HotDrinkFactory
{
    virtual unique_ptr<HotDrink> make() const = 0;
};
```
- The `HotDrinkFactory` class is declared as abstract with 1 virtual function `make()`
  - This enforces derived classes (`TeaFactory`, `CoffeeFactory`, and `HotChocolateFactory`) to override `make()` which returns a pointer to a HotDrink object
- Every derived `HotDrink` class has a Factory of itself
```cpp
DrinkFactory()
{
    hot_factories["coffee"] = make_unique<CoffeeFactory>();
    hot_factories["tea"] = make_unique<TeaFactory>();
    hot_factories["hotchocolate"] = make_unique<HotChocolateFactory>();
}
```
- `DrinkFactory` is the concrete factory and facilitator of `HotDrinkFactory`
- Polymorphically map concrete factories based on abstract factory

### ✨Functional✨ Drink Factory [`DrinkFactory.cpp`](DrinkFactory.cpp)
- Instead of using polymorphism with the map `hot_factories` in `DrinkFactory`, a map of lambda functions can be used instead
```cpp
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
```
- In the above example only 1 lamda ("tea") is defined
