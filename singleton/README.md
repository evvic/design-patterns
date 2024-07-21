# Singleton

> Not commonly used anymore
- A component which is instantiated once

## Motivation
- For some components it only makes sense to have one in the system
    - .i.e. one database, object factory
- When the constructor call is expensive and shouldn't be done again
- Want to prevent anyone from creating additional copies
- Want thread safety for the object

## Making a "safe" Singleton
- Hide/delete the type's constructor, copy constructor, and copy assignment operators
- Create a static method that returns a reference to static member
- Guaranteed to be thread safe sicne C++11

## Singleton Class
### Example [`singletondb.cpp`](singletondb.cpp)
- The constructor for the `SingletonDatabase` is private
```cpp
SingletonDatabase(SingletonDatabase const&) = delete;
void operator=(SingletonDatabase const&) = delete;
```
- And the copy constructor and assignment operator are removed
```cpp
SingletonDatabase::get().getPopulation("Tokyo")
```
- To access data from the `SingletonDatabase` the above syntax is needed

### Pros
- This class does not allow multiple constructor calls
    - Therefore data is only read from [`capitals.txt`](capitals.txt) once
- Better performance in a situation like this where copying the data or reconstructing the singleton is only a waste of time and memory

### Cons
- The [`capitals.txt`](capitals.txt) and the `SingletonDatabase` functions are coupled together
    - Meaning you can't just unit test `getPopulation()` method
        - Without also pulling the data from [`capitals.txt`](capitals.txt)
        - It's not a unit test of the function but an intergration test of also pulling data from "database"
    - No easy way to independently test methods 
    - This could be resolved with **dependency injection**

## Multiton 
- Sets a key-value store
- Restricts the number of objects in that store and given to the client

### Example [`multiton.cpp`](multiton.cpp)
- This multiton can only have **3 instances** because the Key is `Importance` enum
    - And only has 3 values
```cpp
enum class Importance {
    primary,
    secondary,
    tertiary
};
```
- The `Multiton` class has the main purpose of tracking the objects created
```cpp
template <typename T, typename Key = std::string>
class Multiton
{
public:
    static shared_ptr<T> get(const Key& key)
    {
        if (const auto it = instances.find(key); 
            it != instances.end()) 
        {
            return it->second;
        }
        
        auto instance = make_shared<T>();
        instances[key] = instance;
        return instance;
    }
private:
    static map<Key, shared_ptr<T>> instances;
    ... // other private members
};
```
- `get()` method is used to get an existing object or create a new one
    - check if key is already in the map and return the pointer to the already created object
    - else create a new object, add to map, and return pointer to new object
- `instances` is a static map that holds the pointers to the created objects



## Monostate
- **Static fields cannot be inherited!**
- Therefore creating a monostate class can lead to errors
    - If developers try to make multiple objects
    - Or use a monostate class as a base class
- Usually a bad idea
```cpp
class Printer {
    static int id;
public:
    int get_id() const {return id;}
    void set_id(int value) {id = value;}
}

int main() {
    Printer p;
    int id = p.get_id();
    Printer p2;
}
```
- All of the storage is going into a static member
- Both `Printers` are using the same data (`id`)
- The latest `set` method sets every single instance

