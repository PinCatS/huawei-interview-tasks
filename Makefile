CC := g++
CFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic -Werror -Iinclude

SRC_DIRS := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build
EXEC_DIR := ./bin

.PHONY: all
all: text1 text2 text3

text1: text1.o bigint.o
	mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) -o $(EXEC_DIR)/text1 $(BUILD_DIR)/text1.o $(BUILD_DIR)/bigint.o

text1.o: $(SRC_DIRS)/text1.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIRS)/text1.cpp -o $(BUILD_DIR)/text1.o

bigint.o: $(INCLUDE_DIR)/bigint.h
	$(CC) $(CFLAGS) -c $(SRC_DIRS)/bigint.cpp -o $(BUILD_DIR)/bigint.o


text2: text2.o greatest_number.o
	mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) -o $(EXEC_DIR)/text2 $(BUILD_DIR)/text2.o $(BUILD_DIR)/greatest_number.o

text2.o: $(SRC_DIRS)/text2.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIRS)/text2.cpp -o $(BUILD_DIR)/text2.o

greatest_number.o: $(INCLUDE_DIR)/greatest_number.h
	$(CC) $(CFLAGS) -c $(SRC_DIRS)/greatest_number.cpp -o $(BUILD_DIR)/greatest_number.o


text3: text3.o linked_matrix.o dlx.o map_solver.o
	mkdir -p $(EXEC_DIR)
	$(CC) $(CFLAGS) -o $(EXEC_DIR)/text3 $(BUILD_DIR)/text3.o $(BUILD_DIR)/linked_matrix.o $(BUILD_DIR)/dlx.o $(BUILD_DIR)/map_solver.o

text3.o: $(SRC_DIRS)/text3.cpp
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIRS)/text3.cpp -o $(BUILD_DIR)/text3.o

linked_matrix.o: $(INCLUDE_DIR)/linked_matrix.h
	$(CC) $(CFLAGS) -c $(SRC_DIRS)/linked_matrix.cpp -o $(BUILD_DIR)/linked_matrix.o

dlx.o: $(INCLUDE_DIR)/dlx.h
	$(CC) $(CFLAGS) -c $(SRC_DIRS)/dlx.cpp -o $(BUILD_DIR)/dlx.o

map_solver.o: $(INCLUDE_DIR)/map_solver.h
	$(CC) $(CFLAGS) -c $(SRC_DIRS)/map_solver.cpp -o $(BUILD_DIR)/map_solver.o


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(EXEC_DIR)
