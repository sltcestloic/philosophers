/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:22:21 by lbertran          #+#    #+#             */
/*   Updated: 2021/12/07 13:45:38 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
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
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	long			last_eat;
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
	sem_t			*voice;
	sem_t			*fork;
	sem_t			*eating;
	int				*pids;
	t_philo			philo;
}				t_game;

int			ft_atoi(const char *str);
uint64_t	current_millis(void);
int			error(char *msg);
void		print_msg(t_philo *philo, char *msg);
void		custom_usleep(long time);
void		synchronize(t_philo *philo);
void		routine(t_game *game);
int			init_philos(t_game *game);
void		end_game(t_game *game);
void		*monitor(void *game);
#endif