#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Memento
{
    int balance;
public:
    Memento(int balance) : balance(balance) {}
    friend class BankAccount;
    friend class BankAccount2;
};

class BankAccount
{
    int balance = 0;
public:
    explicit BankAccount(const int balance) : balance(balance) {}

    Memento deposit(int amount)
    {
        balance += amount;
        return Memento{ balance };
    }

    void restore(const Memento& m)
    {
        balance = m.balance;
    }

    friend ostream& operator<<(ostream& os, const BankAccount& obj)
    {
        return os << "balance: " << obj.balance;
    }
};

class BankAccount2 // supports undo/redo
{
    int balance = 0;
    vector<shared_ptr<Memento>> changes;
    int current;
public:
    explicit BankAccount2(const int balance)
        : balance(balance)
    {
        changes.emplace_back(make_shared<Memento>(balance));
        current = 0;
    }

    shared_ptr<Memento> deposit(int amount)
    {
        balance += amount;
        auto m = make_shared<Memento>(balance);
        changes.push_back(m);
        ++current;
        return m;
    }

    void restore(const shared_ptr<Memento>& m)
    {
        if (m)
        {
            balance = m->balance;
            changes.push_back(m);
            current = changes.size() - 1;
        }
        cout << "Cannot restore: memento is invalid." << endl;
    }

    shared_ptr<Memento> undo()
    {
        if (current > 0)
        {
            --current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        cout << "Cannot undo: already at oldest state." << endl;
        return{}; // returning a null shared_ptr
    }

    shared_ptr<Memento> redo()
    {
        if (current + 1 < changes.size())
        {
            ++current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        cout << "Cannot redo: already at latest state." << endl;
        return{}; // returning a null shared_ptr
    }

    friend ostream& operator<<(ostream& os, const BankAccount2& obj)
    {
        return os << "balance: " << obj.balance;
    }
};

void memento()
{
    BankAccount ba{ 100 };
    auto m1 = ba.deposit(50); // 150
    auto m2 = ba.deposit(25); // 175
    cout << ba << "\n";

    // undo to m1
    ba.restore(m1);
    cout << ba << "\n";

    // redo
    ba.restore(m2);
    cout << ba << "\n";
}

void undo_redo()
{
    BankAccount2 ba{ 100 };
    // auto mem1 = ba.deposit(50);
    // ba.deposit(25); // 125
    cout << ba << "\n";

    auto mem1 = ba.undo();
    cout << "Undo 1: " << ba << "\n";
    ba.undo();
    cout << "Undo 2: " << ba << "\n";
    ba.redo();
    cout << "Redo 2: " << ba << "\n";

    // 
    ba.restore(mem1);
}

int main()
{
    // memento()
    undo_redo();

    return 0;
}
