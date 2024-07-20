# SOLID Design Principles
- 5 of the most common programming design principles

## **S**ingle Responsibility Principle
- A class should have a primary responsibility and should not take up other responsibilites
- Gather together the things that change for the same reasons
  - Separate things that change for different reasons
- The class is more robust when it is focused on a single concern

### Example [`1-srp.cpp`](1-srp.cpp)
- The `Journal` class has one responsibility and that is to allow writing entries
- Adding a `save` member function to persist the entries is another responsibilty
    - This would mean that other classes would alos have to implement their own method to save/load and it would have to be changed everywhere
- Instead a `save` method is in it's own class (`PersistenceManager`)
    - Any other class that should eed to save/load data can use the `PersistenceManager`

## **O**pen-Closed Principle
- The system should be **open** to extension (i.e. by inheritance) but **closed** from modificaton
- Bad practice is to have to modify existing code versus inheriting and extending the system

### Example [`2-ocp.cpp`](2-ocp.cpp)
- To filter the vector of `Products` creating a function to filter by color or size is repetitive
  - Plus the function would have to be replicated continuously for every additional filter added
  - And what if they want to combine filters
    - ...now there can be many different combinations for filter functions



## **L**iskov Substitution Principle

# Setup
- Install the boost library
```bash
sudo apt install libboost-all-dev
```

- Run `make` to build all the independent examples binaries