# Source, Object, Binary, Include, and Library directories
SRC_DIR  := sources
OBJ_DIR  := build\obj
LIB_DIR  := libraries
INC_DIR  := include
LIB_NAME := libarithmetic.a

# Path to the static library
LIB := $(LIB_DIR)/$(LIB_NAME)

# Find all source files in the source directory and subdirectories
SRC := $(shell dir /b /s $(SRC_DIR)\*.c)
SRC := $(subst $(SRC_DIR)\,$(SRC_DIR)/,$(SRC))  # Convert backslashes to forward slashes

# Corresponding object files in the object directory
OBJ := $(subst $(SRC_DIR)\,$(OBJ_DIR)\,$(SRC:.c=.o))

# Command to remove directories (Windows)
RMDIR := rd /s /q

# Compiler and archiver commands
CC       := gcc
AR       := ar

# Compiler flags for preprocessor, compiler, and linker
CPPFLAGS := -I$(INC_DIR) -MMD -MP  # Include directory, generate dependencies
CFLAGS   := -Wall -Werror           # Show all warnings, treat warnings as errors

# Phony targets to prevent conflicts with files of the same name
.PHONY: all clean archive

# Default target: build the archive
all: archive

# Rule to build the static library (archive)
$(LIB): $(OBJ) | $(LIB_DIR)
	$(AR) rcs $@ $^

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir $(dir $@) 2> NUL
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Rule to create necessary directories
$(OBJ_DIR) $(LIB_DIR):
	if not exist "$@" mkdir $@

# Rule to clean the build: remove object files and the static library
clean:
	@if exist $(OBJ_DIR) $(RMDIR) $(OBJ_DIR)
	@if exist $(LIB_DIR)\$(LIB_NAME) del $(LIB_DIR)\$(LIB_NAME)

# Explicit target to create the archive
archive: $(LIB)

# Include dependency files
-include $(OBJ:.o=.d)
