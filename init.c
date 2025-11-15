/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fses <fses@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:19:30 by fses              #+#    #+#             */
/*   Updated: 2025/08/10 15:25:07 by fses             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <unistd.h>

int	init_data(t_data *data, int argc, char **argv)
{
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[1]) > 200 || ft_atoi(argv[2]) < 60
		|| ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60 || (argv[5]
			&& ft_atoi(argv[5]) <= 0))
	{
		write(2, "Error: Invalid argument\n", 25);
		return (1);
	}
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	data->simulation_end = 0;
	data->start_time = 0;
	data->forks = NULL;
	data->philos = NULL;
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->end_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].last_meal_time = -1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].is_waiting_for_forks = 0;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}
