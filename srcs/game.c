/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 12:37:30 by lbertran          #+#    #+#             */
/*   Updated: 2021/08/15 12:37:51 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_game(t_game *game)
{
	int	i;

	i = 0;
	custom_usleep(game->time_to_eat + game->time_to_sleep + 20);
	while (i < game->amount_of_philos)
		pthread_mutex_destroy(&game->fork_mutex[i++]);
	free(game->philos);
	free(game->fork_mutex);
	pthread_mutex_destroy(&game->eat_mutex);
	pthread_mutex_destroy(&game->speak_mutex);
}

void	init_philos(t_game *game)
{
	int			i;

	i = 0;
	game->philos = malloc(sizeof(t_philo) * game->amount_of_philos);
	game->fork_mutex = malloc(sizeof(pthread_mutex_t) * game->amount_of_philos);
	while (i < game->amount_of_philos)
	{
		pthread_mutex_init(&game->fork_mutex[i], NULL);
		game->philos[i].id = i + 1;
		game->philos[i].state = SLEEPING;
		game->philos[i].game = game;
		game->philos[i].lfork = i;
		game->philos[i].rfork = (i + 1) % game->amount_of_philos;
		game->philos[i].tid = pthread_create(&game->philos[i].thread, NULL, \
			routine, &game->philos[i]);
		i++;
	}
	game->start_time = current_millis();
	i = 0;
	while (i < game->amount_of_philos)
		game->philos[i++].last_eat = game->start_time;
	game->sync = 1;
}
