/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_fork1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fses <fses@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:23:17 by fses              #+#    #+#             */
/*   Updated: 2025/08/10 12:37:53 by fses             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	starved(t_philo *p)
{
	long long	lm;
	long long	now;

	pthread_mutex_lock(&p->data->data_mutex);
	lm = p->last_meal_time;
	pthread_mutex_unlock(&p->data->data_mutex);
	if (lm == -1)
		return (0);
	now = get_time();
	return (now - lm >= p->data->time_to_die);
}

static int	fail_if_starved_after_first(t_philo *p, pthread_mutex_t *first)
{
	if (!starved(p))
		return (0);
	pthread_mutex_unlock(first);
	set_waiting(p, 0);
	return (1);
}

static int	fail_if_starved_after_both(t_philo *p, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	if (!starved(p))
		return (0);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	set_waiting(p, 0);
	return (1);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->data->num_philos == 1)
		return (handle_single(philo));
	set_waiting(philo, 1);
	pick_order(philo, &first, &second);
	pthread_mutex_lock(first);
	if (abort_now(philo, first, NULL) || fail_if_starved_after_first(philo,
			first))
		return (0);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(second);
	if (abort_now(philo, first, second) || fail_if_starved_after_both(philo,
			first, second))
		return (0);
	print_status(philo, "has taken a fork");
	set_waiting(philo, 0);
	return (1);
}
