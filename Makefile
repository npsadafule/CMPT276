# Define the compiler
CXX = g++

# Define the compiler flags
CXXFLAGS = -Wall -std=c++17

# Define the target executables
TARGET_MAIN = main
TARGET_TEST = unitTest

# Define the source files
SRC_MAIN = main.cpp Product.cpp ChangeRequest.cpp Report.cpp User.cpp UserInterface.cpp ProcessCoordinator.cpp
SRC_TEST = unitTestMain.cpp Product.cpp ChangeRequest.cpp Report.cpp User.cpp UserInterface.cpp ProcessCoordinator.cpp

# Define the object files
OBJ_MAIN = $(SRC_MAIN:.cpp=.o)
OBJ_TEST = $(SRC_TEST:.cpp=.o)

# Default target
all: $(TARGET_MAIN) $(TARGET_TEST)

# Rule to build the main executable
$(TARGET_MAIN): $(OBJ_MAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build the test executable
$(TARGET_TEST): $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f $(OBJ_MAIN) $(OBJ_TEST) $(TARGET_MAIN) $(TARGET_TEST) 

# Rule to run the main program
run: $(TARGET_MAIN)
	./$(TARGET_MAIN)

# Rule to run the test program
run_test: $(TARGET_TEST)
	./$(TARGET_TEST)
