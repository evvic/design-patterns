# Template Method

- A high-level blurprint for an algorithm to be completed by inheritors
- Allows definition of the 'skeleton' of the algorithm
    -   With concrete implementation defined in the subclasses
- Algorithms can be decomposed into common parts + specifics

- Similar to the strategy pattern
    - The strategy pattern accomplishes this through composition
    - High level algorithm uses an interface
    - Concrete implementations implement the interface
- Template Method does the same thing but through inheritance
    - Overall algorithm is typcially an abstract base class
    - Inheritors of the concrete algorithm override the key abstract members 
    - The parent template method is then invoked

## Motivation
- Define an algorithm at a high level
- Define constituent parts as abstract methods
- Then inherit from the algorithm class, providing the necessary overrides

## Template Game Example
- The algorithm is not defined in some external class but in the base class
 
#### Abstract Template Class Game [`game.cpp`](game.cpp)
```cpp
class Game
{
public:
	explicit Game(int number_of_players) : number_of_players(number_of_players) {}

	void run()
	{
		start();
		while (!have_winner())
			take_turn();
		cout << "Player " << get_winner() << " wins.\n";
	}

protected:
	virtual void start() = 0;
	virtual bool have_winner() = 0;
	virtual void take_turn() = 0;
	virtual int get_winner() = 0;

	int current_player{ 0 };
	int number_of_players;
};
```
- The high-level abstract class that requires its child class to inherit from it
- Requires `number_of_players` to be initialized
- `run` is to emulate a game is being played by letting all players make a turn until `have_winner` method returns true
- Pure virtual members that the inheritor has override and provide definitions for:
    - `start`
    - `have_winner`
    - `take_turn`
    - `get_winner`

#### Inheritor Chess Game
```cpp
class Chess : public Game
{
public:
	explicit Chess() : Game{ 2 } {}
protected:
    // ....
private:
	int turns{ 0 }, max_turns{ 10 };
};
```
- The `Chess` class inehrits from `Game` and has to override all the virtual members

### Running Game
```cpp
Chess chess;
chess.run();
```
- `chess.run()` is a high-level skeleton algorithm within `Game` that requires the inherited concrete `Game` class to have implemented all the virtual functions
    - run requires all the virtual functions to be implemented

### Differences to Strategy Pattern
- With Template Method it is expected to inherit the abstract class and provide the implementatiosn for the lower level details of the algorithm
- **Versus Strategy** where the lower-level algorithm class (*details*) are a member of the higher-level class