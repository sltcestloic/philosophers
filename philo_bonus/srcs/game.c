/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 12:37:30 by lbertran          #+#    #+#             */
/*   Updated: 2021/12/07 13:59:58 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	end_game(t_game *game)
{
	int	i;
	int	status;
	int	num_philo_done_eating;

	num_philo_done_eating = 0;
	status = 1;
	i = 0;
	while (waitpid(-1, &status, 0) != -1)
	{
		if (WEXITSTATUS(status) == 1)
			while (i < game->amount_of_philos)
				kill(game->pids[i++], SIGKILL);
	}
	free(game->pids);
}

int	init_philos(t_game *game)
{
	int	i;

	i = 0;
	game->philo.id = 1;
	game->philo.eat_count = 0;
	game->philo.game = game;
	game->pids = malloc(sizeof(int) * game->amount_of_philos);
	if (!game->pids)
		return (0);
	while (i < game->amount_of_philos)
	{
		game->pids[i] = fork();
		if (!game->pids[i])
		{	
			pthread_create(&game->philo.thread, NULL, monitor, game);
			routine(game);
		}
		else
			game->philo.id += 1;
		i++;
	}
	return (1);
}
