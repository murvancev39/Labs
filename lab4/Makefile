CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
OBJ_DIR = obj
BIN_DIR = bin
SRC_DIR = src
RES_DIR = res
PLOT_DIR = plots
TESTS_DIR = tests

SRC_FILES  = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TESTS_DIR)/*.c)

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES)) \
            $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_FILES))

TARGET = bin/tester.exe

# all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@mkdir -p bin
# 	@echo pobeda
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(RES_DIR):
	mkdir -p $(RES_DIR)


part_1: $(TARGET)
	mkdir -p $(RES_DIR)
	./$(TARGET) -U > $(RES_DIR)/results_unsigned.txt

part_2: $(TARGET)
	mkdir -p $(RES_DIR)
	./$(TARGET) -F > $(RES_DIR)/results_float.txt

part_3: $(TARGET)
	mkdir -p $(RES_DIR)
	./$(TARGET) -S > $(RES_DIR)/results_string.txt

run_part_1_3: $(TARGET)
	mkdir -p $(RES_DIR)
	./$(TARGET) -U > $(RES_DIR)/results_unsigned.txt
	./$(TARGET) -F > $(RES_DIR)/results_float.txt
	./$(TARGET) -S > $(RES_DIR)/results_string.txt

plot: $(RES_DIR)
	python plotter.py

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(RES_DIR) $(PLOT_DIR)


.PHONY: all clean