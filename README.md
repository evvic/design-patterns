# design-patterns
Notes and examples on programming design patterns

# Design Principes
- 5 of the most common design pronciples are covered with notes and examples under [_SOLID](_SOLID/README.md)


# Patterns
- Below are the sections of patterns based on **Gamma Categorization**
    - Named after Erich Gamma, one of the Gang of Four authors

## 1. Creational Design
- Deal with the creation (construction) of objects
- Explicit creation: creation requires a few arguments to the constructor and the object is returned
- Implicit creation: could be implicit to create an object
    - Requires a dependency injection framework, reflection, or another method that created the obejct behind the scenes
- Intialization processes:
    - Wholesale: single statement/constructor call to vreate the entire object
    - Piecewise: Initialization is a complicated process that takes multiple statements
        - step-by-step

### Creational Design Patterns
- [Builder](builder/)
- [Factory](factory/)
    - Abstract Factory
    - Factory Method
- [Prototype](prototype/)
- [Singleton](singleton/)

## 2. Structural Design
- Concerned with the structure of the class/object
    - Class members, class adhering to en interface, etc...
- Many patterns are wrappers that mimic the underlying class interface
- Stress the importance of good API design
    - Make the interface as easy to use as possible

### Structural Design Patterns
- Adapter
- Bridge
- Composite
- Decorator
- Facade
- Flyweight
- Proxy

## 3. Behavioral Design
- There is no central theme to these design patterns
    - They are all different (with some slight overlap)

### Behavioral Design Patterns
- Chain of responsibility
- Command
- Interpreter
- Iterator
- Mediator
- Memento
- Observer
- State
- Strategy
- Template method
- Visitor

# Setup
- Modern C++ is used for these design pattern examples (C++20)
- VSCode interpreter is using `gnu++20`
    - [Change C++ interpreter in VS Code](https://code.visualstudio.com/docs/cpp/config-linux#_cc-configurations)
    - Enter `C/C++: Edit Configurations (UI)` into command palette
    - Change the `C++ standard` value to `gnu++20` or newer