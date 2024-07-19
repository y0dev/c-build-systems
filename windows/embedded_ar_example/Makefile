# Source, Object, Binary, Include, and Library directories
SRC_DIR  := sources
OBJ_DIR  := build\obj
LIB_DIR  := libraries
REL_INC_DIR := include

# Convert the relative include directory to an absolute path
INC_DIR := $(realpath $(REL_INC_DIR))
LIB_NAME := libarithmetic.a

# Path to the static library
LIB := $(LIB_DIR)/$(LIB_NAME)

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

# Compiler and archiver commands for MicroBlaze
CC       := mb-gcc
AR       := mb-ar
CPPFLAGS := -I$(INC_DIR) -MMD -MP

# Compiler flags for MicroBlaze
CFLAGS   := -Wall -Werror -mcpu=v11.0 -mxl-mode -meb

# -mcpu=v11.0: Specifies the MicroBlaze CPU version.
# -mxl-mode: Enables MicroBlaze extended mode instructions.
# -meb: Sets the endianness to big-endian. Use `-mel` for little-endian.

# Linker flags (not needed for archiving, but kept for reference)
LDFLAGS  :=

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
