SRC_DIR  := sources
OBJ_DIR  := build\obj
BIN_DIR  := build
REL_INC_DIR := include

LIB_DIR  := libraries
EXE_NAME := helloworld.exe

# Path to the elf
EXE := $(BIN_DIR)/$(EXE_NAME)

# Find all source files in the source directory and subdirectories
SRC := $(shell dir /b /s $(SRC_DIR)\*.c)
SRC := $(subst $(SRC_DIR)\,$(SRC_DIR)/,$(SRC))  # Convert backslashes to forward slashes

# Corresponding object files in the object directory
OBJ := $(subst $(SRC_DIR)\,$(OBJ_DIR)\,$(SRC:.c=.o))


# Find all include directories in the source directory and subdirectories
INC_DIRS := $(shell cd $(INC_DIR) && dir /s /b /ad)
INC_DIRS := $(sort $(INC_DIRS))  # Remove duplicates
INC_DIRS := $(subst \,/,$(INC_DIRS))  # Convert backslashes to forward slashes
INC_DIRS := $(addprefix -I,$(INC_DIRS))

# Command to remove directories (Windows)
RMDIR := rd /s /q

# Compiler and archiver commands
CC       := gcc

CPPFLAGS := -I$(INC_DIR) $(INC_DIRS) -MMD -MP  # Include directory, generate dependencies

# Compiler flags for preprocessor, compiler, and linker
CFLAGS   := -Wall -Werror           # Show all warnings, treat warnings as errors


LDFLAGS  := -L$(LIB_DIR)
LDLIBS   := -lm -static $(patsubst $(LIB_DIR)\lib*.a, -l$(LIB_DIR)\*, $(wildcard $(LIB_DIR)/lib*.a))

# Phony targets to prevent conflicts with files of the same name
.PHONY: all clean

# Default target: build the archive
all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir $(dir $@) 2> NUL
	@echo "$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Rule to create necessary directories
$(BIN_DIR) $(OBJ_DIR):
	if not exist "$@" mkdir $@

# Rule to clean the build: remove object files and the binaries
clean:
	@if exist $(BIN_DIR) $(RMDIR) $(BIN_DIR)
	@if exist $(OBJ_DIR) $(RMDIR) $(OBJ_DIR)

# Include dependency files
-include $(OBJ:.o=.d)
