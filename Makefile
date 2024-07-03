# ============================================
# Module Name: Makefile
# Version History:
# Rev. 1 - 2024/07/01 - Neel Sadafule
# ============================================

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include

# Source files
MAIN_SRC_FILES = $(filter-out $(SRC_DIR)/unitTestMain.cpp, $(wildcard $(SRC_DIR)/*.cpp))
TEST_SRC_FILES = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))

# Object files
MAIN_OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(MAIN_SRC_FILES))
TEST_OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SRC_FILES))

# Executables
MAIN_EXEC = $(BIN_DIR)/ITS
TEST_EXEC = $(BIN_DIR)/unitTests

# Default target
all: $(MAIN_EXEC) $(TEST_EXEC)

# Link the main executable
$(MAIN_EXEC): $(MAIN_OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Link the test executable
$(TEST_EXEC): $(TEST_OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile the source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Run the main executable
run: $(MAIN_EXEC)
	./$(MAIN_EXEC)

# Run the unit tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

.PHONY: all clean run test
