CC = gcc


CFLAGS 

INCLUDE_FLAG = -Iinclude

DEBUG_CFLAGS = -std=c11 -D _DEBUG -ggdb3 -O0 -pie -fPIE \
           -Wall -Wextra -Waggressive-loop-optimizations \
           -Wmissing-declarations -Wcast-align -Wcast-qual \
           -Wchar-subscripts -Wconditionally-supported -Wconversion \
           -Wempty-body -Wfloat-equal -Wformat-nonliteral \
           -Wformat-security -Wformat-signedness -Wformat=2 -Winline \
           -Wlogical-op -Wopenmp-simd \
           -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow \
           -Wsign-conversion -Wstrict-overflow=2 \
           -Wsuggest-attribute=noreturn \
           -Wswitch-default -Wswitch-enum -Wsync-nand \
           -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros \
           -Wstack-protector -Werror=vla -Wlarger-than=8192 -Wstack-usage=8192 \
           -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing \
           -Wno-varargs

RELEASE_FLAGS = -O3 -flto -fstack-protector -fno-omit-frame-pointer -DNDEBUG

CFLAGS = $(RELEASE_FLAGS) $(INCLUDE_FLAG) 

LDFLAGS  = -flto-odr-type-merging -fno-omit-frame-pointer -fcheck-new \
           -fsized-deallocation -fstack-protector -fstrict-overflow

SANITIZE = -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,\
			float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,\
			null,object-size,return,returns-nonnull-attribute,shift,\
			signed-integer-overflow,undefined,unreachable,vla-bound,vptr


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


$(TARGET): $(OBJ_FILES)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(RES_DIR):
	mkdir -p $(RES_DIR)

--release: CFLAGS = $(RELEASE_FLAGS) $(INCLUDE_FLAG)
--release: clean_obj $(TARGET)
	@echo "Release build done."

--debug: CFLAGS = $(INCLUDE_FLAG) $(DEBUG_CFLAGS) $(SANITIZE) $(LDFLAGS)
--debug: clean_obj $(TARGET)
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

plot: $(RES_DIR)
	python plotter.py

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(RES_DIR) $(PLOT_DIR)

clean_obj:
	rm -rf $(OBJ_DIR)

.PHONY: all clean