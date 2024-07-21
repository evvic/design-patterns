#include <iostream>
#include <fstream>
#include <map>

using namespace std;

#include <boost/lexical_cast.hpp>

using namespace boost;


class SingletonDatabase
{
    SingletonDatabase()
    {
        cout << "Constructing database..." << endl;
        ifstream ifs("capitals.txt");
        string s, s2;

        while (getline(ifs, s))
        {
            getline(ifs, s2);
            int population = lexical_cast<int>(s2);
            capitals[s] = population;
        }
    }
    map<string, int> capitals;
public:
    // To make a safe singleton, delete the use of 
    // copy constructor and assignment operator
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }

    int getPopulation(const string& name)
    {
        return capitals[name];
    }
};

int main()
{
    cout << SingletonDatabase::get().getPopulation("Tokyo") << endl;
    cout << SingletonDatabase::get().getPopulation("Beijing") << endl;

    return 0;
}
