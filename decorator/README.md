# Decorator
- Give an existing object additional functionality
- Facilitates the addition of behaviors to individual objects

## Motivation
- Want to augment an object with additional functionality
    - Without rewriting/altering the existing class (OCP)
    - Or want to keep new functionality separarte (SRP)
- Needs to be able ti interact with existing features
- 2 options:
    - Aggregate the decorated object
    - Inherit from the decorated object

## Dynamic Decorator
- A decorator that inherits from the interface class and then wraps around the concrete object
- A dynamic decorator keeps the reference to the decorated object(s)
```cpp
struct Shape {
  virtual string str() const = 0;
};

struct Circle : Shape {
    float radius;

    Circle(){}

    explicit Circle(const float radius) : radius{radius} {}

    void resize(float factor) {
        radius *= factor;
    }

    string str() const override {
        ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape {
    float side;

    Square() {}

    explicit Square(const float side) : side{side} {}

    string str() const override {
        ostringstream oss;
        oss << "A square of with side " << side;
        return oss.str();
    }
};
```
- Above there is the abstract `Shape` struct and 2 concrete shapes inheriting from it
    - `Square` and `Circle`

#### Decorator
```cpp
struct ColoredShape : Shape {
    Shape& shape;
    string color;

    ColoredShape(Shape& shape, const string& color)
        : shape{shape}, color{color}
    {}

    string str() const override {
        ostringstream oss;
        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};
```
- `ColoredShape` is a decorator (wrapper)
    - That wraps around the `Shape& shape` passed in from the constructor
- This does not modify the existing base class `Shape`
    - Cannot make `ColoredSquare` or `ColoredCircle` classes
        - Technically they can be made but no point
#### 2nd Decorator
```cpp
struct TransparentShape : Shape {
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape& shape, const uint8_t transparency)
        : shape{shape}, transparency{transparency}
    {}

    string str() const override
    {
        ostringstream oss;
        oss << shape.str() << " has "
            << static_cast<float>(transparency) / 255.f*100.f
            << "% transparency";
        return oss.str();
    }
};
```
- Notice how both decorators inherit from `Shape` and hold a `Shape` object within them
- This means the decorators can wrap around each other
#### Instantiation
```cpp
Square square(5);
ColoredShape red_square(square, "red");
TransparentShape decorated_square(red_square, 51);
cout << decorated_square << endl;
```
#### Output
```
A square with side 5 has the color red has 20% transparency
```
- A basic square object is created then decorators wrap around
    - They do not change the abstract and concrete classes

#### Dynamic Decorator Cons
```cpp
void Circle::resize(float factor) {
    radius *= factor;
}
```
- Creating any wrapper object around the concrete object will lose access to that obects member classes
- i.e. creating a `ColoredShape` of a `Circle` can no longer call `.resize()`

## Static Decorator

- **Mixin inheritance**: bake in decorator information into the concrete object:
```cpp
template <typename T>
concept IsAShape = std::is_base_of<Shape, T>::value;

template <IsAShape T> struct ColoredShape2 : T {
    string color;
    ColoredShape2() {}

    template <typename...Args>
    ColoredShape2(const string& color, Args ...args)
        : T(std::forward<Args>(args)...), color(color)
    {}
};
```
- Defining a Shape with `ColoredShape2` allows the underlying methods to be called
    - `resize()` method can be called!
- **concepts** is a C++20 feature


- **Constructive forwarding**: pass correct value onto underlying class being wrapped
    - The concept ensures the ColoredShape2 will be inheriting from some type of `Shape`
        - But it is not guaranteed the `Shape` will be i.e. a Circle with a `resize()` member
    ```cpp
    ColoredShape2(const string& color, Args ...args)
        : T(std::forward<Args>(args)...), color(color)
    {}
    ```
    - All the forwarded arguments get matched with the right base class contructor

## Functional Decorator
#### [`logger_wrapper.cpp`](logger_wrapper.cpp)
- This program implements a `Logger` struct that takes a function
- When the function is invoked it simply prints an enter and exit message
    - But it could be expanded to do much more!

```c++
template <typename> struct Logger;
```
- Incomplete template declaration
- This enforces specialization
    - The template can work with specific fucntion signatures
    - Meaning the later definition of `Logger` struct

#### `make_logger()`
```cpp
template <typename R, typename... Args>
auto make_logger(R (*func)(Args...), const string& name)
{
    auto built_func = std::function<RetType(Args...)>(func);
    return Logger<RetType(Args...)>(built_func, name);
}
```
- Takes in a function pointer and the string name of the function
- The ellpsis `...` represents a spread of 0 to any number of arguments

todo EXPLAIN HOW THE PROGRAM WORKS AND ASK AI