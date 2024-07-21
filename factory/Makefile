# Do not include .h/.hpp files in the list of source files to complile
# The compiler will automatically include them when compiling main.cpp.
# This avoids the "#pragma once in main file" warning and ensures proper compilation.

# ^ But because the .hpp files include definitions (not just function declarations),
# they need to be included for make to track changes and recompile them

# Build the target executable
hotdrink: main.cpp HotDrink.hpp HotDrinkFactory.hpp
	g++ -std=c++20 main.cpp HotDrink.hpp HotDrinkFactory.hpp -o hotdrink

# Remove object files
clean: 
	rf -f *.o
