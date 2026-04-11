.PHONY: all run plot clean

TARGET = tester

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC_DIR = src
OBJ_DIR = obj
RES_DIR = res
PLT_DIR = plots
BIN_DIR = bin

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECT_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECT_FILES)
	$(CC) $(OBJECT_FILES) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


run: $(TARGET)
	mkdir -p $(RES_DIR)/arr $(RES_DIR)/list
	(cd $(RES_DIR)/arr && ../../$(TARGET) -A)
	(cd $(RES_DIR)/list && ../../$(TARGET) -L)

plot: run
	mkdir -p $(PLT_DIR)
	python3 laba.py

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	rm -rf $(RES_DIR)/*.txt
	rm -rf $(PLT_DIR)/*.png
