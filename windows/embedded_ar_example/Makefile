# Source, Object, Binary, Include, and Library directories
SRC_DIR  := sources
BIN_DIR	 := bin
OBJ_DIR  := $(BIN_DIR)\obj
REL_INC_DIR := include

# Convert the relative include directory to an absolute path
INC_DIR := $(realpath $(REL_INC_DIR))
LIB_NAME := libarithmetic.a

# Path to the static library
LIB := $(BIN_DIR)/$(LIB_NAME)

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

# Compiler and archiver commands for MicroBlaze
CC       := mb-gcc
AR       := mb-ar
CPPFLAGS := -I$(INC_DIR) $(INC_DIRS) -MMD -MP  # Include directory, generate dependencies

# Compiler flags for MicroBlaze
CFLAGS   := -Wall -Werror -mcpu=v11.0 -mxl-mode -meb -fmessage-length=0

# -mcpu=v11.0: Specifies the MicroBlaze CPU version.
# -mxl-mode: Enables MicroBlaze extended mode instructions.
# -meb: Sets the endianness to big-endian. Use `-mel` for little-endian.
# -fmessage-length=0: Do not wrap diagnostic messages, useful for environments with limited screen width.


# Linker flags (not needed for archiving, but kept for reference)
LDFLAGS  :=

# Phony targets to prevent conflicts with files of the same name
.PHONY: all clean archive echoes

# Default target: build the archive
all: archive

# Rule to build the static library (archive)
$(LIB): $(OBJ)
	$(AR) rcs $@ $^

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Rule to create necessary directories
$(OBJ_DIR):
	@if not exist "$@" mkdir $@

# Rule to clean the build: remove object files and the static library
clean:
	@if exist $(BIN_DIR) $(RMDIR) $(BIN_DIR)
	@if exist $(OBJ_DIR) $(RMDIR) $(OBJ_DIR)

# Explicit target to create the archive
archive: $(LIB)

echoes:
	@echo "Include Directories: $(INC_DIRS) -I$(INC_DIR)"
	@echo "Source Directories: $(SRC_DIR)"
	@echo "Source Files: $(C_SRCS)"
	@echo "Object Directories: $(OBJ_DIR)"
	@echo "Object files: $(OBJ)"

# Include dependency files
-include $(OBJ:.o=.d)
