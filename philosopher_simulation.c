/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_simulation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:12:57 by ischeini          #+#    #+#             */
/*   Updated: 2025/05/26 14:12:57 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = (t_table *)philo->table;
	if (!philo->table)
	{
		printf("philo->table no existe\n");
		return (NULL);
	}
	pthread_mutex_lock(&table->start_mutex);
	pthread_mutex_unlock(&table->start_mutex);
	gettimeofday(&table->start_time, NULL);
	philo->last_meal_time = ft_get_current_time(table);
	philo->is_eating = 0;
	philo->priority = 1;
	if (table->simulation_running && (table->max_meals != 0) && (table->time_to_die) != 0)
		ft_print_status(philo, "is thinking");
	while (table->simulation_running && (table->max_meals != 0) && (table->time_to_die) != 0 && table->num_philos != 1)
	{
		if (philo->priority)
		{
			pthread_mutex_lock(&philo->left_fork->mutex);
			pthread_mutex_lock(&philo->right_fork->mutex);
			philo->priority = 0;
		}
		if (table->simulation_running)
		{
			philo->is_eating = 1;
			ft_print_status(philo, "has taken a fork");
			ft_print_status(philo, "has taken a fork");
			ft_print_status(philo, "is eating");
			usleep(table->time_to_eat * 1000);
			philo->last_meal_time = ft_get_current_time(table);
			philo->is_eating = 0;
		}
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		if (table->simulation_running)
		{
			ft_print_status(philo, "is sleeping");
			usleep(table->time_to_sleep * 1000);
			ft_print_status(philo, "is thinking");
			philo->meals_eaten++;
		}
		if (table->max_meals != -1 && philo->meals_eaten >= table->max_meals)
			break ;
	}
	return (NULL);
}

void	*ft_monitor_routine(void *arg)
{
	long	lm;
	t_table	*table;
	int		i;
	int		j;

	table = (t_table *)arg;
	usleep(table->time_to_die * 900);
	while (table->simulation_running)
	{
		i = 0;
		j = 1;
		while (i < table->num_philos)
		{
			if (table->philos[i].meals_eaten < table->max_meals || table->max_meals == -1)
			{
				j = 0;
				lm = ft_get_current_time(table) - table->philos[i].last_meal_time;
				if (lm > table->time_to_die && !table->philos[i].is_eating)
				{
					table->simulation_running = 0;
					pthread_mutex_lock(&table->print_mutex);
					printf("%.06ld %d died\n", ft_get_current_time(table),
					table->philos[i].id);
					pthread_mutex_unlock(&table->print_mutex);
					return (NULL);
				}
			}
			if (i == 0)
			{
				if (!table->philos[table->num_philos - 1].priority && !table->philos[i + 1].priority)
					table->philos[i].priority = 1;
			}
			else
			{
				if (!table->philos[i - 1].priority && !table->philos[i + 1].priority)
					table->philos[i].priority = 1;
			}
			i++;
		}
		if (j)
			table->simulation_running = 0;
	}
	return (NULL);
}
