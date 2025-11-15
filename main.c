/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fses <fses@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:19:27 by fses              #+#    #+#             */
/*   Updated: 2025/08/10 12:19:28 by fses             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;
	int			i;

	if (check_args(argc, argv) != 0)
		return (1);
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_mutexes(&data) != 0)
		return (cleanup(&data, 1));
	if (init_philos(&data) != 0)
		return (cleanup(&data, 1));
	data.start_time = get_time();
	i = -1;
	while (++i < data.num_philos)
		if (pthread_create(&data.philos[i].thread, NULL, philosopher_routine,
				&data.philos[i]) != 0)
			return (cleanup(&data, 1));
	if (pthread_create(&monitor, NULL, monitor_routine, &data) != 0)
		return (cleanup(&data, 1));
	i = -1;
	while (++i < data.num_philos)
		pthread_join(data.philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (cleanup(&data, 0));
}
