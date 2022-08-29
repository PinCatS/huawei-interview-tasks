CC := g++
CFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic -Werror -Iinclude

SRC_DIR := ./src
INCLUDE_DIR := ./include
OBJ_DIR := ./obj
EXEC_DIR := ./bin
INPUT_DATA_DIR := ./data

.PHONY: all
all: text1 text2 text3 run

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

.PHONY: run
run:
	@echo "Run all tasks..."
	@echo "*******************************"
	@echo "Big inetger addition (text1)"
	@echo "-------------------------------"
	@$(EXEC_DIR)/text1 < $(INPUT_DATA_DIR)/text1_input.txt
	@echo "*******************************"
	@echo "Greatest Number (text2)"
	@echo "-------------------------------"
	@$(EXEC_DIR)/text2 < $(INPUT_DATA_DIR)/text2_input.txt
	@echo "*******************************"
	@echo "Find Map pieces (text3)"
	@echo "-------------------------------"
	@$(EXEC_DIR)/text3 < $(INPUT_DATA_DIR)/text3_input.txt
	@echo "*******************************"

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(EXEC_DIR)
