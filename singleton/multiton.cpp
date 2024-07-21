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
public:
    static shared_ptr<T> get(const Key& key)
    {
        if (const auto it = instances.find(key); it != instances.end()) {
            return it->second;
        }
        
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

// Class to use the Multiton
// Can have up to 3 printers as there are 3 possible Keys from Importance enum
class Printer
{
public:
    Printer() {
        ++Printer::totalInstanceCount;
        cout << "A total of " << Printer::totalInstanceCount
             << " instances created so far\n";
    }
private:
    static int totalInstanceCount;
};

// initialize static totalInstanceCount outside of class
int Printer::totalInstanceCount = 0;

int main()
{
    typedef Multiton<Printer, Importance> mt;

    std::shared_ptr<Printer> main = Multiton<Printer, Importance>::get(Importance::primary);
    std::shared_ptr<Printer> second = Multiton<Printer, Importance>::get(Importance::secondary);
    std::shared_ptr<Printer> another = Multiton<Printer, Importance>::get(Importance::secondary);

    // another and second will have the same pointer as they both used the same Key
    cout << "second and another pointing to the same object? " << ((another == second) ? "True" : "False") << endl;

    return 1;
}