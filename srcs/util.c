/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:59:08 by lbertran          #+#    #+#             */
/*   Updated: 2021/08/14 15:37:47 by lbertran         ###   ########lyon.fr   */
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

long	time_elapsed(t_game *game)
{
	return (current_millis() - game->start_time);
}

int	error(char *msg)
{
	printf("%s\n", msg);
	return (1);
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
	printf("%s%lu%s %d %s\n", RED, time_elapsed(philo->game),
		RESET, philo->id, msg);
	pthread_mutex_unlock(&philo->game->speak_mutex);
}
