# Makefile Project: Windows

**This is the makefile intended for usage with the Windows command line (not PowerShell). This document explains the structure of the project and how it relates to the makefile.**

## Building this project

### Requirements

1. **MicroBlaze GCC**: Ensure that you have the appropriate MicroBlaze GCC compiler installed.
2. **Make**: After installing, you will already have `mingw32-make`. Look for the `mingw32-make` way in this guide, and you can skip the installation and proceed to step 6. https://www.technewstoday.com/install-and-use-make-in-windows/

### Build flow

1. Clone this repository from the Windows cmd: `> git clone https://github.com/Goldan32/c-build-systems.git`
2. Go to the windows folder: `> cd c-build-systems\windows`
3. Build the project: `> make all`
4. Test the project (if applicable): `> .\bin\helloworld.exe`

Output should be:

```
Hello World!
Hello from another file!
Static library says 3*3 is 9
```

5. Test clean target: `> make clean`

## Project structure

### Defining folders

```
SRC_DIR  := sources         # .c source files
BIN_DIR  := bin             # folder containing the binary (.exe) output
OBJ_DIR  := $(BIN_DIR)\obj  # object files created during compilation
REL_INC_DIR := include      # .h source files
LIB_NAME := libarithmetic.a # name of the static library
```

These variables define where the makefile will search for the source files. The names of these folders and files can be changed freely. The `OBJ_DIR` is nested within the `BIN_DIR`, but it could be placed in the project root folder separately by changing its value here.

### Defining targets

```
LIB := $(BIN_DIR)/$(LIB_NAME)
```

This is the final target, the static library. We define it so it will be located in the `BIN_DIR` folder.

```
C_SRCS := $(shell forfiles /P $(SRC_DIR) /S /M *.c /C "cmd /c echo @relpath")
C_SRCS := $(subst ",,$(C_SRCS))  # Remove quotes from path
C_SRCS := $(subst .\,$(SRC_DIR)/,$(C_SRCS))  # Replace .\ to source directory path
```

This is where the `.c` sources are collected. The `forfiles` command lists all the files matching the pattern in its argument. The `subst` function removes quotes and adjusts paths.

```
OBJ := $(subst $(SRC_DIR)/,$(OBJ_DIR)/,$(C_SRCS:.c=.o))
```

This is where the object files are collected. These files match the names of the `.c` source files, but with an `.o` extension.

### Include directories

```
INC_DIR := $(realpath $(REL_INC_DIR))
INC_DIRS := $(shell cd $(INC_DIR) && dir /s /b /ad 2> NUL)
INC_DIRS := $(sort $(INC_DIRS))  # Remove duplicates
INC_DIRS := $(subst \,/,$(INC_DIRS))  # Convert backslashes to forward slashes
INC_DIRS := $(addprefix -I,$(INC_DIRS))
```

The `INC_DIR` is the absolute path to the include directory. The `INC_DIRS` variable collects all the include directories in the source directory and subdirectories, removes duplicates, converts backslashes to forward slashes, and adds the `-I` prefix.

### Various other defines

```
RMDIR := rd /s /q
```

The standard makefile defines some variables. `RMDIR` is such a variable, but we can explicitly redefine it. This definition is equivalent to the Linux command `rm -rf` in Windows cmd form.

### Compile flags

```
CC       := mb-gcc
AR       := mb-ar
CPPFLAGS := -I$(INC_DIR) $(INC_DIRS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"
CFLAGS   := -Wall -Werror -mcpu=v11.0 -mxl-mode -meb -fmessage-length=0
```

`CC` stands for C compiler, and `AR` stands for archiver. `CPPFLAGS` stands for C PreProcessor Flags, allowing us to define our include directory and other preprocessor options. `CFLAGS` are flags passed to the compiler.

- `-mcpu=v11.0`: Specifies the MicroBlaze CPU version.
- `-mxl-mode`: Enables MicroBlaze extended mode instructions.
- `-meb`: Sets the endianness to big-endian. Use `-mel` for little-endian.
- `-fmessage-length=0`: Do not wrap diagnostic messages, useful for environments with limited screen width.

### Explanation of Dependency Flags

- `-MMD`: Generate dependency files alongside the object files, listing the dependencies for each `.o` file without including system headers.
- `-MP`: Add a phony target for each dependency to prevent `make` from failing if a header file is removed.
- `-MF"$(@:%.o=%.d)"`: Specify the name of the file to which the dependencies should be written, replacing the `.o` extension with `.d`.
- `-MT"$@"`: Change the target of the rule emitted by dependency generation, ensuring dependencies are correctly attributed to the object file being generated.

### Phony targets

```
.PHONY: all clean archive echoes
```

Phony targets are not interpreted as file names, even if a file exists with such a name. Phony targets are used to collect multiple other targets most of the time.

## Target recipes

```
all: archive
```

The `all` target is a convention; it is the final target of the project.

```
$(LIB): $(OBJ)
	$(AR) rcs $@ $^
```

This part says that to build the static library, we will need the object files. If any of those are not ready or up-to-date, their recipes will execute.

```
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
```

This is the recipe for the object files. Their prerequisites are the corresponding `.c` files and the existence of the `OBJ_DIR`.

```
$(OBJ_DIR):
	@if not exist "$@" mkdir $@
```

This is the recipe for creating the object directory. If it doesn't exist, the makefile creates it here.

```
clean:
	@if exist $(OBJ_DIR) $(RMDIR) $(OBJ_DIR)
	@if exist $(LIB_DIR) $(RMDIR) $(LIB_DIR)
```

The `clean` target deletes everything that is created during the compile process.

```
archive: $(LIB)
```

The `archive` target creates the static library.

```
echoes:
	@echo "Include Directories: $(INC_DIRS) -I$(INC_DIR)"
	@echo "Source Directories: $(SRC_DIR)"
	@echo "Source Files: $(C_SRCS)"
	@echo "Object Directories: $(OBJ_DIR)"
	@echo "Object files: $(OBJ)"
```

The `echoes` target prints out the collected directories and files for debugging purposes.

### Include other makefile sources

```
-include $(OBJ:.o=.d)
```

GCC creates a `.d` file for every `.o` file, which contains makefile rules, so they are included here.
