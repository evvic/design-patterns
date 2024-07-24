#include <iostream>
#include <string>
using namespace std;

struct CreatureCard
{
    string name;
    int attack, defense;

    CreatureCard(const string& name, const int attack, const int defense)
        : name(name), attack(attack), defense(defense)
    {}

    friend ostream& operator<<(ostream& os, const CreatureCard& obj)
    {
        return os
        << "name: " << obj.name
        << " attack: " << obj.attack
        << " defense: " << obj.defense;
    }
};

class CardModifier
{
private:
    CardModifier* next{ nullptr }; // unique_ptr
protected:
    CreatureCard& creature; // pointer or shared_ptr
public:
    explicit CardModifier(CreatureCard& creature)
      : creature(creature)
    {}

    virtual ~CardModifier() = default;

    void add(CardModifier* cm)
    {
        if (next) next->add(cm);
        else next = cm;
    }

    // two approaches:

    // 1. Always call base handle(). There could be additional logic here.
    // 2. Only call base handle() when you cannot handle things yourself.

    virtual void handle()
    {
      if (next) next->handle();
    }
};

// 1. Double the creature's attack
// 2. Increase defense by 1 unless power > 2
// 3. No bonuses can be applied to this creature

class NoBonusesModifier : public CardModifier
{
public:
    explicit NoBonusesModifier(CreatureCard& creature)
        : CardModifier(creature)
    {}

    void handle() override
    {
        // does not call CardModifier::handle()
        // this breaks the chain from receursively continuing
    }
};

class DoubleAttackModifier : public CardModifier
{
public:
    explicit DoubleAttackModifier(CreatureCard& creature)
        : CardModifier(creature)
    {}

    void handle() override
    {
        creature.attack *= 2;
        CardModifier::handle();
    }
};

class IncreaseDefenseModifier : public CardModifier
{
public:
    explicit IncreaseDefenseModifier(CreatureCard& creature)
        : CardModifier(creature)
    {}


    void handle() override
    {
        if (creature.attack <= 2)
            creature.defense += 1;
        CardModifier::handle();
    }
};

int main()
{
    CreatureCard goblin{ "Goblin", 1, 1 };
    CardModifier root{ goblin };
    DoubleAttackModifier r1{ goblin };
    DoubleAttackModifier r1_2{ goblin };
    IncreaseDefenseModifier r2{ goblin };
    //NoBonusesModifier nb{ goblin }; // effectively Command objects

    //root.add(&nb);
    root.add(&r1);
    root.add(&r1_2);
    root.add(&r2);

    root.handle(); // annoying

    cout << goblin << endl;

    //getchar();
    return 0;
}
