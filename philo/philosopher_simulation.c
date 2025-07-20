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

static void	ft_simulation(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	if (table->simulation_running)
	{
		pthread_mutex_lock(&table->get_time_mutex);
		philo->last_meal_time = ft_get_current_time(table);
		pthread_mutex_unlock(&table->get_time_mutex);
		ft_print_status(philo, "has taken a fork");
		ft_print_status(philo, "has taken a fork");
		ft_print_status(philo, "is eating");
		usleep(table->time_to_eat * 1000);
		pthread_mutex_lock(&table->get_time_mutex);
		philo->last_meal_time = ft_get_current_time(table);
		pthread_mutex_unlock(&table->get_time_mutex);
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
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = (t_table *)philo->table;
	if (!philo->table)
		return (NULL);
	pthread_mutex_lock(&table->start_mutex);
	pthread_mutex_unlock(&table->start_mutex);
	philo->last_meal_time = ft_get_current_time(table);
	if (philo->id % 2 == 0)
		usleep(table->time_to_eat * 900);
	if (table->simulation_running && (table->max_meals != 0)
		&& (table->time_to_die) != 0)
		ft_print_status(philo, "is thinking");
	while ((table->simulation_running && (table->max_meals != 0)
			&& (table->time_to_die) != 0 && table->num_philos != 1))
		ft_simulation(table, philo);
	usleep(table->time_to_die * 1000);
	return (NULL);
}

static t_table	*ft_is_dead(t_table *table, int i, int j)
{
	long	lm;

	while (++i < table->num_philos)
	{
		if (table->philos[i].meals_eaten < table->max_meals
			|| table->max_meals == -1)
		{
			j = 0;
			pthread_mutex_lock(&table->get_time_mutex);
			lm = ft_get_current_time(table) - table->philos[i].last_meal_time;
			pthread_mutex_unlock(&table->get_time_mutex);
			if (lm > table->time_to_die)
			{
				table->simulation_running = 0;
				pthread_mutex_lock(&table->print_mutex);
				printf("%.06ld %d died\n", ft_get_current_time(table),
					table->philos[i].id);
				pthread_mutex_unlock(&table->print_mutex);
				return (NULL);
			}
		}
	}
	if (j)
		table->simulation_running = 0;
	return (table);
}

void	*ft_monitor_routine(void *arg)
{
	t_table	*table;
	int		i;
	int		j;

	table = (t_table *)arg;
	pthread_mutex_init(&table->get_time_mutex, NULL);
	gettimeofday(&table->start_time, NULL);
	pthread_mutex_unlock(&table->start_mutex);
	usleep(table->time_to_die * 900);
	while (table->simulation_running)
	{
		i = -1;
		j = 1;
		if (!ft_is_dead(table, i, j))
			return (NULL);
	}
	return (NULL);
}
