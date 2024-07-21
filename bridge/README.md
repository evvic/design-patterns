# Bridge
- Connecting components together through abstractions
- A mechanism that decouples an interface (hierarchy) from an implementation (hierarchy)

## Motivation
- Bridge prevents a 'Cartesian product' complexity explosion

## Pimpl Idiom
- **P**rivate **Impl**ementation?
- Hiding the implementation details of a class by sticking it its implementation
    - Put the imlplementation details into another nested class
- About physical design of files
- Can improve compilation speed as headers shouldnt need to be recompiled

### Example
#### `Person.hpp`
```cpp
class Person {
public:
    class PersonImpl;
    PersonImpl* impl;

    Person();
    ~Person();

    void greet();
}
```
- The consumer of the header does not get exposed to the details of the implemetation
- A dev looking at this would not see the implemnetation logic but just the functions designed to be used

#### `Person.cpp`
```cpp
class Person::PersonImpl {
public:
    void greet(Person *p);
};

void Person::PersonImpl::greet(Person *p) {
    cout << "hello " << p->name << endl;
}

Person::Person() : impl(new PersonImpl) {}
Person::~Person() {delete impl;}
Person::greet() {
    impl->greet(this);
}
```
- Not exposing the inner mechanics of the `Person` class to whover is consuming the library
- Although functions could be `private`, the consumer can still see from the header they exist
    - Maybe the functions should be a secret for a reason
        - Trade secerets?
    - Or including them would just make the class more confusing to understand

## Bridge Example

#### [`bridge.cpp`](bridge.cpp)
```cpp
struct Renderer {
    virtual void render_circle(float x, float y, float radius) = 0;
};

struct RasterRenderer : Renderer {
    void render_circle(float x, float y, float radius) override {
        cout << "Rasterizing circle of radius " << radius << endl;
    }
};

struct VectorRenderer : Renderer {
    void render_circle(float x, float y, float radius) override {
        cout << "Drawing a vector circle of radius " << radius << endl;
    }
};

```
- If there were different Shapes with 2 different methods for rendering the shapes, the number of methods to render shapes would exponentially grow
- In the [`bridge.cpp`](bridge.cpp) example there is only one concrete `Shape` defined, `Circle`
```cpp
struct Shape
{
protected:
    Renderer& renderer;
    Shape(Renderer& renderer) : renderer{ renderer } {}
...
};
```
- Having a reference to the renderer in the `Shape` class is the bridge
    - Bridge from the `Shape` to the `Renderer` being applied

