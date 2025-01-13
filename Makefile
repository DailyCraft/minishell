# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dvan-hum <dvan-hum@student.42perpignan.fr> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/02 08:35:31 by dvan-hum          #+#    #+#              #
#    Updated: 2025/01/10 15:16:52 by dvan-hum         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -Wall -Wextra -Werror -g -fsanitize=address

SRC = envp_utils.c envp.c errors.c main.c tty.c utils.c \
	commands/cd.c commands/echo.c commands/env.c commands/exit.c commands/export.c commands/pwd.c commands/unset.c \
	execution/exec.c execution/pipeline.c execution/redirect.c execution/runs.c execution/utils.c \
	parsing/command_del.c parsing/command.c parsing/logical_operator.c parsing/parsing.c parsing/pipe.c parsing/redirections_op.c parsing/redirections.c
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

gdb: all
	gdb -q -tui ./minishell

run: all
	./minishell