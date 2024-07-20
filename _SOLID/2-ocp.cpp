#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product {
    string name;
    Color color;
    Size size;
};

template <typename T> struct AndSpecification;

template <typename T> struct Specification
{
  virtual ~Specification() = default;
  virtual bool is_satisfied(T* item) const = 0;

  // new: breaks OCP if you add it post-hoc
  /*AndSpecification<T> operator&&(Specification<T>&& other)
  {
    return AndSpecification<T>(*this, other);
  }*/
};

// new: 
template <typename T> 
AndSpecification<T> operator &&(const Specification<T>& first, const Specification<T>& second)
{
    return AndSpecification<T>(first, second);
}

// defines the interface that needs to be implemented by any kind of filter
template <typename T> struct Filter
{
    virtual vector<T*> filter(vector<T*> items, Specification<T> &spec) = 0;
};

struct BetterFilter : Filter<Product>
{
    vector<Product*> filter(vector<Product*> items, Specification<Product> &spec) override
    {
        vector<Product*> result;
        for (auto& item : items)
            if (spec.is_satisfied(item))
            {
                result.push_back(item);
            }
        return result;
    }
};

// To create a filter specification simply inherit from Specification
// and override the is_satisfied function with how the filter should
// compare
struct ColorSpecification : Specification<Product>
{
    Color color;
    ColorSpecification(const Color color) : color(color) {}

    bool is_satisfied(Product* item) const override
    {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product>
{
    Size size;
    SizeSpecification(const Size size) : size(size) {}

    bool is_satisfied(Product* item) const override
    {
        return item->size == size;
    }
};

// combinator of 2 specification to filter
template <typename T>
struct AndSpecification 
: Specification<T>
{
    const Specification<T>& first;
    const Specification<T>& second;

    AndSpecification(Specification<T>& first, Specification<T>& second)
    : first(first), second(second)
    {}

    AndSpecification(const Specification<T>& first, const Specification<T>& second)
    : first(first), second(second)
    {}

    bool is_satisfied(T* item) const override
    {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};


int main() {
    cout << "Open-Closed Principle" << endl;

    // Create some random products to test filtering

    Product apple {"Apple", Color::green, Size::small};
    Product tree {"Tree", Color::green, Size::large};
    Product house {"House", Color::blue, Size::large};

    // Store products in a vector to be filtered

    const vector<Product*> items {&apple, &tree, &house};

    /*** Filter items by passing in an overrided Specification to filter() ***/
    BetterFilter bf;
    ColorSpecification green(Color::green);

    for (auto &item : bf.filter(items, green))
        cout << item->name << " is green" << endl;

    // To build more filter features ontop of this virtual Specification is easy

    // test a combination filter
    SizeSpecification large(Size::large);
    AndSpecification<Product> green_and_large(green, large);

    for (auto &item : bf.filter(items, green_and_large))
        cout << item->name << " is green and large" << endl;

    // test a combination filter created using && overloaded operator

    // AndSpecification<Product> combofilter = ColorSpecification(Color::green) && SizeSpecification(Size::small);
    // ^ Compiler does not like this and makes the AndSpecification with both as just virtual Specification
    ColorSpecification blue(Color::blue);
    AndSpecification<Product> combofilter = blue && large;

    for (auto &item : bf.filter(items, combofilter))
        cout << item->name << " is blue and large" << endl;

    return 0;
}