#include <iostream>
#include <string>
using namespace std;

#include <boost/signals2.hpp>
using namespace boost::signals2;


struct Query
{
    string creature_name;
    enum Argument { attack, defense } argument;
    int result;


    Query(const string& creature_name, const Argument argument, const int result)
        : creature_name(creature_name), argument(argument), result(result)
    {}
};

// mediator
struct Game 
{
    signal<void(Query&)> queries;
};

class CreatureCard
{
    Game& game;
    int attack, defense;
public:
    string name;
    CreatureCard(Game& game, const string& name, const int attack, const int defense)
        : game(game), attack(attack), defense(defense), name(name)
    {}
    
    // no need for this to be virtual
    int GetAttack() const
    {
        Query q{ name, Query::Argument::attack, attack };
        game.queries(q);
        return q.result;
    }

    friend ostream& operator<<(ostream& os, const CreatureCard& obj)
    {
        return os
        << "name: " << obj.name
        << " attack: " << obj.GetAttack() // note here
        << " defense: " << obj.defense;
    }
};

class CardModifier
{
    Game& game;
    CreatureCard& creature;
public:
    virtual ~CardModifier() = default;

    // there is no handle() function

    CardModifier(Game& game, CreatureCard& creature)
        : game(game), creature(creature)
    {}
};

class DoubleAttackModifier : public CardModifier
{
    connection conn;
public:
    DoubleAttackModifier(Game& game, CreatureCard& creature)
        : CardModifier(game, creature)
    {
        // whenever someone wants this creature's attack,
        // we return DOUBLE the value
        conn = game.queries.connect([&](Query& q) {
            if (q.creature_name == creature.name && 
                q.argument == Query::Argument::attack)
            {
                q.result *= 2;
            }
        });
    }

    ~DoubleAttackModifier()
    {
        conn.disconnect();
    }
};

// similar idea, but Query instead of Command
int main(int ac, char** av)
{
    Game game;
    CreatureCard goblin{ game, "Strong Goblin", 2, 2 };

    cout << goblin << endl;

    // use braces to temporarily apply DoubleAttackModifier
    {
        cout << "Adding DoubleAttackModifier" << endl;
        DoubleAttackModifier dam{ game, goblin };

        cout << goblin << endl;
    }

    cout << "Removed DoubleAttackModifier" << endl;

    cout << goblin << endl;

    return 0;
}
