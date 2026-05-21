# ----------------------------
# FLAGS
# ----------------------------

MODE ?= debug

INCLUDE_FLAG = -Iinclude

RELEASE_CFLAGS = -std=c11 -O3 -march=native -flto -DNDEBUG \
                 -Wall -Wextra -fomit-frame-pointer

RELEASE_LDFLAGS = -flto -s

DB_CFLAGS = -std=c11 -ggdb3 -O3 \
         -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-align \
         -Wformat=2 -Wunreachable-code -Wstack-usage=8192 \
         -fno-omit-frame-pointer -fstack-protector

SANITIZE = -fsanitize=address,undefined,leak

ifeq ($(MODE), release)
    CFLAGS  = $(INCLUDE_FLAG) $(RELEASE_CFLAGS)
    LDFLAGS = $(RELEASE_LDFLAGS)
else
    CFLAGS  = $(INCLUDE_FLAG) $(DB_CFLAGS) $(SANITIZE)
    LDFLAGS = $(SANITIZE)
endif

# ----------------------------
# DIRS AND FILES
# ----------------------------


CC = gcc
OBJ_DIR = obj
BIN_DIR = bin
SRC_DIR = src
RES_DIR = res
PLOT_DIR = plots
DOC_DIR = doc

AVL_NAME      = AVL
B_NAME        = B
RB_NAME       = RB
CRT_NAME      = CRT
SPL_NAME      = SPL
SKIP_NAME     = SKIP
BST_RAND_NAME = BST_RAND
BST_SORT_NAME = BST_SORT

PYTHON = python3
VENV = .venv
BIN = $(VENV)/bin

ALL_TREES = $(AVL_NAME) $(B_NAME) $(RB_NAME) $(CRT_NAME) $(SPL_NAME) $(SKIP_NAME) $(BST_RAND_NAME) $(BST_SORT_NAME)

SRC_FILES = $(shell find $(SRC_DIR) -name "*.c")

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

TARGET = $(BIN_DIR)/main.exe

# ----------------------------
# TARGETS
# ----------------------------

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(TARGET) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS)  -c $< -o $@

run_avl: $(TARGET)
	@mkdir -p $(RES_DIR)/$(AVL_NAME)
	./$(TARGET) --$(AVL_NAME) $(RES_DIR)/$(AVL_NAME)

run_b: $(TARGET)
	@mkdir -p $(RES_DIR)/$(B_NAME)
	./$(TARGET) --$(B_NAME) $(RES_DIR)/$(B_NAME)

run_rb: $(TARGET)
	@mkdir -p $(RES_DIR)/$(RB_NAME)
	./$(TARGET) --$(RB_NAME) $(RES_DIR)/$(RB_NAME)

run_crt: $(TARGET)
	@mkdir -p $(RES_DIR)/$(CRT_NAME)
	./$(TARGET) --$(CRT_NAME) $(RES_DIR)/$(CRT_NAME)

run_spl: $(TARGET)
	@mkdir -p $(RES_DIR)/$(SPL_NAME)
	./$(TARGET) --$(SPL_NAME) $(RES_DIR)/$(SPL_NAME)

run_skip: $(TARGET)
	@mkdir -p $(RES_DIR)/$(SKIP_NAME)
	./$(TARGET) --$(SKIP_NAME) $(RES_DIR)/$(SKIP_NAME)

run_bst_rand: $(TARGET)
	@mkdir -p $(RES_DIR)/$(BST_RAND_NAME)
	./$(TARGET) --$(BST_RAND_NAME) $(RES_DIR)/$(BST_RAND_NAME)

run_bst_sort: $(TARGET)
	@mkdir -p $(RES_DIR)/$(BST_SORT_NAME)
	./$(TARGET) --$(BST_SORT_NAME) $(RES_DIR)/$(BST_SORT_NAME)

run_all: $(TARGET)
	@for tree in $(ALL_TREES); do \
		echo "Running tests for $$tree..."; \
		mkdir -p $(RES_DIR)/$$tree; \
		./$(TARGET) --$$tree $(RES_DIR)/$$tree; \
	done

plots: $(VENV)/bin/activate
	@echo "Рисую графики..."
	@$(BIN)/python3 plotter.py

$(VENV)/bin/activate:
	@echo "--- Подготовка окружения ---"
	@$(PYTHON) -m venv $(VENV)
	@$(BIN)/pip install --upgrade pip
	@$(BIN)/pip install matplotlib numpy
	@touch $(VENV)/bin/activate

doc:
	doxygen Doxyfile

open_doc_on_wsl:	
	@explorer.exe "$$(wslpath -w $(DOC_DIR)/html/index.html)"

open_doc_on_win:
	start "" "$(DOC_DIR)/html/index.html"


clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(RES_DIR) $(DOC_DIR)

clean_plots:
	rm -rf $(PLOT_DIR)

clean_venv:
	rm -rf $(VENV)
.PHONY: all clean debug release run_all run_avl run_b run_rb run_crt run_spl run_skip run_bst_rand run_bst_sort