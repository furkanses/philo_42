/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fses <fses@student.42kocaeli.com.tr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:36:21 by fses              #+#    #+#             */
/*   Updated: 2025/08/10 12:40:42 by fses             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long long		last_meal_time;
	int				meals_eaten;
	int				is_waiting_for_forks;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		start_time;
	int				simulation_end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	data_mutex;
	t_philo			*philos;
}					t_data;

int					init_data(t_data *data, int argc, char **argv);
int					init_philos(t_data *data);
int					init_mutexes(t_data *data);
int					cleanup(t_data *data, int ret);
void				*philosopher_routine(void *arg);
void				*monitor_routine(void *arg);
int					eat_meal(t_philo *philo);
int					dynamic_think(t_philo *philo);
int					is_simulation_stopped(t_data *data);
void				wait_for(long long time, t_data *data, t_philo *philo,
						int is_eating);
long long			get_time(void);
void				print_status(t_philo *philo, char *status);
int					check_death(t_data *data);
int					check_args(int argc, char **argv);
int					ft_atoi(const char *str);
void				set_waiting(t_philo *p, int v);
void				pick_order(t_philo *p, pthread_mutex_t **first,
						pthread_mutex_t **second);
int					abort_now(t_philo *p, pthread_mutex_t *a,
						pthread_mutex_t *b);
int					handle_single(t_philo *p);
int					take_forks(t_philo *philo);
long long			get_last_meal(t_data *data, int i);
int					all_philos_met_goal(t_data *data);

#endif