/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:22:21 by lbertran          #+#    #+#             */
/*   Updated: 2021/12/07 13:56:25 by lbertran         ###   ########lyon.fr   */
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
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_eat;
	int				lfork;
	int				rfork;
	pthread_t		thrd;
	id_t			tid;
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
	pthread_mutex_t	eat_mutex;
	int				eat_counter;
	int				sync;
}				t_game;

int			ft_atoi(const char *str);
uint64_t	current_millis(void);
int			error(char *msg);
void		print_msg(t_philo *philo, char *msg);
void		custom_usleep(long time);
void		synchronize(t_philo *philo);
void		*routine(void *arg);
int			init_philos(t_game *game);
void		end_game(t_game *game);
#endif