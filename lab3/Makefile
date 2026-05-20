.PHONY: all clean run_logs run_simple run_dense run_sparse plot

CC = gcc
CFLAGS = -I./include -Wall -Wextra -O2
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LOG_DIR = log
PLT_DIR = plt


TESTS = bin_insertion_testing bin_linear_testing\
		binom_testing fib_testing\
		dijkstra_bin_testing dijkstra_binom_testing dijkstra_fib_testing

SIMPLE_TESTS = bin_insertion_testing bin_linear_testing binom_testing fib_testing

DIJKSTRA_TESTS = dijkstra_bin_testing dijkstra_binom_testing dijkstra_fib_testing

TARGETS = $(patsubst %,$(BIN_DIR)/%.exe,$(TESTS))

SIMPLE_LOGS = $(patsubst %,$(LOG_DIR)/%.log,$(SIMPLE_TESTS))
DIJKSTRA_DENSE_LOGS = $(patsubst %,$(LOG_DIR)/%_DENSE.log,$(DIJKSTRA_TESTS))
DIJKSTRA_SPARSE_LOGS = $(patsubst %,$(LOG_DIR)/%_SPARSE.log,$(DIJKSTRA_TESTS))


all: $(BIN_DIR) $(OBJ_DIR) $(TARGETS)


$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@


$(BIN_DIR)/bin_insertion_testing.exe: $(OBJ_DIR)/bin_insertion_testing.o $(OBJ_DIR)/bin_heap.o
	$(CC) $^ -o $@

$(BIN_DIR)/bin_linear_testing.exe: $(OBJ_DIR)/bin_linear_testing.o $(OBJ_DIR)/bin_heap.o
	$(CC) $^ -o $@

$(BIN_DIR)/binom_testing.exe: $(OBJ_DIR)/binom_testing.o $(OBJ_DIR)/binom_heap.o
	$(CC) $^ -o $@

$(BIN_DIR)/fib_testing.exe: $(OBJ_DIR)/fib_testing.o $(OBJ_DIR)/fib_heap.o
	$(CC) $^ -o $@

$(BIN_DIR)/dijkstra_bin_testing.exe: $(OBJ_DIR)/dijkstra_bin_testing.o $(OBJ_DIR)/dijkstra_bin.o $(OBJ_DIR)/graphs.o
	$(CC) $^ -o $@

$(BIN_DIR)/dijkstra_binom_testing.exe: $(OBJ_DIR)/dijkstra_binom_testing.o $(OBJ_DIR)/dijkstra_binom.o $(OBJ_DIR)/graphs.o
	$(CC) $^ -o $@

$(BIN_DIR)/dijkstra_fib_testing.exe: $(OBJ_DIR)/dijkstra_fib_testing.o $(OBJ_DIR)/fib_heap.o $(OBJ_DIR)/graphs.o
	$(CC) $^ -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/tests/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/heaps/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/dijkstra/%.c
	$(CC) $(CFLAGS) -c $< -o $@



run_dense: $(DIJKSTRA_DENSE_LOGS)

$(LOG_DIR)/%_DENSE.log: $(BIN_DIR)/%.exe
	@mkdir -p $(LOG_DIR)
	@echo "Running  $* (dense mode)"
	-./$< "-D" > $@

run_sparse: $(DIJKSTRA_SPARSE_LOGS)

$(LOG_DIR)/%_SPARSE.log: $(BIN_DIR)/%.exe
	@mkdir -p $(LOG_DIR)
	@echo "Running  $* (sparse mode)"
	-./$< "-S" > $@

run_simple: $(SIMPLE_LOGS)

$(LOG_DIR)/%.log: $(BIN_DIR)/%.exe
	@mkdir -p $(LOG_DIR)
	@echo "Running simple test $*..."
	-./$< > $@

run_logs: run_dense run_sparse run_simple

plot: all
	@mkdir -p $(PLT_DIR)
	@echo "--- Plotting ---"
	python3 plotter.py


clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(PLT_DIR) $(LOG_DIR)