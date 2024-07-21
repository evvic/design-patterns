#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <sstream>

using namespace std;
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace boost;

struct Address
{
    string street;
    string city;
    int suite;

    Address() {}

    Address(const string& street, const string& city, const int suite)
        : street{street}, city{city}, suite{suite}
    {}

    friend ostream& operator<<(ostream& os, const Address& obj)
    {
        return os
        << "street: " << obj.street
        << " city: " << obj.city
        << " suite: " << obj.suite;
    }

private:
    friend class boost::serialization::access;

    template <class archive>
    void serialize(archive& ar, const unsigned version) const
    {
        ar & street;
        ar & city;
        ar & suite;
    }

    template <class archive>
    void save(archive& ar, const unsigned version) const
    {
        ar << street;
        ar << city;
        ar << suite;
    }

    template <class archive>
    void load(archive& ar, const unsigned version) const
    {
        ar >> street;
        ar >> city;
        ar >> suite;
    }
};


struct Contact
{
private:
    string name;
    Address* address;

public:
    Contact& operator=(const Contact& other)
    {
        if (this == &other)
        return *this;
        name = other.name;
        address = other.address;
        return *this;
    }

    Contact() {} // required for serialization   

    Contact(const Contact& other) 
        : name{other.name}
    {
        address = new Address(
            other.address->street, 
            other.address->city, 
            other.address->suite
        );
    }
private:
    friend class boost::serialization::access;

    template <class archive>
    void serialize(archive& ar, const unsigned version) const
    {
        ar & name;
        ar & address;
    }

    template <class archive>
    void save(archive& ar, const unsigned version) const
    {
        ar << name;
        ar << address;
    }

    template <class archive>
    void load(archive& ar, const unsigned version)
    {
        ar >> name;
        ar >> address;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

public:
    Contact(string name, Address* address)
        : name{name}, address{address}
    {}
    ~Contact()
    {
        delete address;
    }

    void setName(const string& name) {this->name = name;}
    void setSuite(const int suite) {this->address->suite = suite;}


    friend ostream& operator<<(ostream& os, const Contact& obj)
    {
        return os
        << "name: " << obj.name
        << " works at " << *obj.address; // note the star here
    }
};

struct EmployeeFactory
{
    // static Contact main;
    // static Contact aux;

    static unique_ptr<Contact> NewMainOfficeEmployee(string name, int suite)
    {
        static Contact proto{"",  new Address {"123 Main Office Addy", "Maine", 0}};
        return NewEmployee(name, suite, proto);
    }

    static unique_ptr<Contact> NewAuxOfficeEmployee(string name, int suite)
    {
        static Contact proto{"",  new Address {"123 Auxilary Office Addy", "Connecticut", 0}};
        return NewEmployee(name, suite, proto);
    }

    private:
    static unique_ptr<Contact> NewEmployee(string name, int suite, Contact& proto)
    {
        auto result = make_unique<Contact>(proto);
        result->setName(name);
        result->setSuite(suite);
        return result;
    }
};

//Contact EmployeeFactory::main{ "", new Address{ "123 East Dr", "London", 0 } };
//Contact EmployeeFactory::aux{ "", new Address{ "123B East Dr", "London", 0 } };

int main()
{
    // this is tedious
    // Contact john{ "John Doe", new Address{"123 East Dr", "London"} };
    // Contact jane{ "Jane Doe", new Address{"123 East Dr", "London"} };

    auto clone = [](const Contact& c)
    {
        // Serialize object
        ostringstream oss;
        archive::text_oarchive oa(oss);

        oa << c;

        // Check serialized data
        string s = oss.str();
        cout << s << endl;

        // Deserialize into object
        istringstream iss(s);
        archive::text_iarchive ia(iss);

        Contact *result; //pointer
        ia >> result;
        return result;
    };

    auto john = EmployeeFactory::NewMainOfficeEmployee("John", 420);
    auto jane = clone(*john);

    return 0;
}