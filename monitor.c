/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fses <fses@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:19:24 by fses              #+#    #+#             */
/*   Updated: 2025/08/10 12:40:10 by fses             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

static void	end_simulation(t_data *data)
{
	pthread_mutex_lock(&data->end_mutex);
	data->simulation_end = 1;
	pthread_mutex_unlock(&data->end_mutex);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	if (!data || !data->philos)
		return (NULL);
	while (1)
	{
		if (check_death(data))
			return (NULL);
		if (all_philos_met_goal(data))
		{
			end_simulation(data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

static void	announce_death(t_data *data, int i, long long now)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%lld %d died\n", now - data->start_time, data->philos[i].id);
	pthread_mutex_unlock(&data->print_mutex);
}

static int	handle_death(t_data *data, int i, long long last_meal)
{
	long long	now;

	now = get_time();
	if (now - last_meal < data->time_to_die)
		return (0);
	pthread_mutex_lock(&data->end_mutex);
	if (!data->simulation_end)
	{
		data->simulation_end = 1;
		pthread_mutex_unlock(&data->end_mutex);
		announce_death(data, i, now);
		return (1);
	}
	pthread_mutex_unlock(&data->end_mutex);
	return (1);
}

int	check_death(t_data *data)
{
	int			i;
	long long	last_meal;

	i = 0;
	while (i < data->num_philos)
	{
		last_meal = get_last_meal(data, i);
		if (last_meal != -1 && handle_death(data, i, last_meal))
			return (1);
		i++;
	}
	return (0);
}
