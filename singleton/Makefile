# Directory contains 2 independent projects
all: singletondb multiton

# Build the target executable
singletondb: singletondb.cpp
	g++ -std=c++20 singletondb.cpp -o singletondb

multiton: multiton.cpp
	g++ -std=c++20 multiton.cpp -o multiton

# Remove object files
clean: 
	rf -f *.o
