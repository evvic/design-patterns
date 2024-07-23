#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
using namespace boost;

// Use the Boost flyweight library to wrap and store the strings in a static object
// that does not hold duplicates!

struct BoostUser
{
    // users share names! e.g., John Smith
    flyweight<string> first_name, last_name;
    //string first_name, last_name;
    // ...

    BoostUser(const string& first_name, const string& last_name) {}
};



int main()
{
    BoostUser john_doe{ "John", "Doe" };
    BoostUser jane_doe{ "Jane", "Doe" };

    cout << "Do Jane Doe and John Doe have the same memory address for their first name?" << endl
         << boolalpha <<  (&jane_doe.first_name.get() == &john_doe.first_name.get()) << endl;
    
    cout << "Do Jane Doe and John Doe have the same memory address for their last name?" << endl
         << boolalpha <<  (&jane_doe.last_name.get() == &john_doe.last_name.get()) << endl;

    return 0;
}