/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:59:08 by lbertran          #+#    #+#             */
/*   Updated: 2021/06/28 13:43:40 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_millis(void)
{
	struct timeval	time;
	long long		s1;
	long long		s2;

	gettimeofday(&time, NULL);
	s1 = (long long)(time.tv_sec) *1000;
	s2 = (time.tv_usec / 1000);
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
	printf("%s%lu%s %d %s\n", RED, time_elapsed(&philo->game), RESET, philo->id, msg);
	pthread_mutex_unlock(&philo->game->speak_mutex);
}
