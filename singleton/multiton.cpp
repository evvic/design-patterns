#include <memory>
#include <iostream>
#include <map>

using namespace std;

enum class Importance
{
    primary,
    secondary,
    tertiary
};

// default Key typename to string but will be using Importance as Key
template <typename T, typename Key = std::string>
class Multiton
{
    static shared_ptr<T> get(const Key& key)
    {
        // check if key is already in the map and return the pointer
        // to the already created object
        if (const auto it = instances.find(key); it != instances.end()) {
            return it->second;
        }
        // else create a new object, add to map,
        // and return pointer to new object
        
        auto instance = make_shared<T>();
        instances[key] = instance;
        return instance;
    }
protected:
    Multiton() = default;
    virtual ~Multiton() = default;
private:
    static map<Key, shared_ptr<T>> instances;
};

// initialize instances map (store of instances)
template <typename T, typename Key>
map<Key, shared_ptr<T>> Multiton<T, Key>::instances;

int main()
{
    return 1;
}