CC = gcc
CFLAGS = -Wextra -Wunused-result -O3 -Iinclude
# я вырубил -Wall так как он срабатывал на безопасном sprintf в тестере и выдавал варнинг, что может произойти переполнение, которого там быть не может
PYTHON = python
VENV_DIR = venv
VENV_PYTHON = $(VENV_DIR)/Scripts/python.exe
VENV_PIP = $(VENV_DIR)/Scripts/pip.exe
VENV_DONE = $(VENV_DIR)/.venv_done

SRC_DIR = src

SRC_GEN_SUBDIR = $(SRC_DIR)/gen
SRC_PARTS_SUBDIR = $(SRC_DIR)/parts
SRC_SORTS_SUBDIR = $(SRC_DIR)/sorts
SRC_TEST_SUBDIR = $(SRC_DIR)/test
SRC_DIR_SUBFOLDERS = $(SRC_GEN_SUBDIR) $(SRC_PARTS_SUBDIR) $(SRC_SORTS_SUBDIR) $(SRC_TEST_SUBDIR)

TEST_SUBDIR = test

OBJ_DIR = obj
BIN_DIR = bin
SCRIPTS_DIR = scripts

TEST_FILES_DIR = test_files

TIME_DIR = time_res


PARTS_FLAGS = part_1 part_2 part_3 part_4 part_5 part_10

RUN_TARGETS = $(addprefix run_,$(PARTS_FLAGS))
 

SORTS_SRC = $(wildcard $(SRC_SORTS_SUBDIR)/*.c)
PARTS_SRC = $(wildcard $(SRC_PARTS_SUBDIR)/*.c)
TEST_SRC  = $(wildcard $(SRC_TEST_SUBDIR)/*.c)
GEN_SRC   = $(wildcard $(SRC_GEN_SUBDIR)/*.c)

GEN_OBJ = $(GEN_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_OBJ = $(TEST_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SORTS_OBJ = $(SORTS_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
PARTS_OBJ = $(PARTS_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


SMALL_TESTS_DIR    = $(TEST_FILES_DIR)/small_tests
BIG_TESTS_DIR  	   = $(TEST_FILES_DIR)/big_tests
MOST_DUB_TESTS_DIR = $(TEST_FILES_DIR)/most_dub_tests

TEST_FILES_SUBDIRS = $(SMALL_TESTS_DIR) $(BIG_TESTS_DIR) $(MOST_DUB_TESTS_DIR)


GEN_TARGETS = $(GEN_SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.exe)

PARTS_TARGET = $(PARTS_SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.exe)


# ===========================================================================
# TARGETS:
# =========================================================================== 


all: $(GEN_TARGETS) $(PARTS_TARGET)


$(GEN_TARGETS): $(BIN_DIR)/%.exe: $(OBJ_DIR)/%.o
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@


$(PARTS_TARGET): $(SORTS_OBJ) $(TEST_OBJ) $(PARTS_OBJ)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -o $@
	

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

gen_tests: $(GEN_TARGETS)
	chmod +x $(SCRIPTS_DIR)/all_tests_generate.sh $(SCRIPTS_DIR)/test_gen.sh
	sh ./$(SCRIPTS_DIR)/all_tests_generate.sh $(BIN_DIR)/gen $(SCRIPTS_DIR) $(TEST_FILES_DIR)

$(RUN_TARGETS): run_%: $(PARTS_TARGET)
	@mkdir -p $(TIME_DIR)/$*
	@./$(PARTS_TARGET) $(TEST_FILES_DIR) $(TIME_DIR) --$* || \
	(\
		EXIT_CODE=$$?;\
		echo -e "\n\033[1;31m[CRITICAL ERROR]\033[0m [Part - $$EXIT_CODE] - FAILED";\
		exit $$EXIT_CODE;\
	)

run_all: $(RUN_TARGETS)

# ===========================================================================
# PYTHON VENV TARGETS
# ===========================================================================

$(VENV_DONE): requirements.txt
	$(PYTHON) -m venv $(VENV_DIR)
	@echo "Installing dependencies..."
	$(VENV_PIP) install -r requirements.txt
	@touch $(VENV_DONE)

setup_venv: $(VENV_DONE)

plot: $(VENV_DONE)
	@echo "Running plotter in venv..."
	$(VENV_PYTHON) plotter.py

# ===========================================================================
# CLEAN TARGETS
# ===========================================================================


clean_plot:
	rm -rf plots

clean_venv:
	rm -rf $(VENV_DIR)

clean_ob:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

clean_res:
	rm -rf $(TIME_DIR)

clean_tests:
	rm -rf $(TEST_FILES_DIR)

clean_all: clean_ob clean_res clean_tests clean_venv

