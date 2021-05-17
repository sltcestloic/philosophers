# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/18 16:40:32 by lbertran          #+#    #+#              #
#    Updated: 2021/05/17 13:02:50 by lbertran         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

all:
	@${MAKE} -C ./srcs/philo_one
	@${MAKE} -C ./srcs/philo_two
	@${MAKE} -C ./srcs/philo_three

clean:
	@${MAKE} clean -C ./srcs/philo_one
	@${MAKE} clean -C ./srcs/philo_two
	@${MAKE} clean -C ./srcs/philo_three

fclean: clean
	@${MAKE} fclean -C ./srcs/philo_one
	@${MAKE} fclean -C ./srcs/philo_two
	@${MAKE} fclean -C ./srcs/philo_three

re: fclean all
	
.PHONY: all clean fclean re .c.o
