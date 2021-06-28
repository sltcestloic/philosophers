/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertran <lbertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:22:07 by lbertran          #+#    #+#             */
/*   Updated: 2021/06/28 13:52:48 by lbertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_philo *philo)
{
	while (1)
	{
		if (current_millis() - philo->last_eat > philo->game->time_to_die)
		{
			philo->game->ended = 1;
			print_msg(philo, "died");
		}
	}
}

void	routine(t_philo *philo)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, &monitor, philo);
	while (1)
	{
		pthread_mutex_lock(&philo->game->fork_mutex[philo->lfork]);
		print_msg(philo, "has taken a fork");
		pthread_mutex_lock(&philo->game->fork_mutex[philo->rfork]);
		print_msg(philo, "has taken a fork");
		usleep(philo->game->time_to_eat * 1000);
	}
}

void	init_philos(t_game *game)
{
	int			i;
	pthread_t	tid;

	i = 0;
	game->philos = malloc(sizeof(t_philo) * game->amount_of_philos);
	while (i < game->amount_of_philos)
	{
		game->philos[i].id = i + 1;
		game->philos[i].state = SLEEPING;
		game->philos[i].thread = pthread_create(&tid, NULL, &routine, &game->philos[i]);
		pthread_detach(tid);
		game->philos[i].game = game;
		game->philos[i].lfork = i;
		game->philos[i].rfork = (i + 1) % game->amount_of_philos;
		pthread_mutex_init(&game->fork_mutex[i], NULL);
	}
}

int	parse_args(int ac, char **av, t_game *game)
{
	game->amount_of_philos = ft_atoi(av[1]);
	game->time_to_die = ft_atoi(av[2]);
	game->time_to_eat = ft_atoi(av[3]);
	game->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		game->must_eat_times = ft_atoi(av[5]);
	else
		game->must_eat_times = 0;
	if (game->time_to_die < 60 || game->time_to_eat < 60
		|| game->time_to_sleep < 60 || game->amount_of_philos < 1
		|| game->amount_of_philos > 200 || game->must_eat_times < 0)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 5 && ac != 6)
		return (error("Error: wrong number of arguments."));
	game.start_time = current_millis();
	game.ended = 0;
	if (!parse_args(ac, av, &game))
		return (error("Error: invalid argument."));
	init_philos(&game);
	usleep(10000);
	printf("%s%lu%s Simulation started\n", RED, time_elapsed(&game), RESET);
}
