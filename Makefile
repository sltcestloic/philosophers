# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 16:40:32 by lbertran          #+#    #+#              #
#    Updated: 2021/06/17 08:59:44 by lbertran         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRC		= philo.c \
			ft_atoi.c \
			util.c
SRCS 	= $(addprefix srcs/, ${SRC})
OBJS	= ${SRCS:.c=.o}
INCS	= includes
NAME	= philo
LIBC	= ar rcs
CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror -g3

%.o: %.c ${INCS}/${NAME}.h
	${CC} ${CFLAGS} -c $< -o $@ -I${INCS}

${NAME}: ${OBJS}
	${CC} -o ${NAME} ${OBJS}
	
all: ${NAME}

bonus: all

clean:
	${RM} ${OBJS}
	${RM} a.out

fclean: clean
	${RM} ${NAME}

re: fclean all
	
.PHONY: all clean fclean re .c.o
