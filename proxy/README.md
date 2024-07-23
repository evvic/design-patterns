# Proxy
- An interface for accessing a particular resource
- A class that functions as an interface to a particular resource
    - That resource may be:
        - remove
        - expensive to construct
        - may require logging or someother functionality
- A proxy is an object which looks and behaves as if it were the object its proxying

## Motivation
- Allows the same interface with different behavior in the background

## Smart Pointer
- The C++ smart pointers is a proxy design

### Difference between `make_shared<>` and `shared_ptr<>` smart pointers
- Both `make_shared` and `shared_ptr` track how many smart pointer objects point to the created object
    - When all the pointers are deallocated, the object is automatically removed from memory
```cpp
MyClass* rawPtr = new MyClass();
std::shared_ptr<MyClass> ptr2(rawPtr);
```
- `shared_ptr` does not create the object
    - It is created by being constructed with the raw pointer to the constructed objecy
```cpp
std::shared_ptr<MyClass> = std::make_shared<MyClass>();
```
- `make_shared` can create the object and the `shared_ptr` in one line
    - Provides a more concise way to make `shared_ptr` objects
        - More efficient for not needing 2 allocations (with using `new`)

### Create object via smart pointer
#### [`sharedpointer.cpp`](sharedpointer.cpp)
```cpp
shared_ptr<CurrentAccount> b = make_shared<CurrentAccount>(123);
BankAccount* actual = b.get();
```
- `b` acts like it's a pointer when it really is a smart pointer
- The `.get()` method on a smart pointer returns the raw pointer to the object

## Property Proxy
- Instead of manually creating each individual getter/setter for each property in class,
    - Use Property Proxy!
- A `template struct` `Property` can be created to handle the basic properties

#### [`property.cpp`](property.cpp)
```cpp
template <typename T> struct Property
{
    T value;
    Property(const T initialValue) {
        *this = initialValue;
    }
    operator T() {
        return value;
    }
    T operator =(T newValue) {
        return value = newValue;
    }
};
```
- Overrides the convert `()` operator to "get" the data within the struct (getter)
- Overrides the assignment `=` operator to directly assign the `T` property data within the `Property` struct

## Virtual Proxy
- Gives you the appearance of working on the same object as usual except the base object might've never have been created

#### [`virtual.cpp`](virtual.cpp)
```cpp
struct Bitmap : Image {
    Bitmap(const string& filename) {
        cout << "Loading image from " << filename << endl;
    }

    void draw() override {
        cout << "Drawing image" << endl;
    }
};
```
- No point in loading the bitmap that was constructed until it's used
    - i.e. `Bitmap::draw()`

- The virtual proxy wraps around the `Bitmap` and defers the loading of the bitmap until it is necessary

#### Virtual Proxy
```cpp
struct LazyBitmap : Image
{
    LazyBitmap(const string& filename): filename(filename) {}
    ~LazyBitmap() { delete bmp; }
    void draw() override {
        if (!bmp)
        bmp = new Bitmap(filename);
        bmp->draw();
    }
private:
    Bitmap* bmp{nullptr};
    string filename;
};
```
- Image will not be loaded until it is needed
    - i.e. `LazyBitmap::draw()`
- Both use the `Image` interface
- Allows us to get an object but isn't made yet

## Communication Proxy
#### C++ library requirement
```bash
sudo apt install libcpprest-dev libxmu-dev libxmu-headers freeglut3-dev libxext-dev libxi-dev
```
- `wstring` stores chars as **wide chars**
    - Typically 2 or 4 bytes in size per char
