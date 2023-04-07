# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbordin <rbordin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/31 12:07:44 by rbordin           #+#    #+#              #
#    Updated: 2023/04/07 12:15:04 by rbordin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

SRC = pipex.c \
	pipex_utils.c \

OBJ = ${SRC:.c=.o}

CC = gcc -g

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g

.o:.c
		${cc} ${CFLAGS} -c $< -o ${NAME}

all: ${NAME}

${NAME}: ${OBJ} ${LIBFT}
		${CC} ${OBJ} ${LIBFT}

${LIBFT}:
		make -C $(LIBFT_PATH)

clean:
		${RM} ${OBJ}
		make clean -C ${LIBFT_PATH}
		
fclean: clean
		${RM} ${LIBFT}
		${RM} ${NAME}

re: fclean all