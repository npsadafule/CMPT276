# Define the compiler
CXX = g++

# Define the target executable name
TARGET = IssueTrackingSystem

# Define the source files
SRC = IssueTrackingSystem.cpp

# Define the object files
OBJ = $(SRC:.cpp=.o)

# Define compiler flags
CXXFLAGS = -Wall -std=c++17

# Default target
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f $(OBJ) $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)
