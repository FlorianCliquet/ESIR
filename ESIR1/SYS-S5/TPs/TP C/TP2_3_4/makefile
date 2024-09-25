# Makefile for a project with a main program and a dynamic library
# Author: Florian Cliquet and Pierre Bertholom
# In the subject it's asked to precise in a text file the commands to compile the project
# But we think that a Makefile is more convenient and easier to use
# And it's also a good way to learn how to use Makefiles
# So we assume that it's okay to use a Makefile for this project and it will replace the text file

NAME = tp_c                # The main executable name
LIBNAME = libmylib.so       # The dynamic library name

# Directories for sources, headers and the dynamic library
SRCS_DIR = srcs/
HEADERS_DIR = headers/
LIB_DIR = lib/

LIB_SRCS = $(wildcard $(LIB_DIR)*.c)       # Sources for the dynamic library
MAIN_SRCS = $(wildcard $(SRCS_DIR)*.c)     # Sources for the main program

MY_LIB_OBJECTS = $(LIB_SRCS:.c=.o)         # Objects for the dynamic library
MY_MAIN_OBJECTS = $(MAIN_SRCS:.c=.o)       # Objects for the main program

CFLAGS = -Wall -Wextra -Werror -g          # Compiler flags
LDFLAGS = -L. -lmylib                      # Linker flags, linking with the dynamic library
CC = gcc                                   # Compiler

# Rule for creating .o files from .c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADERS_DIR)

# Target to build the dynamic library
$(LIBNAME): $(MY_LIB_OBJECTS)
	$(CC) -fPIC -shared -o $(LIBNAME) $(MY_LIB_OBJECTS)

# Target to build the main executable, linking with the dynamic library
$(NAME): $(MY_MAIN_OBJECTS) $(LIBNAME)
	$(CC) $(CFLAGS) $(MY_MAIN_OBJECTS) -o $(NAME) $(LDFLAGS)

# Build the dynamic library
all: $(LIBNAME)

# Build the main executable
main: $(NAME)

# Clean object files
clean:
	rm -f $(MY_LIB_OBJECTS) $(MY_MAIN_OBJECTS)

# Clean object files and binaries
fclean: clean
	rm -f $(NAME) $(LIBNAME)

# Rebuild everything
re: fclean all main

.PHONY: all clean fclean re main
