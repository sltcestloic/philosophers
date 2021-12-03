/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 12:37:30 by lbertran          #+#    #+#             */
/*   Updated: 2021/12/03 15:06:42 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	end_game(t_game *game)
{
	int	i;
	int status;
	int num_philo_done_eating;

	num_philo_done_eating = 0;
	status = 1;
	i = 0;
	while (num_philo_done_eating < game->amount_of_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
			while (i < game->amount_of_philos)
				kill(0, SIGKILL);
		if (WEXITSTATUS(status) == 2)
			num_philo_done_eating++;
	}
}

void	init_philos(t_game *game)
{
	int	i;
	int	pid;

	i = 0;
	game->philo.id = 1;
	game->philo.eat_count = 0;
	game->philo.game = game;
	while (i < game->amount_of_philos)
	{
		pid = fork();
		if (!pid)
		{	
			pthread_create(&game->philo.thread, NULL, monitor, game);
			routine(game);
		}
		else
			
		game->philo.id += 1;
		i++;
	}
}
