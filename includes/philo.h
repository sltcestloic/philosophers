/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:22:21 by lbertran          #+#    #+#             */
/*   Updated: 2021/06/28 13:41:48 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define EATING 1
# define THINKING 2
# define SLEEPING 3
# define RED "\e[0;91m"
# define BLUE "\e[0;94m"
# define RESET "\e[0m"
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_philo
{
	int				state;
	int				id;
	int				eat_count;
	long			last_eat;
	long			death_time;
	int				lfork;
	int				rfork;
	pthread_t		thread;
	struct s_game	*game;
}				t_philo;

typedef struct s_game
{
	long			start_time;
	int				amount_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_times;
	int				ended;
	t_philo			*philos;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	speak_mutex;
}				t_game;

int			ft_atoi(const char *str);
long long	current_millis(void);
long		time_elapsed(t_game *game);
int			error(char *msg);
void		print_msg(t_philo *philo, char *msg);
#endif