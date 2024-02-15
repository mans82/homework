SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := .
BIN_NAME := bankmanager

OBJ_FILES := bank.o shapes.o trie.o main.o
OBJ := $(OBJ_FILES:%.o=$(OBJ_DIR)/%.o)

CXX := g++

$(BIN_NAME): $(OBJ)
	$(CXX) $^ -o $(BIN_DIR)/$(BIN_NAME)

objects: $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -c $? -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_NAME)