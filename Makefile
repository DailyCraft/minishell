# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/02 08:35:31 by dvan-hum          #+#    #+#              #
#    Updated: 2025/01/24 16:45:32 by dvan-hum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -Wall -Wextra -Werror -O3

SRC = envp_utils.c envp.c errors.c main.c signals.c tty.c utils.c
SRC_CMD = cd.c echo.c env.c exit.c export.c pwd.c unset.c
SRC_EXEC = exec.c heredoc.c pipeline.c redirect.c runs.c utils.c
SRC_PARSING = check_valid_token.c command_error.c command_utils.c command.c envp.c \
	line.c quote.c redirect.c subshell.c token_utils.c tokenize.c wildcards_utils.c wildcards.c
SRC += $(SRC_CMD:%=commands/%) $(SRC_EXEC:%=execution/%) $(SRC_PARSING:%=parsing/%)
HEADERS = minishell.h
OBJ = $(SRC:%.c=obj/%.o)

ifndef VERBOSE
MAKEFLAGS += --silent
endif

all: $(NAME)

%.a:
	make -C $(shell dirname $@)

$(NAME): libft/libft.a $(OBJ)
	echo "\n\t\e[1;32mBuilding\e[0m \e[36m$(NAME)\e[0m\n"
	$(CC) -o $(NAME) $(OBJ) -L ./libft -lft -lreadline

obj/%.o: src/%.c $(HEADERS)
	echo "$(NAME) \e[90m➤\e[0m \e[32mCompiling\e[0m \e[36m$<\e[0m"
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ -I ./ -I ./libft

clean:
	make -C libft clean
	echo "$(NAME) \e[90m➤\e[0m\t\e[1;31mCleaning object files\e[0m"
	rm -rf ./obj

fclean:
	make -C libft fclean
	echo "$(NAME) \e[90m➤\e[0m\t\e[1;31mCleaning object files\e[0m"
	rm -rf ./obj
	echo "$(NAME) \e[90m➤\e[0m\t\e[31mCleaning $(NAME)\e[0m"
	rm -f $(NAME)

re: fclean all

bonus: all

run: all
	./$(NAME)

gdb: all
	gdb -q -tui ./$(NAME)

vg: all
	valgrind --leak-check=full ./$(NAME)