# Iterator
- Fasciliates the traversal of different data structures
    - Iterator is a class that fascilitates the traversal
        - Keeps a reference to the current element
        - Know how to move to a different element


## Motivation
- Core functionality of many data structures to be able to travers

## Iterators in the STL
#### Member iterator
```cpp
vector<string> names{ "john", "jane", "jill", "jack" };

vector<string>::iterator it = names.begin();
```
- Most STL data structures have a .begin() member function built in
    - This returns the pointer to the first element in the data structure

#### Global Iterator
```cpp
vector<string>::iterator it = begin(names);
```
- There is also a global iterator `begin()` that can be called on data structures
    - Arrays don't have member functions so this works with arrays!
    
#### Dereference Iterator
```cpp
cout << "first name is " << *it << "\n";
```
- Derefernce the iterator (`*it`)
    - Very similar to a pointer but incompatible

#### Increment Iterator
```cpp
while (++it != names.end())
{
    cout << "another name: " << *it << "\n";
}

// reverse iterator
for (auto ri = rbegin(names); ri != rend(names); ++ri) {
    // traversing the vector in reverse
}
```
- `names.end()` **does not give** an iterator that points to the last element
    - It gives ab iterator which points to the element **one past the last element**
- Also exists as a global function `end()`
