#===============================#
#          PROJECT NAME         #
#===============================#

NAME		=	philo

#===============================#
#             VPATH             #
#===============================#

VPATH		=	srcs

#===============================#
#             DIRS              #
#===============================#

OBJS_DIR	=	objs
INCS_DIR	=	includes

#===============================#
#            SOURCES            #
#===============================#


SRCS		= 	ft_atoi.c \
				game.c \
				philo.c \
				util.c

#===============================#
#            OBJECTS            #
#===============================#

OBJS		=	$(addprefix objs/, ${SRCS:.c=.o})

#===============================#
#             FILES             #
#===============================#

HEADERS		=	${INCS_DIR}/philo.h
MAKEFILE 	=	Makefile

#===============================#
#            COMMANDS           #
#===============================#

RM			=	rm -f

#===============================#
#            COMPILER           #
#===============================#

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g3

#===============================#
#             COLORS            #
#===============================#

BLACK		=	\x1b[30m
RED			=	\x1b[31m
GREEN		=	\x1b[32m
YELLOW		=	\x1b[33m
BLUE		=	\x1b[34m
PURPLE		=	\x1b[35m
CYAN		=	\x1b[36m
WHITE		=	\x1b[37m

#===============================#
#             RULES             #
#===============================#

#          MAIN RULES           #

all: ${NAME} 

bonus: all

re: fclean all

#        CLEANING RULES         #

clean:
	${RM} ${OBJS}
	${RM} a.out

fclean: clean
	${RM} ${NAME}

#       COMPILATION RULES       #

${OBJS_DIR}/%.o: %.c ${HEADERS} ${MAKEFILE} 
	@mkdir -p ${OBJS_DIR}
	@${CC} ${CFLAGS} -c $< -o $@ -I ${INCS_DIR}
	@echo "[${NAME}] Compiling ${YELLOW}$<${WHITE}"

${NAME}: ${OBJS}
	@echo "[${NAME}] Creating executable..."
	@${CC} -o ${NAME} ${OBJS}
	@echo "[${NAME}] ${GREEN}Compilation successful!${WHITE}"


#            .PHONY             #

.PHONY: all clean fclean re .c.o
