# Composite
- Treating individual and aggregate objects uniformly
- A mechanism for treating individual (scalar) objects and compositions of objects in a uniform manner
- Composite desing pattern is used to treat both single (scalar) and composite objects uniformly
    - i.e. `Foo` and `Composite<Foo>` have the same APIs
- Objects can use other objects via inheritance/composition
- Some composed and singular objects need similar/identical behaviors 
- Composite design patterns allow us to treat both types of objects uniformly


## Motivation
- Objects are using other objects fields/properties/members through inheritance and composition
- Composition let's us make compound objects
    - i.e. a mathematical expression composed os simple expressions
    - i.e. a grouping of shapes that consists of several shapes

## Composite Example
- Individual objects and collections of objects all behave in the same manner
- This allows for recursion
    - A collection can be inside of a collection
- A trick is a single object can masquerade as a collection
    - Must implement `begin()`/`end()`

```cpp
struct GraphicObject {
    virtual void draw() = 0;
};

struct Circle : GraphicObject {
    void draw() override {
        std::cout << "Circle" << std::endl;
    }
};

struct Group : GraphicObject {
    std::string name;

    explicit Group(const std::string& name)
        : name{name} {}

    void draw() override
    {
        cout << "Group " << name.c_str() << " contains:" << endl;
        for (auto&& o : objects)
            o->draw();
    }

    std::vector<GraphicObject*> objects;
};
```
- The above structs for `GraphicObject` is a composite
    - Due to the `Group` class taking a `vector<GraphicObject*>`
- The `Group` can still act as `GraphicObject` and can contain `Group` objects

```cpp
inline void graphics() {
    Group root("root");
    Circle c1, c2;
    root.objects.push_back(&c1);

    Group subgroup("sub");
    subgroup.objects.push_back(&c2);

    root.objects.push_back(&subgroup);

    root.draw();
}
```
- In the above snippet a `Group` named root contains a `Circle` and another `Group` "sub"
    - "sub" itself contains a `Circle` object
- Running `draw()` will "draw" (cout) the objects in the order they are in `vector<GraphicObject*> objects`

### Example Neural Network
#### [`neurons.cpp`](neurons.cpp)

```cpp
struct Neuron : SomeNeurons<Neuron>
{
    vector<Neuron*> in, out;
    unsigned int id;

    Neuron()
    {
        static int id = 1; 
        this->id = id++;
    }
    ... // other methods...
```
- There is a `Neuron` struct that creates a single `Neuron` object
- It also contains a `in` and `out` vector of pointers to other Neurons
- Neurons will save their connections with these vectors
```cpp
struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer>
{
    NeuronLayer(int count)
    {
        while (count-- > 0)
        emplace_back(Neuron{});
    }
    ... // other methods...
```
- And there is a `NeuronLayer` struct that creates a vetor of neurons
    - Considered one layer as they are all in the same vector in a `NeuronLayer` object

```cpp
template <typename Self>
struct SomeNeurons
{
    template <typename T> void connect_to(T& other)
    {
        for (Neuron& from : *static_cast<Self*>(this))
        {
            for (Neuron& to : other)
            {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};
```
- `SomeNeurons` is a Curiously Recurring Template Pattern (CRTP) and acts as a composite element
    - Provides a common interface for `Neuron` and `NeuronLayer` through template specialization
    - This also allows `static_cast<Self*>(this)` to cast the current object (this) to its actual type (`Neuron` or `NeuronLayer`)
    - CRTP allows both `Neuron` and `NeuronLayer` to use the `connect_to` function (code reuse!)
        - Type safety: the compiler ensures that static cast is valid since Self is set to the actual derived type
- The `Neuron` struct won't work in the `connect_to` method in `SomeNeurons`
    - `connect_to` iterrates through a data structure of `Neuron`s with a .begin() and .end()
- Therefore the `Neuron` struct needs a .begin() and .end() defined...
```cpp
struct Neuron : SomeNeurons<Neuron>
{
    ... //  other methods...
    Neuron* begin() { return this; }
    Neuron* end() { return this + 1; }
};
```
- The custom begin and end methods in Neuron allow for treating a single neuron like a range
- Now the singular `Neuron` will work within the for loop!
- In a range-based for loop the iterrator will begin at `begin()`
    - Then it will incrmement after handing the first (only) Neuron
    - It will then see it has reached the `end()`

## Composite and Proxy Combination

- If a class had a number of properties that all needed getters and setters
- It would be tedious to add more properties
### Array backed properties
- Solution is to have compositite storage for the fields

### Example
```cpp
enum Abilities {strength, agility, intelligence, count};
array<int, count> abilities;
```
- The properties in a class can be made into an enum
    - The last element in the enum is `count`
        - `count` will be equal to the length of the array
