/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fses <fses@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:19:35 by fses              #+#    #+#             */
/*   Updated: 2025/08/31 12:05:24 by fses             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	dynamic_think(t_philo *philo)
{
	long long	think_time;
	long long	time_since_last_meal;

	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->last_meal_time != -1)
	{
		time_since_last_meal = get_time() - philo->last_meal_time;
		if (time_since_last_meal > philo->data->time_to_die / 2)
			think_time = 1;
		else
			think_time = philo->data->time_to_eat / 2;
	}
	else
		think_time = 1;
	pthread_mutex_unlock(&philo->data->data_mutex);
	print_status(philo, "is thinking");
	wait_for(think_time, philo->data, philo, 0);
	return (1);
}

int	is_simulation_stopped(t_data *data)
{
	int	stopped;

	pthread_mutex_lock(&data->end_mutex);
	stopped = data->simulation_end;
	pthread_mutex_unlock(&data->end_mutex);
	return (stopped);
}

void	wait_for(long long time, t_data *data, t_philo *philo, int is_eating)
{
	long long	start;
	long long	current_time;

	start = get_time();
	while (get_time() - start < time)
	{
		if (is_simulation_stopped(data))
			return ;
		if (!is_eating)
		{
			current_time = get_time();
			pthread_mutex_lock(&data->data_mutex);
			if (philo->last_meal_time != -1 && current_time
				- philo->last_meal_time >= data->time_to_die)
			{
				pthread_mutex_unlock(&data->data_mutex);
				return ;
			}
			pthread_mutex_unlock(&data->data_mutex);
		}
		usleep(100);
	}
}
