/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:59:08 by lbertran          #+#    #+#             */
/*   Updated: 2021/08/15 12:36:27 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	current_millis(void)
{
	struct timeval	time;
	uint64_t		s1;
	uint64_t		s2;

	gettimeofday(&time, NULL);
	s1 = time.tv_sec * 1000;
	s2 = time.tv_usec / 1000;
	return (s1 + s2);
}

int	error(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

void	synchronize(t_philo *philo)
{
	while (!philo->game->sync)
		usleep(1000);
	if (philo->id % 2 == 1)
		usleep(2000);
}

void	custom_usleep(long time)
{
	uint64_t	current;

	current = current_millis();
	while (current + time > current_millis())
		usleep(20);
}

void	print_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->game->speak_mutex);
	if (philo->game->ended
		|| philo->game->eat_counter == philo->game->amount_of_philos)
	{
		pthread_mutex_unlock(&philo->game->speak_mutex);
		return ;
	}
	printf("%s%llu%s %d %s\n", RED, current_millis() - philo->game->start_time,
		RESET, philo->id, msg);
	pthread_mutex_unlock(&philo->game->speak_mutex);
}
