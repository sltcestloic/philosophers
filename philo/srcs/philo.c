/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:22:07 by lbertran          #+#    #+#             */
/*   Updated: 2021/12/07 13:56:57 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->amount_of_philos)
	{
		if (game->eat_counter == game->amount_of_philos)
			return (0);
		pthread_mutex_lock(&game->eat_mutex);
		if ((long)current_millis() - game->philos[i].last_eat
			> game->time_to_die)
		{
			print_msg(&game->philos[i], "died");
			game->ended = 1;
			return (0);
		}
		pthread_mutex_unlock(&game->eat_mutex);
		i++;
		usleep(200);
	}
	return (1);
}

void	routine2(t_philo *philo)
{
	pthread_mutex_unlock(&philo->game->eat_mutex);
	custom_usleep(philo->game->time_to_eat);
	pthread_mutex_unlock(&philo->game->fork_mutex[philo->lfork]);
	pthread_mutex_unlock(&philo->game->fork_mutex[philo->rfork]);
	print_msg(philo, "is sleeping");
	custom_usleep(philo->game->time_to_sleep);
	print_msg(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	synchronize(philo);
	while (!philo->game->ended
		&& philo->game->eat_counter < philo->game->amount_of_philos)
	{
		pthread_mutex_lock(&philo->game->fork_mutex[philo->lfork]);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(&philo->game->fork_mutex[philo->rfork]);
		print_msg(philo, "has taken a fork");
		print_msg(philo, "is eating");
		pthread_mutex_lock(&philo->game->eat_mutex);
		philo->last_eat = current_millis();
		philo->eat_count++;
		if (philo->game->must_eat_times && philo->eat_count
			== philo->game->must_eat_times)
			philo->game->eat_counter++;
		routine2(philo);
	}
	return (NULL);
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
		if (game->must_eat_times == 0)
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
	game.ended = 0;
	game.eat_counter = 0;
	pthread_mutex_init(&game.eat_mutex, NULL);
	pthread_mutex_init(&game.speak_mutex, NULL);
	if (!parse_args(ac, av, &game))
		return (error("Error: invalid argument."));
	game.sync = 0;
	if (!init_philos(&game))
		return (error("Malloc error."));
	while (monitor(&game))
		;
	end_game(&game);
	return (0);
}
