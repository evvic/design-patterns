# Prototype
- Used for object copying
- A partially or fully initialized object ypu copy to make use of
- When it's easier to copy an existing object than to fully initialize a new one

## Motivation
- Complicated objects aren't designed from scratch
- An existing (partially or fully constructed) design is a protoype
    - Want to make variations on it
- Want to make a copy (clone) of the prototype and customize it
    - Requires "deep copy" support
- Convienent to clone (make it that wayt)

## Prototype
- When a copy of an object is desired, that original obejct to-bo-copied is the prototype
- It helps when the class that the prototype object is from has a **copy constructor**
- When an object is built from derived classes, it is good if all classes have a copy constructor
    - So each class only has to copy its certain part then pass the rest of the object on
- Multiple ways to clone the prototype:
    1. Implement a deep copy (class copy constructors)
    2. `IPrototype` interface with a deep_copy member 
        - Implement that interace into every class that is part of the overall object
    3. Serialize and deserialize
        - Traverse object graph to make a deep copy of its data

## Prototype Factory
- When you only want people to create a new object based off a prototype
    - Rather than create a new object from a class
    - Or creating a new type of prototype
- Stick protoypes in a factory and make constuctors private

```cpp
struct EmployeeFactory {
public:
    // create a new emplyee with defaulted Address data
    static unique_ptr<Contact> new_main_office_employee(
        const string& name,
        const int suite)
    {
        static Contact proto{"",  new Address {"123 Main Office Addy", "City", 0}};
        return new_employee(name, suite, proto);
    }
private:
    static unique_ptr<Contact> new_employee(
        const string& name,
        const int suite,
        const Contact& prototype)
    {
        // clone protoype...
        auto result = make_unique<Contact>(prototype);
        // customize copy...
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};
```
- The above struct is a Factory for creating a new object based on copying a prototype
- Instead of having to manually add the main office address details, that is already in the protoype
    - All that is needed is the employee name and their specific office suite at the main office
```cpp
auto john = EmployeeFactory::new_main_office_employee("John", 420);
```
- Creating the `Contact` for a John has much less redundancy!

## Prototype via Serialization
- Copying obejcts via copy constructors can be a bit complicated when member variables are pointers
- **Serialize**: store all the aspects of an object
- **Deserialize**: restore all the aspects of an object
- There is no magic bullet to automatically serialize/deserialize the object

### Boost Library to Serialize [`serialize.cpp`]()
- Using `boost` library can take care of some of the serialization boilerplate code
- Boost automaticaally knows to follow the pointer to serialize the data its pointing to
    - The main benefit of usng boost over a copy constructor is not worrying about copying pointers
- Requires a default constructor to deserialize the copy
- All classes inside object being copied needs the boost data