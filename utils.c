/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fses <fses@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:19:17 by fses              #+#    #+#             */
/*   Updated: 2025/08/10 15:10:34 by fses             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_philo *philo, char *status)
{
	long long	time;
	int			simulation_ended;

	pthread_mutex_lock(&philo->data->end_mutex);
	simulation_ended = philo->data->simulation_end;
	pthread_mutex_unlock(&philo->data->end_mutex);
	if (simulation_ended)
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_time() - philo->data->start_time;
	printf("%lld %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_return(int ret)
{
	write(2, "Error: Invalid argument\n", 25);
	return (ret);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (ft_return(1));
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (ft_return(1));
		}
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0)
		return (ft_return(1));
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (ft_return(1));
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
