# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
DEBUGFLAGS := -g -DDEBUG
RELEASEFLAGS := -O2

# Directories
SRC_DIR  := src
OBJ_DIR  := obj
BIN_DIR  := bin

# Target executable
TARGET   := $(BIN_DIR)/app

# Source and object files
SRCS     := $(wildcard $(SRC_DIR)/*.cpp)
OBJS     := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
.PHONY: all
all: $(TARGET)

# Link
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories if missing
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Debug build
.PHONY: debug
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(TARGET)

# Release build
.PHONY: release
release: CXXFLAGS += $(RELEASEFLAGS)
release: $(TARGET)

# Run the app
.PHONY: run
run: all
	./$(TARGET)

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
