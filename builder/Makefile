TARGET = person

# Compiler flags
CXXFLAGS = -std=c++20

# Specify the C++ compiler
CXX = g++

# Specify the source files
SOURCES = main.cpp Person.hpp Person.cpp PersonBuilder.hpp PersonBuilder.cpp \
	PersonAddressBuilder.hpp PersonJobBuilder.hpp

# The remove command
RM = rf -f

# Build the target executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Remove object files
clean: 
	rf -f *.o