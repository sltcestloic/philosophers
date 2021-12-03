/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:59:08 by lbertran          #+#    #+#             */
/*   Updated: 2021/12/03 14:48:02 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	custom_usleep(long time)
{
	uint64_t	current;

	current = current_millis();
	while (current + time > current_millis())
		usleep(20);
}

void	print_msg(t_philo *philo, char *msg)
{
	sem_wait(philo->game->voice);
	printf("%s%llu%s %d %s\n", RED, current_millis() - philo->game->start_time,
		RESET, philo->id, msg);
	sem_post(philo->game->voice);
}
