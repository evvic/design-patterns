# Singleton

> Not commonly used anymore
- A component which is instantiated once

## Motivation
- For some components it only makes sense to have one in the system
    - .i.e. one database, object factory
- When the constructor call is expensive and shouldn't be done again
- Want to prevent anyone from creating additional copies
- Want thread safety for the object

## Singleton Object [`singletondb.cpp`](singletondb.cpp)
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