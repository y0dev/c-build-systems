# Define the main source directories containing both source and header files
SRC_DIRS := arithmetic utils

# Define output directories
BIN_DIR  := bin
OBJ_DIR  := $(BIN_DIR)/obj
LIB_NAME := libcombined.a

# Path to the static library
LIB := $(BIN_DIR)/$(LIB_NAME)

# Find all source files (.c) in the specified source directories recursively using forfiles
C_SRCS := $(foreach dir,$(SRC_DIRS),$(shell forfiles /P $(dir) /S /M *.c /C "cmd /c echo @relpath"))
C_SRCS := $(subst ",,$(C_SRCS))  # Remove quotes from paths
C_SRCS := $(subst .\,,$(C_SRCS))  # Remove leading .\ from the paths
C_SRCS := $(addprefix $(dir)/,$(C_SRCS))  # Add source directory prefix

# Corresponding object files in the object directory
OBJ := $(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(C_SRCS:.c=.o))

# Find all include directories in the source directory and subdirectories using forfiles
INC_DIRS := $(foreach dir,$(SRC_DIRS),$(shell forfiles /P $(dir) /S /M * /C "cmd /c echo @relpath"))
INC_DIRS := $(subst ",,$(INC_DIRS))
INC_DIRS := $(sort $(dir $(INC_DIRS)))
INC_DIRS := $(filter-out $(SRC_DIRS)\.git\,$(INC_DIRS))  # Exclude .git directory
INC_DIRS := $(addprefix -I,$(INC_DIRS))

# Compiler and flags
CC       := gcc
CPPFLAGS := $(INC_DIRS) -MMD -MP  # Include directories and generate dependency files
CFLAGS   := -Wall -Werror

# Phony targets to prevent conflicts with files of the same name
.PHONY: all clean archive echoes

# Default target: build the archive
all: archive

# Rule to build the static library (archive)
$(LIB): $(OBJ)
	$(AR) rcs $@ $^

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Rule to create necessary directories
$(OBJ_DIR):
	@if not exist "$@" mkdir $@

# Rule to clean the build: remove object files and the static library
clean:
	@if exist $(BIN_DIR) rd /s /q $(BIN_DIR)
	@if exist $(OBJ_DIR) rd /s /q $(OBJ_DIR)

# Explicit target to create the archive
archive: $(LIB)

# Optional target to print out information for debugging
echoes:
	@echo "Include Directories: $(INC_DIRS)"
	@echo "Source Directories: $(SRC_DIRS)"
	@echo "Source Files: $(C_SRCS)"
	@echo "Object Directories: $(OBJ_DIR)"
	@echo "Object files: $(OBJ)"

# Include dependency files
-include $(OBJ:.o=.d)
