# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nel-yama <nassr.elyamani@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 21:03:05 by nel-yama          #+#    #+#              #
#    Updated: 2025/08/13 07:44:45 by nel-yama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable name & Compiler and flags
NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./lib/libft -I./headers

# Libraries
LIBFT_DIR = lib/libft

LIBFT = $(LIBFT_DIR)/libft.a

# Linker Driver Flags (ld) - Linker search paths
LDFLAGS = -L$(LIBFT_DIR)

# Header file (optional, not strictly needed unless for dependencies)
HEADER = headers/main.h

# Source files for main program
MAIN = main.c
BONUS = main_bonus.c

# Source files from source directories
SRC = src/printf/ft_printf.c src/env/ft_get_env.c \
	src/parsing/parsing.c src/pipes/create_pipes.c \
	src/run_cmd/run_cmd.c src/run_cmd/run_child.c \
	src/exit_prog/exit_prog.c src/exit_prog/exit_error.c

# All source files
SRCS = $(MAIN) $(SRC)

# Object files
OBJ_DIR = build
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(MAIN:.c=.o)
BONUS_OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(BONUS:.c=.o)

# Rules
.PHONY: all clean fclean re bonus

# Default rule: build the executable
all: $(NAME)

# Link object files into executable
# Normal executable
$(NAME): $(OBJ) $(LIBFT)
	@echo "Linking $(NAME)..."
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME)

# Bonus executable
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OBJ) $(LIBFT)
	@echo "Linking $(BONUS_NAME)..."
	@$(CC) $(BONUS_OBJ) $(LIBFT) -o $(NAME_BONUS)

# Creating the build Directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile source files into object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Remove object files
clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJ) $(BONUS_OBJ)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Remove object files and the executable
fclean: clean
	@echo "Cleaning the library..."
	@rm -f $(NAME) $(NAME_BONUS)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all
