# Chain of Responsibility
- Sequence of handlers processing an event oner after another
- Chain of components who all get a chance to process a command or query
    - Optionally having default processing implementation
    - An ability to to terminate the processing chain
        - One component in the chain an stop the rest of the components from processing

## Motivation
- A "chain" of objects that can affect the object below it
- Similar to a singly linked list where each node can modify those under it
- i.e. a card game with creatures that have attack, defence, etc...
    - Can play card modifiers on top of the base card to chain stats

## Pointer Chain
#### [`cards.cpp`](cards.cpp)

- The creature `CreatureCard` has base abilities
- The abilities can be modified by stacking `CardModifier`s on top
    - The `CardModifier` is a chain what can continuously be added on top of itself

```cpp
```