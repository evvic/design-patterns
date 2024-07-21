#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#include "Person.hpp"
#include "PersonBuilder.hpp"
// #include "PersonAddressBuilder.hpp" // not needed
// #include "PersonJobBuilder.hpp"     // not needed

int main() {
    
    Person p = Person::create()
        .lives()
            .at("123 Unicorn Road")
            .with_postcode("99119")
            .in("San Diego")
        .works()
            .at("Qualcomm")
            .as_a("Software Engineer")
            .earning(100400);

    // can jump from PersonAddressBuilder to PersonJobBuilder
    // with ease because they share a common interface

    // cout << p << endl;

    return 0;
}
