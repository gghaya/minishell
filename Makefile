# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gghaya <gghaya@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 08:42:13 by gghaya            #+#    #+#              #
#    Updated: 2023/08/04 18:33:56 by gghaya           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc -g -fsanitize=address
FLAGS =  -Wall -Werror -Wextra
CFILES = main.c utils1.c utils2.c utils3.c utils4.c utils5.c utils6.c utils7.c utils8.c utils9.c utils10.c
LIBFTDIR = ft_libft
LIBFT = ft_libft/libft.a

OFILES = ${CFILES:.c=.o}

O = ${C:.c=.o}

all : ${NAME}

${NAME}: ${OFILES} minishell.h ${CFILES} ${LIBFT}
	${CC}  ${FLAGS} ${LIBFT} ${OFILES}  -o  ${NAME} -lreadline


${LIBFT}:
	${MAKE} -C ${LIBFTDIR}
%.o:%.c minishell.h
	${CC} -c ${FLAGS} $<

clean :
	rm -f ${OFILES}
	${MAKE} clean -C ${LIBFTDIR}
fclean : clean
	rm -f ${NAME}
	${MAKE} fclean -C ${LIBFTDIR}
re : fclean all

.PHONY: clean fclean re all 