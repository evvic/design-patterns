#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person
{
    string name;
};

// Abstraction interface to have Research not depend so heavily on Relationships implementatin of data
// Like an API to connect the low-level and high level modules
struct RelationshipBrowser
{
    virtual vector<Person> find_all_children_of(const string& name) = 0;
};

// low-level module
// functionality for data storage with utility functions
// inhering functions from RelationshipBrowser allows changes made to 
// Relationships to stay there
struct Relationships : RelationshipBrowser
{
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_and_child(const Person& parent, const Person& child)
    {
        // must add relationship in both directions
        relations.push_back(make_tuple(parent, Relationship::parent, child));
        relations.push_back(make_tuple(child, Relationship::child, parent));
    }

    vector<Person> find_all_children_of(const string& name) override
    {
        vector<Person> result;
        for (auto&& [first, rel, second] : relations)
        {
            if (first.name == name && rel == Relationship::parent)
            {
                result.push_back(second);
            }
        }
        return result;
    }
};

// high-level
// performs research on the low-level module
// Directly using the Relationships class would leave this class
// vulnerable to changes
struct Research
{
    Research(RelationshipBrowser& browser)
    {
        for (auto& child : browser.find_all_children_of("Eric") )
        {
            cout << "Eric has a child named " << child.name << endl;
        }
    }
};

int main()
{
    Person parent{"Eric"};
    Person child1{"Alex"}, child2{"Tanna"};

    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);

    Research _(relationships);
    
    return 0;
}