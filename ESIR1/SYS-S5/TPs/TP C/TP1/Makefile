# Name of the final executable
NAME = code_breaker

# Directory containing source files
SRCS_DIR = srcs/

# Directory containing header files
HEADERS_DIR = headers/

# List of all source files in the source directory
MY_SOURCES = $(wildcard $(SRCS_DIR)*.c)

# List of all object files corresponding to the source files
MY_OBJECTS = $(MY_SOURCES:.c=.o)

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Compiler to use
CC = gcc

# Rule to compile a .c file into a .o file
# This rule will be used for each source file to create its object file
# $< represents the first prerequisite (i.e., the .c file)
# $@ represents the target (i.e., the .o file)
.o: .c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADERS_DIR)

# Rule to link all object files to create the final executable
# $(NAME) is the target executable
# $(MY_OBJECTS) is the list of object files to be linked
$(NAME): $(MY_OBJECTS)
	$(CC) $(CFLAGS) $(MY_OBJECTS) -o $(NAME)

# Default target to build the executable
# It depends on the $(NAME) target, which is the final executable
all: $(NAME)

# Rule to remove all object files
# This is used to clean up the build directory
clean:
	rm -f $(MY_OBJECTS)

# Rule to remove all object files and the final executable
# It depends on the clean target to ensure object files are removed first
fclean: clean
	rm -f $(NAME)

# Rule to recompile the project from scratch
# It depends on the fclean target to ensure a fresh start
re: fclean all

# Declare the following targets as phony, meaning they do not represent actual files
# This prevents make from confusing these targets with files named 'all', 'clean', etc.
.PHONY: all clean fclean re
