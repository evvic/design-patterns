#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

enum class State
{
    OffHook,
    Connecting,
    Connected,
    OnHold,
    OnHook
};

inline ostream& operator<<(ostream& os, const State& s)
{
    switch (s)
    {
    case State::OffHook:
        os << "off the hook";
        break;
    case State::Connecting:
        os << "connecting";
        break;
    case State::Connected: 
        os << "connected";
        break;
    case State::OnHold:
        os << "on hold";
        break;
    case State::OnHook:
        os << "on the hook";
        break;
    }
    return os;
}

enum class Trigger
{
    CallDialed,
    HungUp,
    CallConnected,
    PlacedOnHold,
    TakenOffHold,
    LeftMessage,
    StopUsingPhone
};

inline ostream& operator<<(ostream& os, const Trigger& t)
{
    switch (t)
    {
    case Trigger::CallDialed:
        os << "call dialed";
        break;
    case Trigger::HungUp:
        os << "hung up";
        break;
    case Trigger::CallConnected:
        os << "call connected";
        break;
    case Trigger::PlacedOnHold:
        os << "placed on hold";
        break;
    case Trigger::TakenOffHold:
        os << "taken off hold";
        break;
    case Trigger::LeftMessage: 
        os << "left message";
        break;
    case Trigger::StopUsingPhone:
        os << "putting phone on hook";
        break;
    default: break;
    }
    return os;
}

class Phone {

    map<State, vector<pair<Trigger, State>>> rules;

    State currentState{ State::OffHook }, exitState{ State::OnHook };

public:
    Phone() {
        rules[State::OffHook] = {
            {Trigger::CallDialed, State::Connecting},
            {Trigger::StopUsingPhone, State::OnHook}
        };

        rules[State::Connecting] = {
            {Trigger::HungUp, State::OffHook},
            {Trigger::CallConnected, State::Connected}
        };

        rules[State::Connected] = {
            {Trigger::LeftMessage, State::OffHook},
            {Trigger::HungUp, State::OffHook},
            {Trigger::PlacedOnHold, State::OnHold}
        };

        rules[State::OnHold] = {
            {Trigger::TakenOffHold, State::Connected},
            {Trigger::HungUp, State::OffHook}
        };
    }

    State getExitState()
    {
        return exitState;
    }

    State getState()
    {
        return currentState;
    }

    map<State, vector<pair<Trigger, State>>> getRules()
    {
        return rules;
    }

    void setState(int input)
    {
        if (input < 0 || (input+1) > rules[currentState].size())
        {
            std::cout << "Incorrect option. Please try again." << "\n";
            return;
        }
        currentState = rules[currentState][input].second;
    }

};

int main(char* argv[])
{


    Phone phone;

    while (true)
    {
        cout << "The phone is currently " << phone.getState() << endl;
    // select_trigger:
        cout << "Select a trigger:" << "\n";

        int i = 0;
        for (auto item : phone.getRules())
        {
            cout << i++ << ". " << item.first << "\n";
        }

        int input;
        cin >> input;
        phone.setState(input);

        
        if (phone.getState() == phone.getExitState()) break;
    }

    cout << "We are done using the phone" << "\n";

    return 0;
}
