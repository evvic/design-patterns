# Command
- An object which represents an instuction or a set of instructions to perform a particular action
- Contains all the  information necessary for the action to be taken
- Encapsulate the details of the operation into a separate object
    - Can store/serialize th object
- Define the the instruction(s) for applying the command
- Optionally have instructions to rollback/undo
- Macros = composite commands

## Motivation
- Ordinary C++ statements are perishable
    - History of assignments
        - Could go back and reverse assignments made
- Want an object which represents an operation
- i.e. GUI command like terminal macro

## Command vs. Query Separation
- Command = asking for an action or change 
    - "please set your value to 2"
    - Get no result back (return no value)
- Query = asking for information
    - "please give me your attack value"
    - No change to the system but gets the value back
- Command Query Separation = Split your system into separate components and different means of sending commands and queries
    - Having separate means of sending commands and queries
- Gang of Four only mentions Commands, but the queries are basically wrapped into the command design pattern

## Command Example
[`bankstatement.cpp`](bankstatement.cpp)

#### Command Interface
```cpp
struct Command
{
    virtual ~Command() = default;
    virtual void call() const = 0;
    virtual void undo() const = 0;
};
```
- The Command interface will be used 
- `call()` is attached to an object and actually modifies it when it is invoked
```cpp
BankAccount ba;
auto history = BankAccountCommand{ba, BankAccountCommand::deposit, 100};
```
- The `BankAccountCommand` class wraps around `BankAccount` and inherits `Command`
- Each `BankAccountCommand` obejct created is like recording that command occured
    - In the constructor the command runs and then stores the information of the action
    - Every action to the `BankAccount` should be creating a `BankAccountCommand`

#### CompositeBankAccountCommand
```cpp
struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command {
    CompositeBankAccountCommand(const initializer_list<value_type>& items)
        : vector<BankAccountCommand>(items) 
    {}

    void call() const override {
        for (auto& cmd : *this) cmd.call();
    }

    void undo() const override {
        for (auto& cmd : *this) cmd.undo();
    }
};
```
- The `CompositeBankAccountCommand` is what will hold the transaction (command) history
    - It inherits from `vector<BankAccountCommand>` making it iterable (`for (auto& cmd : *this)`)
    - Also inherits `Command`, thefore making `CompositeBankAccountCommand` a **composite**
- `BankAccountCommand`s can be pushed onto the vector
    - They commands are not executed until `CompositeBankAccountCommand::call()` is invoked

#### MoneyTransferCommand
```cpp
struct MoneyTransferCommand : DependentCompositeCommand
{
    MoneyTransferCommand(
        BankAccount& from,
        BankAccount& to,
        int amount
    ) : DependentCompositeCommand {
        BankAccountCommand{from, BankAccountCommand::withdraw, amount},
        BankAccountCommand{to, BankAccountCommand::deposit, amount}
    } 
    {}
};
```
- Creates 2 inverse transactions to similuate transferring money from one account to the other
- Relies on `DependentCompositeCommand` to verify the entire sub set of commands for the transfer all succeeded

