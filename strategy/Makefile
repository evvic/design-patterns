all: dynamic static

dynamic: dynamic-list.cpp list-strategy.cpp
	g++ -std=c++20 dynamic-list.cpp list-strategy.cpp -o dynamic-list

static: static-list.cpp list-strategy.cpp
	g++ -std=c++20 static-list.cpp list-strategy.cpp -o static-list

# Remove object files
clean: 
	rf -f *.o
