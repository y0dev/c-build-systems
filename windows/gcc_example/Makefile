SRC_DIR  := sources
BIN_DIR	 := bin
OBJ_DIR  := $(BIN_DIR)\obj
REL_INC_DIR := include

LIB_DIR  := libraries
EXE_NAME := helloworld.exe

# Path to the elf
EXE := $(BIN_DIR)/$(EXE_NAME)

# Find all source files in the source directory and subdirectories
C_SRCS := $(shell forfiles /P $(SRC_DIR) /S /M *.c /C "cmd /c echo @relpath")
C_SRCS := $(subst ",,$(C_SRCS))	# Remove quotes from path
C_SRCS := $(subst .\,$(SRC_DIR)/,$(C_SRCS))	# Replace .\ to source directory path

# Corresponding object files in the object directory
OBJ := $(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(C_SRCS:.c=.o))

# Find all include directories in the source directory and subdirectories
INC_DIRS := $(shell cd $(INC_DIR) && dir /s /b /ad 2> NUL)
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


# Linker flags
LDFLAGS  := -L$(LIB_DIR)
LDLIBS   := -lm -static $(patsubst $(LIB_DIR)\lib*.a, -l$(LIB_DIR)\*, $(wildcard $(LIB_DIR)/lib*.a))

# Phony targets to prevent conflicts with files of the same name
.PHONY: all clean

# Default target: build the archive
all: $(EXE)

# Rule to build the binary
$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Rule to create necessary directories
$(OBJ_DIR):
	@if not exist "$@" mkdir $@

# Rule to clean the build: remove object files and the binaries
clean:
	@if exist $(BIN_DIR) $(RMDIR) $(BIN_DIR)
	@if exist $(OBJ_DIR) $(RMDIR) $(OBJ_DIR)

echoes:
	@echo "Include Directories: $(INC_DIRS) -I$(INC_DIR)"
	@echo "Source Directories: $(SRC_DIR)"
	@echo "Source Files: $(C_SRCS)"
	@echo "Object Directories: $(OBJ_DIR)"
	@echo "Object files: $(OBJ)"

# Include dependency files
-include $(OBJ:.o=.d)
