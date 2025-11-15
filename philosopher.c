/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fses <fses@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:19:21 by fses              #+#    #+#             */
/*   Updated: 2025/08/10 12:40:20 by fses             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->data->data_mutex);
	while (!is_simulation_stopped(philo->data))
	{
		if (!eat_meal(philo))
			break ;
		if (is_simulation_stopped(philo->data))
			break ;
		print_status(philo, "is sleeping");
		wait_for(philo->data->time_to_sleep, philo->data, philo, 0);
		if (is_simulation_stopped(philo->data))
			break ;
		if (!dynamic_think(philo))
			break ;
	}
	return (NULL);
}

long long	get_last_meal(t_data *data, int i)
{
	long long	time;

	pthread_mutex_lock(&data->data_mutex);
	time = data->philos[i].last_meal_time;
	pthread_mutex_unlock(&data->data_mutex);
	return (time);
}

int	all_philos_met_goal(t_data *data)
{
	int	i;

	if (data->must_eat == -1)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (data->philos[i].meals_eaten < data->must_eat)
		{
			pthread_mutex_unlock(&data->data_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->data_mutex);
		i++;
	}
	return (1);
}
