# Iterator
- Fasciliates the traversal of different data structures
    - Iterator is a class that fascilitates the traversal
        - Keeps a reference to the current element
        - Know how to move to a different element
        - Typically requires `++` and `!=` operator overload
- Specifies how to traverse a specific object


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

## Custom Iterator
#### [`it.cpp`](it.cpp)

#### Node
```cpp
template <typename T> struct Node
{
    T value = T();
    Node<T> *left = nullptr;
    Node<T> *right = nullptr;
    Node<T> *parent = nullptr;
    BinaryTree<T>* tree = nullptr;
    // ...
```
- Using doubly-linked tree nodes
    - So traversal back up through the parents is possible

```cpp
template <typename T> struct BinaryTree
{
    Node<T>* root = nullptr;

    explicit BinaryTree(Node<T>* const root)
        : root{ root } 
    {
        root->set_tree(this);
    }
```
- This example uses a "BinaryTree" data structure
- Some type of data structure class is needed to define the custom iterator
    - The `BinrayTree` of nodes can be imagined as a map

```cpp
template <typename U>
    struct LevelOrderIterator
    Node<U>* current;
    queue<Node<U>*> next;

    explicit LevelOrderIterator(Node<U>* current)
        : current(current), next({current})
    {}

    bool operator!=(const LevelOrderIterator<U>& other)
    {
        return current != other.current;
    }
    // ...
typedef LevelOrderIterator<T> iterator;
```
- This iterator `LevelOrderIterator` iterates thrrough the binary tree with level order traversal

```cpp
iterator begin() {
    return iterator{ root };
}
```
- Therefore the `.begin()` returns the address to the root node
    - `.begin` and `root` node are part of the `BinaryTree` class
- `.begin()` returns an `LevelOrderIterator<T>` object pointing to the root node 

```cpp
BinaryTree::LevelOrderIterator<U>& operator++() {
    if (!next.empty()) {           
        // Print front of queue and remove it from queue
        current = next.front();
        next.pop();

        // Enqueue left child
        if (current->left != NULL)
            next.push(current->left);

        // Enqueue right child
        if (current->right != NULL)
            next.push(current->right);
    } 
    else current = nullptr;
    
    return *this;
}
```
- The increment operator is overloaded for the `LevelOrderIterator<U>`
    - This increment now performs level order traversal
- Every increment runs to the next node in the proper order of level order traversal
    - When the traversal is at the end, it returns `nullptr`
        - This is determined if the queue `next` becomes empty (no more nodes to traverse)

