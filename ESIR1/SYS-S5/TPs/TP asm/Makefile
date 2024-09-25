# Name of the ASM file (without extension)
# If you want to compile a different file, change the value of NAME
# WARNING: We haven't made this Makefile to compile multiple files at once
# We could do it but we don't have any file that needs it
# Check our C TP for a Makefile that can compile multiple files at once : https://github.com/FlorianCliquet/ESIR/blob/main/ESIR1/SYS-S5/TPs/TP%20C/TP2_3_4/makefile

NAME = chiff7

# Compiler and linker
ASM = nasm
ASMFLAGS = -f elf
LD = ld
LDFLAGS = -m elf_i386

# Debugging flags (optional)
DEBUG_FLAGS = -g

# Input and output files
ASM_FILE = srcs/$(NAME).s
OBJ_FILE = srcs/$(NAME).o
OUT_FILE = $(NAME)

# Default target: compile and link
.PHONY: all
all: $(OUT_FILE)

# Rule to compile .s file to .o
$(OBJ_FILE): $(ASM_FILE)
	@echo "Assembling $(ASM_FILE) to $(OBJ_FILE)..."
	$(ASM) $(ASMFLAGS) $(DEBUG_FLAGS) -o $(OBJ_FILE) $(ASM_FILE)

# Rule to link .o file to create the executable
$(OUT_FILE): $(OBJ_FILE)
	@echo "Linking $(OBJ_FILE) to create $(OUT_FILE)..."
	$(LD) $(LDFLAGS) -o $(OUT_FILE) $(OBJ_FILE)

# Debug target: Compile and link with debug symbols
.PHONY: debug
debug: ASMFLAGS += $(DEBUG_FLAGS)
debug: LDFLAGS += $(DEBUG_FLAGS)
debug: clean all

# Clean object and output files
.PHONY: clean
clean:
	@echo "Cleaning object files..."
	rm -f $(OBJ_FILE)

# Full clean (object + output files)
.PHONY: fclean
fclean:
	@echo "Cleaning all build files..."
	rm -f $(OBJ_FILE) $(OUT_FILE)

# Rebuild everything from scratch
.PHONY: rebuild
rebuild: fclean all

# Help
.PHONY: help
help:
	@echo "Usage:"
	@echo "  make          # Compiles and links $(NAME).s"
	@echo "  make debug    # Compiles and links $(NAME).s with debug symbols"
	@echo "  make clean    # Removes $(NAME).o"
	@echo "  make fclean   # Removes $(NAME).o and $(NAME) executable"
	@echo "  make rebuild  # Cleans and rebuilds everything from scratch"
	@echo "  make help     # Displays this help message"

