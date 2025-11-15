/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fses <fses@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:19:32 by fses              #+#    #+#             */
/*   Updated: 2025/08/10 12:35:05 by fses             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	cleanup(t_data *data, int ret)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->end_mutex);
	pthread_mutex_destroy(&data->data_mutex);
	return (ret);
}
