# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nel-yama <nel-yama@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 21:03:05 by nel-yama          #+#    #+#              #
#    Updated: 2025/08/31 17:28:27 by nel-yama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I.

# Files
SRC_FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
	ft_isquote.c ft_is_escaped.c \
	ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
	ft_split_str.c ft_split_smart.c \
	ft_split_smart_helper.c ft_split_smart_helper_2.c \
	ft_isspace.c ft_str_has_whitespace.c ft_is_str_unique.c \
	ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
	ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	ft_strcount_char.c \
	ft_put_hex_llnbr.c ft_putnbr_base.c \
	ft_put_unsigned_nbr_base.c ft_put_unsigned_nbr.c \
	ft_lstadd_back.c ft_lstadd_front.c \
	ft_lstlast.c ft_lstnew.c ft_lstsize.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	ft_lstmap.c

OBJ_DIR = build
OBJ_FILES = $(SRC_FILES:%.c=$(OBJ_DIR)/%.o)

HEADER = libft.h

# Rules
.PHONY: all clean fclean re #bonus

# Default rule: make all will call make libft.a
all: $(NAME)

# Create the mandatory part of library libft.a
$(NAME): $(OBJ_FILES)
	@echo "Creating library $@"
	@ar rcs $@ $^

# Creating the build Directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile source files (depend on libft.h)
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "Compiling $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Remove object files
clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJ_FILES)
	@rm -rf $(OBJ_DIR)

# Remove object files and the library
fclean: clean
	@echo "Cleaning the library..."
	@rm -f $(NAME)

# Rebuild the library
re: fclean all
