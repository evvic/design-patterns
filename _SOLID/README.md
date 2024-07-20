# SOLID Design Principles
- Acronym for the **5 most common programming design principles**:
  1. [Single Responsibility Principle](#single-responsibility-principle)
  2. [Open-Closed Principle](#open-closed-principle)
  3. [Liskov Substitution Principle](#liskov-substitution-principle)
  4. [Interface Segregation Principle](#interface-segregation-principle)
  5. [Dependency Inversion Principle](#dependency-inversion-principle)

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
- The core interfaces would never need to be modified (closed), new features can be implemented as classes that inherit from these core interfaces

### Example [`2-ocp.cpp`](2-ocp.cpp)
- To filter the vector of `Products` creating a function to filter by color or size is repetitive
  - Plus the function would have to be replicated continuously for every additional filter added
  - And what if they want to combine filters
    - ...now there can be many different combinations for filter functions
- Create a virtual `Specification` class that is used to be inherited by
  - Contains the virtual method (for comparing the specific feature) that needs to be overrided
- Create a virtual `Filter` class that is meant to be inherited
  - Contains the virtual method for filtering a vector by a Specification and returning the filtered vector


## **L**iskov Substitution Principle
- Subtypes should be immediately substitutable for their base types
- Objects of a subclass must behave the same way as the objects from the base class

### Example [`3-lsp.cpp`](3-lsp.cpp)
- The `Square` class inheriting from `Rectangle` does not behave the same way in the `process()` function
- Squares shouldnt be seen as inheriting from Rectangles
- Using a Factory to create either a Square or Rectangle would be better as both are still rectangles and does not break behavior

## **I**nterface Segregation Principle
- Do not make interfaces too large that implementers have to implement
- Avoid stuffing too many methods into a single interface
- Better to break up the interface into separate interfaces

### Example [`4-isp.cpp`](4-isp.cpp)
- Instead of having the print, scan and fax functionality all in one interface, make each a separate interface
- Then multiple interfaces can be used to make one interface:
```cpp
struct IMachine: IPrinter, IScanner {};
```
- Here the Machine interface (`IMachine`) takes both printer and scanner inerfaces
  - A machine inheriting from IMachine will now have the print and scan ability
  - After overriding the virtual methods from `IPrinter` and `IScanner`


## **D**ependency Inversion Principle
- Best way to form dependencies between different objects
- Changing the details of the dependency should not break the high-level module
- Abstractions = interfaces or base classes


2 Principles:
1. High-level modules should not depend on low-level modules
    - Both should depend on abstractions
2. Abstractions should not depend on the details
    - Details should depend on the abstractions

### Example [`5-dip.cpp`](5-dip.cpp)
- The low-vel module `Relationships` is used by the high-level module `Research`
- Directly including `Relationships` into `Research` makes `Research` vulnerable to any changes in `Relationships`
- It is better to create some "API" that abstracts the dependencies and keeps any changes all within `Relationships`

# Setup
- Install the boost library
```bash
sudo apt install libboost-all-dev
```

- Run `make` to build all the independent examples binaries
