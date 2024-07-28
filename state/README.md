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
- Using Boosts Meta State Machine
    - With Boost meta programming library (MPL)

#### [`msm.cpp`](msm.cpp)
#### Transiitons
```cpp
struct CallDialed {};
struct HungUp {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct PhoneThrownIntoWall {};
```
- All the transitions are declared as empty structs
- Instead of using enums for states and transitions, Boost has them be structs

#### PhoneStateMachine States
```cpp
struct PhoneStateMachine : state_machine_def<PhoneStateMachine>
{
    bool angry{ true }; // start with false

    struct OffHook : state<> {};
```
- The states are also defined as structs but within the state machine class implementing Boost MSM
    - i.e. `OffHook` state

#### PhoneStateMachine State with Entry Function
```cpp
// within PhoneStateMachine class {...
struct Connecting : state<>
{
    template <class Event, class FSM>
    void on_entry(Event const& evt, FSM&)
    {
        cout << "We are connecting..." << endl;
    }
    // also on_exit
};
```
- A function can be declared with the State so it runs on the entry to the state
    - There are functions within the function that can be "overridden":
        - `on_entry`
        - `on_exit`

#### Transition Table
- Similar to the `map` used for the state made by hand

```cpp
// start, event, target, action, guard
struct transition_table : mpl::vector <
    Row<OffHook, CallDialed, Connecting>,
    Row<Connecting, CallConnected, Connected>,
    Row<Connected, PlacedOnHold, OnHold>,
    Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed, 
        PhoneBeingDestroyed, CanDestroyPhone>
> {};
```
- Uses MPL (meta programming library) 
    - A vector of rows of typenames
- Each row specifies the:
    - **starting state**
    - **transition**
    - **final state**
- i.e. `OffHook` transitions with `CallDialed` into `Connecting` state

```cpp
Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed, PhoneBeingDestroyed, CanDestroyPhone>
```
- Additional customization can be applied to a row
- The 4th item in the row is the action
    - This is triggered upon state change
- The 5th item in the row is the guard
    - This struct overloads the `()` operator to return a boolean
    - The function `()` determines whether the state transition is allowed by what it returns

