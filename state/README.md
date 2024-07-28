# State
 


## Classic State Implementation
- Classic state is not realistic to implement
- Using actual classes for each state
#### classic.cpp
```cpp
struct State {
    virtual void on(LightSwitch *ls) {
        cout << "Light is already on\n";
    }
    virtual void off(LightSwitch *ls) {
        cout << "Light is already off\n";
    }
};
```
- Virtual functions `on` and `off` 
    - Not purely virtual

```cpp
struct OnState : State {
    OnState() {
        cout << "Light turned on\n";
    }

    void off(LightSwitch* ls) override;
};
```
- Only want to verride the function of the state you are not in
- i.e. `OnState` overrides the `off` function
    - The definition for the override occurs after the rest of the class declarations
        - Else there would be a dependency issue with using `LightSwitch` object
- The `OffState` has the same class design except it overrides the `on` function from State

#### Override State Methods
```cpp
void OffState::on(LightSwitch* ls) {
    cout << "Switching light on...\n";
    ls->set_state(new OnState());
    delete this;
}
```
- This occurs after the `LightSwitch` class definition
    - But it shows how `OnState` and `OffState` implement switching state between each other

```cpp
class LightSwitch
{
    State *state;
public:
    LightSwitch() {
        state = new OffState();
    }
    void set_state(State* state) {
        this->state = state;
    }
    void on() { state->on(this); }
    void off() { state->off(this); }
};
```
- `LightSwitch` contains state that can either be on or off
- The constructor sets the state to off
- Use `on` and `off` to change the state

#### Running classic implementation
```cpp
LightSwitch ls;
ls.on();
ls.off();
ls.off();
```
- The second consecutive time calling `off` will not change state from off to off
    - It will give the message "Light is already off"

### Handmade State Implementation
- The typical method uses states as enum members

#### [`handmade.cpp`](handmade.cpp)
#### Enum States
```cpp
enum class State
{
    OffHook,
    Connecting,
    Connected,
    OnHold,
    OnHook
};
```
- Define the states with an enum

#### Enum Triggers
```cpp
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
```
- Triggers are made to define the transitions between states
    - i.e. `CallConnected` trigger would lead to `Connected` state
    - i.e. `HungUp` trigger leads to `OffHook`

#### State Change Rules
```cpp
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
```
- Rules determine which state can be transitioned to other states depending on triggers
    - i.e. in `OffHook` State, `Trigger::CallDialed` would trigger to `Connecting` state

### Boost MSM (Meta State Machine)
