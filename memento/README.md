# Memento

- Goal: keep a memento of an object's state to return to that state
- A token/handle rtepresenting the system state
    - Lets the state be rolled back to the what the token saved

- Rollback to states arbitrarily
- The `Memento` is simply a token/handle class with no functions of its own
- Can be used to implement undo/redo
    - Not recommended if the system has lots of state

- Similar to the Command pattern
    - But the Memento simply saves snapshots of the system it can revert to
    - While the Command records every change and knows how to reverse the change
    - Typically the memento is an immutable construct

## Motivation
- An object/system goes through changes
    - i.e. bank account gets deposits/withdrawals
- Allow user to rollbacl to a particular snapshot of the system

## Memento Example
#### [`memento.cpp`](memento.cpp)

### Revert State With Memento
#### Memento Class
```cpp
class Memento
{
    int balance;
public:
    Memento(int balance) : balance(balance) {}
    friend class BankAccount;
};
```
- Use a Memento to allow the state of the bank account to be saved
- The Memento class in this example only has to store `balance`
    - Because `BankAccount` only has the 1 variable
- It is crucial `Memento` has `BankAccount` as a friend
    - This allows only `BankAccount` to access the `Memento` objects' `balance`
    - Therefore the user cannot modify the memento state before using it to revert the state od the bank account

#### BankAccount Class
```cpp
class BankAccount {
    int balance = 0;
public:
    explicit BankAccount(const int balance) : balance(balance) {}

    Memento deposit(int amount) {
        balance += amount;
        return Memento{ balance };
    }

    void restore(const Memento& m) {
        balance = m.balance;
    }
    // ...
};
```
- Whenever a `deposit` is made:
    - The balance is increased by the amount
    - A new `Memento` object is created with the updated balance
    - The Memento object cannot have it's `balance` changed because the variable is private
- When `restore` is called with a `Memento` object the variable(s) in `BankAccount` are reverted

### Undo and Redo State Changes with Memento
- It is possible to ise Memento pattern for undo/redo mechanism provided the state of the system being saved is small
    - In this BankAccount example the internal state is small

#### New BankAccount Class
- Can walk forwards and backwards through the saved mementos with undo/redo
```cpp
class BankAccount // supports undo/redo
{
private:
    int balance = 0;
    vector<shared_ptr<Memento>> changes;
    int current;
public:
    // ...

```
- Store every memento within the `BankAccount` to allow forward and backward traversal of state change
- Besides the `balance` there is a vector of pointers to Memento objects and a `current` index 
    - The vector `changes` is in order of state change
    - The `current` index is used to track undoing of state change

#### New BankAccount Constructor
```cpp
explicit BankAccount::BankAccount(const int balance)
    : balance(balance)
{
    changes.emplace_back(make_shared<Memento>(balance));
    current = 0;
}
```
- Initalizies the balance and saves this as a memento
- `current` is pointing to the 0th element

```cpp
shared_ptr<Memento> BankAccount::deposit(int amount) {
    balance += amount;
    auto m = make_shared<Memento>(balance);
    changes.push_back(m);
    ++current;
    return m;
}
```
- Create a shared pointer to a `new Memento` object with the new balance
- Add that ponter to the new memento to the changes vector and increment `current`

```cpp
void BankAccount::restore(const shared_ptr<Memento>& m) {
    if (m) {
        balance = m->balance;
        changes.push_back(m);
        current = changes.size() - 1;
    }
}
```
- Check the shared_ptr to a Memento is valid (not just a default initialized shared pointer)
    - This works because `shared_ptr` will evaluate to false if it is not pointing to a constructed object
        - aka is is a nullptr
- Then update the balance and add the Memento ptr to the vector
    - Have current also point to the last (latest) Memento in the vector

```cpp
shared_ptr<Memento> BankAccount::undo() {
    if (current > 0) {
        --current;
        auto m = changes[current];
        balance = m->balance;
        return m;
    }
    return{}; // returning a null shared_ptr
}
```
- First check there is a previous state to undo to (`current > 0`)
- Decrement current to the previous
- Update the balance to the Memento stored at `changes[current]`
- Return that memento

```cpp
shared_ptr<Memento> redo() {
    if (current + 1 < changes.size()) {
        ++current;
        auto m = changes[current];
        balance = m->balance;
        return m;
    }
    return{}; // returning a null shared_ptr
}
```
- First check redo is possible, that there is a more recent state to redo to
- Then simply incrememnt `current` index, update the balance, and return the Memento current now points to

