CC = gcc

INCLUDE_FLAG = -Iinclude

DEBUG_CFLAGS = -std=c11 -D_DEBUG -ggdb3 -O0 \
               -Wall -Wextra -Werror=vla \
               -Wpointer-arith -Wshadow -Wconversion

RELEASE_FLAGS = -O3 -flto -fstack-protector -fno-omit-frame-pointer -DNDEBUG

CFLAGS = $(RELEASE_FLAGS) $(INCLUDE_FLAG) 

LDFLAGS  = -fno-omit-frame-pointer -fstack-protector -fstrict-overflow -lm

SANITIZE = -fsanitize=address,leak,undefined


OBJ_DIR = obj
BIN_DIR = bin
SRC_DIR = src
RES_DIR = res
PLOT_DIR = plots
TESTS_DIR = tests
DOC_DIR = doc



PYTHON = python3
VENV_DIR     = venv
VENV_PIP     = $(VENV_DIR)/bin/pip
VENV_PYTHON  = $(VENV_DIR)/bin/python3
VENV_DONE    = $(VENV_DIR)/.venv_done


SRC_FILES  = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TESTS_DIR)/*.c)

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES)) \
            $(patsubst $(TESTS_DIR)/%.c, $(OBJ_DIR)/%.o, $(TEST_FILES))

TARGET = bin/tester.exe


$(TARGET): $(OBJ_FILES)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LDFLAGS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(RES_DIR):
	mkdir -p $(RES_DIR)

release: CFLAGS = $(RELEASE_FLAGS) $(INCLUDE_FLAG)
release: clean_obj $(TARGET)
	@echo "Release build done."

debug: CFLAGS = $(INCLUDE_FLAG) $(DEBUG_CFLAGS) $(SANITIZE)
debug: LDFLAGS += $(SANITIZE)
debug: clean_obj $(TARGET)
	@echo "Debug build done."

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

$(VENV_DONE): requirements.txt
	$(PYTHON) -m venv $(VENV_DIR)
	@echo "Installing dependencies..."
	$(VENV_PIP) install -r requirements.txt
	@touch $(VENV_DONE)

setup_venv: $(VENV_DONE)

plot: $(VENV_DONE)
	@mkdir -p $(PLOT_DIR)
	@echo "--- Plotting ---"
	$(VENV_PYTHON) plotter.py

doc:
	doxygen Doxyfile

open_doc_on_wsl:	
	@explorer.exe "$$(wslpath -w $(DOC_DIR)/html/index.html)"

open_doc_on_win:
	start "" "$(DOC_DIR)/html/index.html"


clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(RES_DIR) $(VENV_DIR) $(DOC_DIR)

clean_obj:
	rm -rf $(OBJ_DIR)

clean_plots:
	rm -rf $(PLOT_DIR)

.PHONY: all clean release debug part_1 part_2 part_3 run_part_1_3 plot clean_obj clean_plots setup_venv