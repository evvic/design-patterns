TARGET = chatroom

# Compiler flags
CXXFLAGS = -std=c++20

# Specify the C++ compiler
CXX = g++

# Specify the source files
SOURCES = main.cpp user.cpp chatroom.cpp

# The remove command
RM = rf -f

# Build the target executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

# Remove object files
clean: 
	rf -f *.o