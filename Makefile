# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbordin <rbordin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 12:07:44 by rbordin           #+#    #+#              #
#    Updated: 2023/05/04 15:55:14 by rbordin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

MAKEFLAGS += --silent

SRC = pipex.c \
	pipex_utils.c \
	pipex_cleaner.c \

OBJ = ${SRC:.c=.o}

CC = gcc -g

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g

.o:.c
		${cc} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ} ${LIBFT}
		${CC} ${OBJ} ${LIBFT} -o $@
		@echo "\033[32mCompiled OK!\033[0m"


${LIBFT}:
		make -C $(LIBFT_PATH)

clean:
		${RM} ${OBJ}
		make clean -C ${LIBFT_PATH}
		@echo "\033[35mCleared everything!\033[0m"
		
fclean: clean
		${RM} ${LIBFT}
		${RM} ${NAME}

re: fclean all