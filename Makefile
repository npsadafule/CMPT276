# Define the compiler
CXX = g++

# Define the target executable names
MAIN_TARGET = main
TEST_TARGET = unitTest

# Define the source files
MAIN_SRC = main.cpp Product.cpp ChangeRequest.cpp Report.cpp User.cpp
TEST_SRC = unitTestMain.cpp Product.cpp ChangeRequest.cpp Report.cpp User.cpp

# Define the object files
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Define compiler flags
CXXFLAGS = -Wall -std=c++17

# Default target
all: $(MAIN_TARGET) $(TEST_TARGET)

# Rule to build the main target executable
$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build the test target executable
$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f $(MAIN_OBJ) $(TEST_OBJ) $(MAIN_TARGET) $(TEST_TARGET)

# Rule to run the main program
run_main: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Rule to run the test program
run_test: $(TEST_TARGET)
	./$(TEST_TARGET)
