# Template Method

- A high-level blurprint for an algorithm to be completed by inheritors
- Allows definition of the 'skeleton' of the algorithm
    -   With concrete implementation defined in the subclasses
- Algorithms can be decomposed into common parts + specifics

- Similar to the strategy pattern
    - The strategy pattern accomplishes this through composition
    - High level algorithm uses an interface
    - Concrete implementations implement the interface
- Template Method does the same thing but through inheritance
    - Overall algorithm is typcially an abstract base class
    - Inheritors of the concrete algorithm override the key abstract members 
    - The parent template method is then invoked

## Motivation

## Template Game Example
