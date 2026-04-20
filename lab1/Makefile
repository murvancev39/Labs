.PHONY: all run plot clean doc

TARGET = tester

CC = gcc
CFLAGS = -O3 -Wall -Wextra -Iinclude

SRC_DIR = src
OBJ_DIR = obj
RES_DIR = res
PLT_DIR = plot
BIN_DIR = bin
DOC_DIR = doc

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
	rm -f $(TARGET)

plot:
	python laba.py

doc:
	"doxygen" Doxyfile
	start "" "$(DOC_DIR)/html/index.html"

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	rm -rf $(RES_DIR)/*/*.txt
	rm -rf $(RES_DIR)/*
	rm -rf $(RES_DIR)
	rm -rf $(PLT_DIR)/*.png
	rm -rf $(PLT_DIR)
	rm -rf $(DOC_DIR)/*/*
	rm -rf $(DOC_DIR)/*
	rm -rf $(DOC_DIR)
