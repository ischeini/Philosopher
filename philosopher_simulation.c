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
	while (table->simulation_running)
	{
		ft_print_status(philo, "is thinking");
		if (table->simulation_running && pthread_mutex_lock(&philo->left_fork->mutex))
			ft_print_status(philo, "has taken a fork");
		if (table->simulation_running && pthread_mutex_lock(&philo->right_fork->mutex))
			ft_print_status(philo, "has taken a fork");
		if (table->simulation_running)
		{
			ft_print_status(philo, "is eating");
			usleep(table->time_to_eat * 1000);
		}
		philo->last_meal_time = ft_get_current_time(table);
		pthread_mutex_unlock(&philo->left_fork->mutex);
		pthread_mutex_unlock(&philo->right_fork->mutex);
		philo->meals_eaten++;
		if (table->max_meals != -1 && philo->meals_eaten >= table->max_meals)
			break ;
		if (table->simulation_running)
		{
			ft_print_status(philo, "is sleeping");
			usleep(table->time_to_sleep * 1000);
		}
	}
	return (NULL);
}

void	*ft_monitor_routine(void *arg)
{
	long	lm;
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (table->simulation_running)
	{
		usleep(100);
		i = 0;
		while (i < table->num_philos)
		{
			lm = ft_get_current_time(table) - table->philos[i].last_meal_time;
			if (lm > table->time_to_die)
			{
				pthread_mutex_lock(&table->print_mutex);
				printf("%.06ld %d died\n", ft_get_current_time(table),
				table->philos[i].id);
				table->simulation_running = 0;
				pthread_mutex_unlock(&table->print_mutex);
				return (NULL);
			}
		}
	}
	return (NULL);
}

/*static int	ft_infinite(t_philo *soul, t_time *time)
{
	gettimeofday(&time->initial, NULL);
	time->last_meal.tv_sec = time->initial.tv_sec;
	time->last_meal.tv_usec = time->initial.tv_usec;
	ft_think(soul, time);
	while (ft_philo_alive(soul, time))
	{
		if (!ft_can_grab_forks(soul, time))
			break ;
		ft_think(soul, time);
	}
	free(time);
	return (1);
}

static int	ft_eat_until_finish(t_philo *soul, t_time *time)
{
	int		j;

	j = 0;
	gettimeofday(&time->initial, NULL);
	time->last_meal.tv_sec = time->initial.tv_sec;
	time->last_meal.tv_usec = time->initial.tv_usec;
	ft_think(soul, time);
	while (j < soul->times_to_eat && ft_philo_alive(soul, time))
	{
		if (!ft_can_grab_forks(soul, time))
			break ;
		j++;
		ft_think(soul, time);
	}
	free(time);
	return (1);
}

static void	*ft_start(void *soul)
{
	t_philo	*tmp;
	t_time	*time;

	tmp = (t_philo *)soul;
	time = malloc((sizeof(t_time)));
	if (!time)
		return (0);
	if (tmp->times_to_eat)
	{
		if (!ft_eat_until_finish(tmp, time))
			return (NULL);
	}
	else
		if (!ft_infinite(tmp, time))
			return (NULL);
	return (soul);
}

void	ft_start_simulation(t_philo **philo, t_table *table)
{
	t_philo	*tmp;
	int		i;	

	tmp = philo[0];
	tmp->soul->philosophers = malloc(sizeof(pthread_t) * table->philosophers);
	if (!tmp->soul->philosophers)
		return ;
	i = 0;
	table->philo = philo;
	i = 0;
	while (i < table->philosophers)
	{
		if (pthread_create(&philo[0]->soul->philosophers[i++], NULL, &ft_start, (void *)tmp))
		{
			free(tmp->soul->philosophers);
			return ;
		}
		tmp = tmp->next;
	}
	i = 0;
	while (i < table->philosophers)
		pthread_join(tmp->soul->philosophers[i++], NULL);
	free(tmp->soul->philosophers);
}*/