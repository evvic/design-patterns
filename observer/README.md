# Observer

- Getting notifications when things happen
- Two participants:
    - The **observer** is an object that wishes to be informed about events happening in the system
    - The **observable** is the entity generating the events
        - The observable netity is intrusive
            - i.e. Perswon class needs to be modified so that it can be observable

- Terminology (for Boost, Qt, etc..)
    - Event/**signal**: gives indication when something changed
    - Subscriber/**slot**: handles the signal when it is fired

## Motivation
- Need to be informed when certain things happen
    - i.e. object field changes, object does something, some external event occurs
- Want to listen to events and be notified when they occur

## Observer Example
- Get notified on particular changes in the system
- Get notified whenever the `age` variable is changed in `Person`

### Observer: for object fields changing

#### [`observer.hpp`](observer.hpp)
```cpp
template <typename T>
struct Observer
{
    virtual void field_changed(
        T& source,
        const std::string& field_name
    ) = 0;
};

```
- Interested in observing changes to a types field

#### [`main.cpp`](main.cpp)
```cpp
struct ConsolePersonObserver : public Observer<Person> {
private:
    void field_changed(Person &source, const std::string &field_name) override {
        cout << "Person's " << field_name << " has changed to ";
        if (field_name == "age") cout << source.get_age();
        if (field_name == "can_vote")
            cout << boolalpha << source.get_can_vote();
        cout << ".\n";
    }
};
```
- `ConsolePersonObserver` implements the `Observer` interface
    - This gets notified whenever the field in `Person` has changed
- The final step to make this work is to include some logic in the `Person` class

### Observable: for notifying object field has changed

#### [`observable.hpp`](observable.hpp)
```cpp
template <typename> struct Observer;

template <typename T>
struct Observable
{
    std::vector<Observer<T>*> observers;
    //...
```
- Interface for observable objects
- Contains a list (`observers`) of all subscribers/listeners

```cpp
void Observable::notify(T& source, const std::string& field_name)
{
    for (auto observer : observers)
        observer->field_changed(source, field_name);
}
```
- `notify` is going to inform all observes that some change has been made

```cpp
void Observable::subscribe(Observer<T>& observer)
{
    observers.push_back(&observer);
}
```
- Take the observer as reference and push pack the pointer to the observer to the observers list

```cpp
void Observable::unsubscribe(Observer<T>& observer)
{
    observers.erase(
        remove(observers.begin(), observers.end(), &observer),
        observers.end()
    );
}
```
- erase-remove idiom to remove the observer from the vector of observers\
    - `remove` searches the vector and reorders all matches of `&observer` to the end
        - Then returns an iterator to the first element after the last occurance of `&observer`
        - `remove` doesn't actually remove elements, it just rearranges them
    - `erase` deletes all elements from the returned iterator from `remove` to `observers.end()`


#### [`main.cpp`](main.cpp)
- Update `Person` to trigger notifications upon field changes
```cpp
class Person : public SaferObservable<Person>
{
    int age{0};
```
- Person needs to inherit from `Observable` to use `notify`
```cpp
void Person::set_age(int age)
{
    if (this->age == age) return;

    auto old_can_vote = get_can_vote();
    this->age = age;
    notify(*this, "age");

    if (old_can_vote != get_can_vote())
    notify(*this, "can_vote");
}
```
- Now when using `set_age` method, it can trigger `notify` with the information of the change

> Note this method will not scale well with lots of dependencies (subscribers and observers)

### Using Obersever and Observable
```cpp
Person p;
p.subscribe(ta);

ConsolePersonObserver cpa;
p.subscribe(cpa);
p.set_age(15);
p.set_age(16);
```
### Thread Safety and Reentry
- Using a vector to iterrate through and notify subscribers in a single thread
- Having multiple subscribers to multiple observers wil quickly make this slow and inefficient

#### [`saferobservable.hpp`](saferobservable.hpp)
```cpp
struct SaferObservable
{
    std::vector<Observer<T>*> observers;
    typedef std::recursive_mutex mutex_t;
    mutex_t mtx;
```
- Will implememnt all functions from `Observable` class but use a `recursive_mutex` lock
    - recursive_mutex allows a thread to acquire the same lock multiple times without deadlocking


```cpp
void SaferObservable::notify(T& source, const std::string& field_name)
{
    std::scoped_lock<mutex_t> lock{mtx};
    for (auto observer : observers)
    if (observer)
        observer->field_changed(source, field_name);
}
```
- Member functions are the same as in `Observable` but now have a `scoped_lock` with `recursive_mutex`
    - `recursive_mutex` is used to deadlocking doesnt occur
        - i.e. while in `notify` the subscriber unsubscribes
- Although it is always not recommende to use `recursive_mutex`:
    - Increased complexity of understanding
    - Increased performance overhead as `recursive_mutex` needs to track the lock count