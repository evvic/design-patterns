# Visitor
- A pattern where a component (visitor) is allowed to traverse the entire inheritance hierarchy
- Implmeneted by propagating a single `visit()` method throughout the entire hierarchy
    - Do not need to touch any other part of the hierarchy

## Motivation
- Need to define a new operation on an entire class hierarchy
    - i.e. make a document model printable to HTML/Markdown
- Do **not** want to keep modifying every class in the hierarchy
- Add extensibility to the side than to an intrusive approach
- Need access ot the non-common aspects of the classes in the hierarchy
- Create an external component to handle rendering
- Avoid type checks
    - Can mostly be built with dynamic casting

## Intrusive Visitor
- Modifies every class in the hierarchy
    - Violates the open-clsoe principle
    - Violates the single responsibility principle
        - Adding new functionality to the classes in the hierarchy is adding another responsibility

#### [`intrusive.cpp`](intrusive.cpp)
```cpp
struct Expression
{
    virtual void print(ostringstream& oss) = 0;
};
```
- The interface `Expression` class will have a virtual `print` method used by all inherited `Expression` classes

```cpp
struct AdditionExpression : Expression
{
    Expression *left, *right;
    // ...

    void print(ostringstream& oss) override {
        oss << "(";
        left->print(oss);
        oss << "+";
        right->print(oss);
        oss << ")";
    }
};
```
- `AdditionExpression` has its `print` recursively call other print methods depending on the obejct type for it's `left` and `right` Expressions

```cpp
auto e = new AdditionExpression{
    new DoubleExpression{1},
    new AdditionExpression{
        new DoubleExpression{2},
        new DoubleExpression{3}
    }
};
ostringstream oss;
e->print(oss);
```
- Calling the visitor that prints the hierarchy of Expressions is simply done with the highest level `print`
- This approach is of course very intrusive and adds another repsonsibility to all Expression-based classes


## Reflective Visitor
- Called **reflective** because in other languages it is called `reflection` for object type checks
    - In C++ this is accomplished with `dynamic_cast`
    - `dynamic_cast` takes time at runtime to check which

```cpp
struct ExpressionPrinter {

    ostringstream oss;

    void print(Expression *e)
    {
        if (auto de = dynamic_cast<DoubleExpression*>(e))
        {
            oss << de->value;
        } 
        else if (auto ae = dynamic_cast<AdditionExpression*>(e))
        {
            oss << "(";
            print(ae->left);
            oss << "+";
            print(ae->right);
            oss << ")";
        }
    }

    string str() const { return oss.str(); }
};
```
- Single general `print` function
    - Prints the way it is meant to depending on the object type of `Expression *e`
- This can be checked by doing a `dynamic_cast`
    - Try casting it to a DoubleExpression
        - Then format it for that object type
    - Else try casting it to a AdditionExpression

- This solution does not scale well with chaining multiple if-statements
- Still better than Intrusive Visitor for not breaking open-close and single responsibility principle

## Classic Visitor (Double Dispatch)
- In C++, it's impossible to form a dispatch at runtime 
- Dispatch: the process of selecting the appropriate code to execute based on certain criteria
    - **Static dispatch**: when the selection occurs at **compile time**
        - C++ mostly operates with the compiler deciding which function to call based on declared types of the variables involved
    - **Dynamic dispatch**: when the selection occurs at **run time**
        - C++ supports a limited form of dynamic dispatch with `virtual` functions
        - When a derived class overrides a virtual function (from a base class), the runtime system determines which version of the function to call
            - Based on the actual type of the object being referenced
        - Also has much more performance overhead at runtime determining the correct function
- **Double dispatch**:

#### [`double-dispatch.cpp`](double-dispatch.cpp)

```cpp
struct Expression
{
    virtual void accept(ExpressionVisitor* visitor) = 0;
};
```
- The base `Expression` class has a virtual accept method that the visitor needs to propogate to all Expression based classes

```cpp
struct DoubleExpression : Expression
{
    double value;
    explicit DoubleExpression(const double value)
        : value{ value } {}

    void accept(ExpressionVisitor* visitor) override
    {
        visitor->visit(this);
    }
};
```
- All 3 classes (`DoubleExpression`, `AdditionExpression`, `SubtractionExpression`) inheriting from Expression will have this **EXACT** same `accept` function
- Although the `accept` function is the same between all of them, the key is that the _`this`_ type passed in will be different based on the object type
    - The type will either be `DoubleExpression`, `AdditionExpression` or `SubtractionExpression`
- That is an example of ONE dynamic dispatch...

```cpp
struct ExpressionVisitor
{
    virtual void visit(DoubleExpression* de) = 0;
    virtual void visit(AdditionExpression* ae) = 0;
    virtual void visit(SubtractionExpression* se) = 0;
};
```
- The second half of the double dispatch is selecting the correct `visit` method based on the object type

```cpp
void ExpressionPrinter::visit(DoubleExpression* de)
{
    oss << de->value;
}
```
- The example `ExpressionPrinter` has a `visit` method for all `Expression` types

#### Running the example
```cpp
auto e = new AdditionExpression{
    new DoubleExpression{ 1 },
    new SubtractionExpression {
        new DoubleExpression{ 2 },
        new DoubleExpression{ 3 }
    }
};
ExpressionPrinter printer;
printer.visit(e);
printer.str();
```
- The Expression is defined with other nested Expressions
- The visitor `ExpressionPrinter` runs `.visit()` on the concrete Expression `e`

## Acyclic Visitor
- Based on **RTTI** (run-time type information)
    - In C++ RTTI allows determination of the dynamic type of an object at runtime
        - Primarily used with `typeid` operator and `dynamic_cast` operator
            - **`typeid`**: returns a type_info object representing the type of expression
            - **`dynamic_cast`**: attempts to cast an expression to a polymorphic type
                - If successful, it returns the converted value, else **null**
- Significantly slower
- Puts no limitations on hierarchy

#### [`acyclic.cpp`](acyclic.cpp)
```cpp
template <typename Visitable>
struct Visitor
{
    virtual void visit(Visitable& obj) = 0;
};
```
- Specify we can visit a `Visitable`

```cpp
struct VisitorBase // marker interface
{
    virtual ~VisitorBase() = default;
};
```
- Add a virtual destructor so the virtual `VisitorBase` class is added to the v-tables

```cpp
struct Expression
{
    virtual ~Expression() = default;

    virtual void accept(VisitorBase& obj)
    {
        using EV = Visitor<Expression>;
        if (auto ev = dynamic_cast<EV*>(&obj))
            ev->visit(*this);
    }
};
```
- `Expression` interface base class
- `accept` method is going to accept a reference to `VisitorBase`
- We want to make sure `obj` param is of type `Visitor<Expression>`
- Verifying the `VisitorBase& obj` being passed into `Expression::accept()` knows how to accept a `Visitor<Expression>`
    - Verifying is done so be checking if `dynamic_cast` can cast the obj into `Visitor<Expression>` type

```cpp
virtual void AdditionExpression::accept(VisitorBase& obj)
{
    using AEV = Visitor<AdditionExpression>;
    if (auto ev = dynamic_cast<AEV*>(&obj))
        ev->visit(*this);
}
```
- All classes inheriting from `Expression` interface need to implement the `accept` for checking `dynamic_cast`

#### Implement ExpressionPrinter
```cpp
struct ExpressionPrinter : VisitorBase,
                           Visitor<Expression>,
                           Visitor<DoubleExpression>,
                           Visitor<AdditionExpression>
{
private:
    ostringstream oss;
```
- `ExpressionPrinter` implements the Visitor classes
    - Inheriting `VisitorBase` (is just a marker but) allows `ExpressionPrinter` to be included into every `accept` method all the `Expression` classes implement
    - Inheriting `Visitor<DoubleExpression>` / `Visitor<AdditionExpression>` allows overriding the `visit` methods each `dynamic_cast` should have for these types

```cpp
void ExpressionPrinter::visit(DoubleExpression &obj) override
{
    oss << obj.value;
}
```
- ExpressionPrinter has a visit method for all concrete Expression objects

- The benefit of Acyclic Visitor is it is very non-intrusive
    - Removing the `ExpressionPrinter` class will not break the overloaded `Visitor<Expression>` `visit` methods
    - It easily extendable to multiple visitor classes


## Multimethods
- Multi dispatch without a visitor
- Implement on 2 arguments instead of 1 argument
- Uses CRTP

#### [`multimethods.cpp`](multimethods.cpp)


- In the following example there is `GameObject` of different objects
    - i.e. planet, spaceship, asteroid and they all interact differently when they collide with each other


```cpp
struct GameObject
{
	virtual ~GameObject() = default;
	virtual type_index type() const = 0;

	virtual void collide(GameObject& other) { ::collide(*this, other); }
};
```
- All the objects will "inherit" from `GameObject` but with a twist...

```cpp
template <typename T> struct GameObjectImpl : GameObject
{
	type_index type() const override
	{   
		return typeid(T);
	}
};
```
- `GameObjectImpl` inherits from `GameObject` and the actual objects will inherit from `GameObjectImpl`

```cpp
struct Planet : GameObjectImpl<Planet> {};
struct Asteroid : GameObjectImpl<Asteroid> {};
struct Spaceship : GameObjectImpl<Spaceship> {};
```
- Objects inherit from `GameObjectImpl` passing in themselves as the template argument
- Determines the `type_index`

```cpp
void spaceship_planet() { cout << "spaceship lands on planet\n"; }
void asteroid_planet() { cout << "asteroid burns up in atmosphere\n"; }
void asteroid_spaceship() { cout << "asteroid hits and destroys spaceship\n"; }
// ...
```
- The functions defined for the types of collision options

#### Map function collisions to object pairs
```cpp
map<pair<type_index,type_index>, void(*)(void)> outcomes{
	{{typeid(Spaceship), typeid(Planet)}, spaceship_planet},
	{{typeid(Asteroid),typeid(Planet)}, asteroid_planet},
	{{typeid(Asteroid),typeid(Spaceship)}, asteroid_spaceship},
	{{typeid(Asteroid), typeid(ArmedSpaceship)}, asteroid_armed_spaceship}
};
```
- The pairs of objects that are colliding are the keys
- The function handling with that type of collision is the value
    - `void(*)(void)` is a pointer to a function that takes no arguments and returns void

```cpp
void collide(GameObject& first, GameObject& second)
{
	auto it = outcomes.find({ first.type(), second.type() });
	if (it == outcomes.end())
	{
		it = outcomes.find({ second.type(), first.type() });
		if (it == outcomes.end())
		{
			cout << "objects pass each other harmlessly\n";
			return;
		}
	}
	it->second();
}
```
- The `collide` function takes 2 `GameObject`s and runs a function in the `outcomes` map if the pair of obejcts exists in the map
- `collide` will check the pair of objects in either order for the mapped function

#### Example testing `collide`
```cpp
Asteroid asteroid;
Planet planet;
collide(planet, asteroid);
```
- Depends on runtime of 2 object arguments

## `std::variant && std::visit`

- A `variant` in C++ allows a variable to be multiple data types

#### `std::variant`
```cpp
variant<string, int> house;
```
- Here the `house` variable can be either a string or an int

```cpp
struct AddressPrinter
{
    void operator()(const string& house_name) const {
        cout << "A house called " << house_name << "\n";
    }

    void operator()(const int house_number) const {
        cout << "House number " << house_number << "\n";
    }
};
```
- `AddressPrinter` is a visitor for a variant type of variable
- Overload the function call `()` operator for every type in the variant

#### `std::visit`
```cpp
variant<string, int> house;
house = 221;

AddressPrinter ap;
std::visit(ap, house);
```
- `std::visit` takes a callable `()` and the variant 
- A visitor that works on a `std::variant`


#### `std::visit` with lambda
- Instead of creating a `struct AddressPrinter` that overloads the `()` operator for all options in the variant, a lambda can be passed into `visit()`

```cpp
variant<string, int> house;
house = "Montefiore Castle";

std::visit([](auto& arg) {
    using T = decay_t<decltype(arg)>;

    if constexpr (is_same_v<T, string>) {
        cout << "A house called " << arg.c_str() << "\n";
    }
    else {
        cout << "House number " << arg << "\n";
    }
}, house);
```
- The lamnda takes an `auto` type for arg because it could be a string or visitor
- `using T = decay_t<decltype(arg)>;` gets the template type of the `arg`
- Then can use the template type `T` for evaluating if the arg is a string
    - How to process the arg being a string or an integer



