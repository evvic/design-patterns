# Directory contains 2 independent projects
all: flyweight boostflyweight

# Build the target executable
flyweight: flyweight.cpp
	g++ -std=c++20 flyweight.cpp -o flyweight

boostflyweight: boostflyweight.cpp
	g++ -std=c++20 boostflyweight.cpp -o boostflyweight

# Remove object files
clean: 
	rf -f *.o
