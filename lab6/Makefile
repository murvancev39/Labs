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

RMQ_N_LOGN_NAME = RMQ_N_LOGN
RMQ_LOGN_N_NAME = RMQ_LOGN_N
RSQ_FENW_NAME   = RSQ_FENW
RSQ_SEG_NAME    = RSQ_SEG_TREE

PYTHON = python3
VENV = .venv
BIN = $(VENV)/bin

ALL_TREES = $(RSQ_SEG_NAME) $(RSQ_FENW_NAME) $(RMQ_LOGN_N_NAME) $(RMQ_N_LOGN_NAME)

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

$(OBJ_FILES): include/main.h

run_rmq_n_logn: $(TARGET)
	@mkdir -p $(RES_DIR)/$(RMQ_N_LOGN_NAME)
	./$(TARGET) --$(RMQ_N_LOGN_NAME) $(RES_DIR)/$(RMQ_N_LOGN_NAME)

run_rmq_logn_n: $(TARGET)
	@mkdir -p $(RES_DIR)/$(RMQ_LOGN_N_NAME)
	./$(TARGET) --$(RMQ_LOGN_N_NAME) $(RES_DIR)/$(RMQ_LOGN_N_NAME)

run_rsq_fenw: $(TARGET)
	@mkdir -p $(RES_DIR)/$(RSQ_FENW_NAME)
	./$(TARGET) --$(RSQ_FENW_NAME) $(RES_DIR)/$(RSQ_FENW_NAME)

run_rsq_seg: $(TARGET)
	@mkdir -p $(RES_DIR)/$(RSQ_SEG_NAME)
	./$(TARGET) --RSQ_SEG $(RES_DIR)/$(RSQ_SEG_NAME)

run_all: $(TARGET)
	@for tree in $(ALL_TREES); do \
		echo "Running tests for $$tree..."; \
		mkdir -p $(RES_DIR)/$$tree; \
		if [ "$$tree" = "$(RSQ_SEG_NAME)" ]; then \
			./$(TARGET) --RSQ_SEG $(RES_DIR)/$$tree; \
		else \
			./$(TARGET) --$$tree $(RES_DIR)/$$tree; \
		fi \
	done

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(RES_DIR)

.PHONY: all clean debug release run_all run_rmq_n_logn run_rmq_logn_n run_rsq_fenw run_rsq_seg