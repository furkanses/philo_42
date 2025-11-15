/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fses <fses@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:24:38 by fses              #+#    #+#             */
/*   Updated: 2025/08/10 12:38:01 by fses             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	handle_single(t_philo *p)
{
	pthread_mutex_lock(&p->data->forks[p->left_fork]);
	print_status(p, "has taken a fork");
	wait_for(p->data->time_to_die, p->data, p, 0);
	pthread_mutex_unlock(&p->data->forks[p->left_fork]);
	return (0);
}

void	set_waiting(t_philo *p, int v)
{
	pthread_mutex_lock(&p->data->data_mutex);
	p->is_waiting_for_forks = v;
	pthread_mutex_unlock(&p->data->data_mutex);
}

void	pick_order(t_philo *p, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (p->id % 2 == 1)
	{
		*first = &p->data->forks[p->left_fork];
		*second = &p->data->forks[p->right_fork];
	}
	else
	{
		usleep(1000);
		*first = &p->data->forks[p->right_fork];
		*second = &p->data->forks[p->left_fork];
	}
}

int	abort_now(t_philo *p, pthread_mutex_t *a, pthread_mutex_t *b)
{
	if (!is_simulation_stopped(p->data))
		return (0);
	if (b)
		pthread_mutex_unlock(b);
	if (a)
		pthread_mutex_unlock(a);
	set_waiting(p, 0);
	return (1);
}
