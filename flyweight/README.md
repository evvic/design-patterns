# Flyweight
- Space optimization design pattern
- A space optimization technique that allows using less memory by storing externally the data associated with similar objects
- Store common data externally
    - Refer to data via indices or pointers
    - Define the idea of "ranges" on homogeneous collections

## Motivation
- Avoid redundancy when story data
- i.e. data base with lots of users
    - Plenty of users with (duplicate) first/last names
    - No sense in storing same first/last name over and over again
    - Store a list of names with pointers to them
- i.e. bold or italic text
    - Format whole words instead of the individual characters
    - Format via ranges

## Flyweight Example
#### [`flyweight.cpp`](flyweight.cpp)

- There is a `User` object created for every user
- Storing each user's first and last name will have many redundancies in data if there are hundreds of thousands of users

#### Database
```cpp
typedef uint32_t key;

struct User {
    ... // other members
protected:
    static bimap<key, string> names;
}
```
- The `Users` class will use a static `bimap<key, string>` as a makeshift database to store all (non-duplicate) names
    - A `bimap` is a bidirectional map that has efficient lookups in **both directions**
        - Search by key for the value, or by value for the key
    - This is useful here because the bimap will be searched by the names too, to see if they exist

#### Add to database
```cpp
static key User::add(const string& s)
{
    auto it = names.right.find(s);
    if (it == names.right.end())
    {
        // add it
        key id = ++seed;
        names.insert(bimap<key, string>::value_type(seed, s));
        return id;
    }
    return it->second;
}
```
- The `add()` function handles adding new names (strings) to the bimap
    - First check the name (string) does not exist in the `.right` part of the bimap
    - Then give a new id value to the string and add both to the bimap
- `add` returns a `Key` (uint32_t) to the string name

#### Constructor
```cpp
User::User(const string& first_name, const string& last_name)
    : first_name{add(first_name)}, last_name{add(last_name)}
{}
```
- The `User` constructor takes in the first and last name strings
    - But the `first_name` and `last_name` members are `Key` types!
    - So the `add()` function wraps around the string agruments to return their Key

#### Retrieve name by Key
```cpp
const string& get_last_name() const
{
    return names.left.find(last_name)->second;
}
```
- The `User` object needs to give the first/last name by retrieving from the bimap "database"
    - The `bimap` `names` is is given the key for the name and returns the name

## Boost Flyweight Example
#### [`boostflyweight.cpp`](boostflyweight.cpp)
- Boost library has a flyweight method instead of implementing a custom flyweight method!

#### BoostUser class
```cpp
struct BoostUser
{
    flyweight<string> first_name, last_name;

    BoostUser(const string& first_name, const string& last_name) {}
};
```
- The flyweight just wraps around the desired params!
