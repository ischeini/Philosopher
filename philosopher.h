/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:03:45 by ischeini          #+#    #+#             */
/*   Updated: 2025/05/10 11:03:45 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
}	t_fork;

typedef struct s_philo
{
	pthread_t		thread;
	struct s_table	*table;
	t_fork			*right_fork;
	t_fork			*left_fork;
	long			last_meal_time;
	int				meals_eaten;
	int				is_eating;
	int				priority;
	int				id;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	start_mutex;
	struct timeval	start_time;
	struct timeval	dif;
	t_philo			*philos;
	long			time_to_sleep;
	long			time_to_die;
	long			time_to_eat;
	int				simulation_running;
	int				num_philos;
	int				max_meals;
	t_fork			*forks;
}	t_table;

int		ft_error(char *str);

int		ft_atoi(const char *str);

void	ft_destroy_mutex(t_table *table);

t_table	*ft_init_table(t_table *table, int argc, char **args);

void	*ft_monitor_routine(void *arg);

void	*ft_philo_routine(void *arg);

long	ft_get_current_time(t_table *table);

void	ft_print_status(t_philo *philos, const char *status);

#endif
