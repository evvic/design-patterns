# Define the C++ compiler
CXX = g++

# Define C++ flags (feel free to customize these)
CXXFLAGS = -Wall -g

# Target for building the executable
all: 1-srp

# Rule to compile the C++ file
1-srp: 1-srp.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile a single C++ file into object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Rule to clean up object files and executables
clean:
	rm -f *.o 1-srp

