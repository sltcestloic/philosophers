/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:22:07 by lbertran          #+#    #+#             */
/*   Updated: 2021/12/03 14:57:40 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *arg)
{
	t_game *game;

	game = (t_game *)arg;
	while (42)
	{
		sem_wait(game->eating);
		if (game->philo.eat_count == game->must_eat_times)
			exit (2);
		else if ((long)current_millis() - game->philo.last_eat
			> game->time_to_die)
		{
			print_msg(&game->philo, "died");
			exit (1);
		}
		sem_post(game->eating);
		usleep(200);
	}
}

void	routine(t_game *game)
{
	while (42)
	{
		sem_wait(game->fork);
		print_msg(&game->philo, "has taken a fork");
		sem_wait(game->fork);
		print_msg(&game->philo, "has taken a fork");
		print_msg(&game->philo, "is eating");
		sem_wait(game->eating);
		game->philo.last_eat = current_millis();
		sem_post(game->eating);
		game->philo.eat_count++;
		custom_usleep(game->time_to_eat);
		sem_post(game->fork);
		sem_post(game->fork);
		print_msg(&game->philo, "is sleeping");
		custom_usleep(game->time_to_sleep);
		print_msg(&game->philo, "is thinking");
	}
}

int	parse_args(int ac, char **av, t_game *game)
{
	game->amount_of_philos = ft_atoi(av[1]);
	game->time_to_die = ft_atoi(av[2]);
	game->time_to_eat = ft_atoi(av[3]);
	game->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		game->must_eat_times = ft_atoi(av[5]);
		if (game->must_eat_times == -1)
			return (0);
	}
	else
		game->must_eat_times = -1;
	if (game->time_to_die < 60 || game->time_to_eat < 60
		|| game->time_to_sleep < 60 || game->amount_of_philos < 1
		|| game->amount_of_philos > 200
		|| (game->must_eat_times < 0 && game->must_eat_times != -1))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 5 && ac != 6)
		return (error("Error: wrong number of arguments."));
	if (!parse_args(ac, av, &game))
		return (error("Error: invalid argument."));
	game.voice = sem_open("/philo_voice", O_CREAT, S_IRWXU, 1);
	sem_unlink("/philo_voice");
	game.fork = sem_open("/philo_fork", O_CREAT, S_IRWXU, game.amount_of_philos);
	sem_unlink("/philo_fork");
	game.eating = sem_open("/philo_eating", O_CREAT, S_IRWXU, 1);
	sem_unlink("/philo_eating");
	game.start_time = current_millis();
	game.philo.last_eat = current_millis();
	init_philos(&game);
	end_game(&game);
	return (0);
}
