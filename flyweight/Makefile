# Directory contains 2 independent projects
all: flyweight boostflyweight textformat

# Build the targets executables
flyweight: flyweight.cpp
	g++ -std=c++20 flyweight.cpp -o flyweight

boostflyweight: boostflyweight.cpp
	g++ -std=c++20 boostflyweight.cpp -o boostflyweight

textformat: textformat.cpp
	g++ -std=c++20 textformat.cpp -o textformat

# Remove object files
clean: 
	rf -f *.o
