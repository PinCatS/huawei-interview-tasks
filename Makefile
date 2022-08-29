CC := g++
CFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic -Werror -Iinclude

SRC_DIR := ./src
INCLUDE_DIR := ./include
OBJ_DIR := ./obj
EXEC_DIR := ./bin

.PHONY: all
all: text1 text2 text3

text1: $(OBJ_DIR)/text1.o $(OBJ_DIR)/bigint.o
	mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) -o $(EXEC_DIR)/text1 $(OBJ_DIR)/text1.o $(OBJ_DIR)/bigint.o

text2: $(OBJ_DIR)/text2.o $(OBJ_DIR)/greatest_number.o
	mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) -o $(EXEC_DIR)/text2 $(OBJ_DIR)/text2.o $(OBJ_DIR)/greatest_number.o

text3: $(OBJ_DIR)/text3.o $(OBJ_DIR)/linked_matrix.o $(OBJ_DIR)/dlx.o $(OBJ_DIR)/map_solver.o
	mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) -o $(EXEC_DIR)/text3 $(OBJ_DIR)/text3.o $(OBJ_DIR)/linked_matrix.o $(OBJ_DIR)/dlx.o $(OBJ_DIR)/map_solver.o

# Building obkects for C++ source
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(EXEC_DIR)
