all: dynamic static

dynamic: dynamic-list.cpp
	g++ -std=c++20 dynamic-list.cpp -o dynamic-list

static: static-list.cpp
	g++ -std=c++20 static-list.cpp -o static-list

# Remove object files
clean: 
	rf -f *.o
