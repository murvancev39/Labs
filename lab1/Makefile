.PHONY: all run plot clean doc

TARGET = tester
UNIT_TEST_TARGET = test

CC = gcc
CFLAGS = -O3 -Wall -Wextra -Iinclude

TEST_CFLAGS = -g -O1 -Wall -Wextra -Iinclude -fsanitize=address -fsanitize=undefined


SRC_DIR = src
OBJ_DIR = obj
RES_DIR = res
PLT_DIR = plot
BIN_DIR = bin
DOC_DIR = doc

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECT_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

ALL_C_FILES = $(wildcard $(SRC_DIR)/*.c)
SOURCES = $(filter-out $(SRC_DIR)/tester.c $(SRC_DIR)/test.c, $(ALL_C_FILES))

all: $(TARGET) $(UNIT_TEST_TARGET)

unit_tests: $(UNIT_TEST_TARGET)

$(UNIT_TEST_TARGET): 
	@mkdir -p $(BIN_DIR)
	$(CC) $(TEST_CFLAGS)  $(SOURCES) $(SRC_DIR)/$(UNIT_TEST_TARGET).c -o $(BIN_DIR)/$(UNIT_TEST_TARGET)

$(TARGET):
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SOURCES) $(SRC_DIR)/$(TARGET).c -o $(BIN_DIR)/$(TARGET)

run_tester: $(TARGET)
	mkdir -p $(RES_DIR)/arr $(RES_DIR)/list
	(cd $(RES_DIR)/arr && ../../$(BIN_DIR)/$(TARGET) -A)
	(cd $(RES_DIR)/list && ../../$(BIN_DIR)/$(TARGET) -L)

run_unit_tests: $(UNIT_TEST_TARGET)
	./$(BIN_DIR)/$(UNIT_TEST_TARGET)

plot:
	python3 laba.py
doc:
	doxygen Doxyfile

open_doc_on_wsl:	
	@explorer.exe "$$(wslpath -w $(DOC_DIR)/html/index.html)"

open_doc_on_win:
	start "" "$(DOC_DIR)/html/index.html"

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	rm -rf $(RES_DIR)
	rm -rf $(DOC_DIR)

clean_plots:
	rm -rf $(PLT_DIR)

.PHONY: all run plot clean doc unit_tests run_tester run_unit_tests open_doc_on_wsl open_doc_on_win $(UNIT_TEST_TARGET) $(TARGET)