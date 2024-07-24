# Chain of Responsibility
- Sequence of handlers processing an event oner after another
- Chain of components who all get a chance to process a command or query
    - Optionally having default processing implementation
    - An ability to to terminate the processing chain
        - One component in the chain an stop the rest of the components from processing
- CoR can be represented as:
    - A chain of pointers/references (singly linked list)
    - Centralized list (broker)

## Motivation
- A "chain" of objects that can affect the object below it
- Similar to a singly linked list where each node can modify those under it
- i.e. a card game with creatures that have attack, defence, etc...
    - Can play card modifiers on top of the base card to chain stats

## Pointer Chain
- Decentralized method for chaining

#### [`cards.cpp`](cards.cpp)

- The creature `CreatureCard` has base abilities
- The abilities can be modified by stacking `CardModifier`s on top
    - The `CardModifier` is a chain what can continuously be added on top of itself

```cpp
void CardModifier::add(CardModifier* cm)
{
    if (next) next->add(cm);
    else next = cm;
}
```
- The card modifiers when they are `add`ed on top of each other construct a linekd list
    - Recursively go through every `CardModifier` until t he last one where the pointer to the new `cm` is added

```cpp
virtual void CardModifier::handle()
{
    if (next) next->handle();
}
```
- All types of card modifier classes will recursively perform some logic
    - then call the next modifier with `next->handle()`

```cpp
void NoBonusesModifier::handle() override {}
```
- The `NoBonusesModifier` breaks the chain by not invoking `next->handle()`
- Therefore this card applied then does not allow the bonuses that come before it to be applied

## Broker Chain
- Event Broker which acts as **centralized** list
- The ability to **query** a creatures stat
    - Every live element in the game has the ability to modify this stat

```cpp
struct Game 
{
    signal<void(Query&)> queries;
};
```
- A **signal** is a way to define an event people/objects can subscribe to
```cpp
struct Query
{
    string creature_name;
    enum Argument { attack, defense } argument;
    int result;
    ... // constructor
}
```
- A `Query` is a class to request information (about a creature)
    - Specify which value (`Argument`)
- The query goes through every subscriber on that signal before returning the request
    - and the subscriber can do something with that query

```cpp
int CreatureCard::GetAttack() const
{
    Query q{ name, Query::Argument::attack, attack };
    game.queries(q);
    return q.result;
}
```
- Here to get the attack stat of a creature the `Game` object is invoked with the `Argument::attack` Query

```cpp
class DoubleAttackModifier : public CardModifier
{
    connection conn;
public:
    DoubleAttackModifier(Game& game, CreatureCard& creature)
        : CardModifier(game, creature) {
        conn = game.queries.connect([&](Query& q) {
            if (q.creature_name == creature.name && 
                q.argument == Query::Argument::attack) {
                q.result *= 2;
            }
        });
    }
    ... // other class stuff
};
```
- The `DoubleAttackModifier` contructor subscribes to the `Game` query
    - The subscribed connection is saved as `connection conn`
- `conn` holds a lambda function that triggers on a query
    - It doubles the attack (`q.result *= 2;`) 
    - But only if the creature ame matches and the query is for getting the attack stat

