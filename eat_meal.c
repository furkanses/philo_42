/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_meal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fses <fses@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:26:01 by fses              #+#    #+#             */
/*   Updated: 2025/08/10 12:41:21 by fses             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	release_forks(t_philo *p)
{
	if (p->data->num_philos > 1)
	{
		pthread_mutex_unlock(&p->data->forks[p->right_fork]);
		pthread_mutex_unlock(&p->data->forks[p->left_fork]);
	}
	else
		pthread_mutex_unlock(&p->data->forks[p->left_fork]);
}

static int	should_abort_after_take(t_philo *p)
{
	if (!is_simulation_stopped(p->data))
		return (0);
	release_forks(p);
	return (1);
}

static void	mark_eating(t_philo *p, long long *start)
{
	print_status(p, "is eating");
	pthread_mutex_lock(&p->data->data_mutex);
	p->last_meal_time = get_time();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->data->data_mutex);
	*start = get_time();
}

static int	wait_eating(t_philo *p, long long start)
{
	while (get_time() - start < p->data->time_to_eat)
	{
		if (is_simulation_stopped(p->data))
		{
			release_forks(p);
			return (0);
		}
		usleep(100);
	}
	release_forks(p);
	return (1);
}

int	eat_meal(t_philo *philo)
{
	long long	start;

	if (!take_forks(philo))
		return (0);
	if (should_abort_after_take(philo))
		return (0);
	mark_eating(philo, &start);
	return (wait_eating(philo, start));
}
