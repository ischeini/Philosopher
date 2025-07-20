/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus_simulation.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:19:51 by ischeini          #+#    #+#             */
/*   Updated: 2025/07/06 12:19:51 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static void	ft_print_status_eat(t_philo *philo, long time)
{
	sem_wait(philo->table->sem_print);
	printf("%.06ld %d has taken a fork\n", time, philo->id);
	printf("%.06ld %d has taken a fork\n", time, philo->id);
	printf("%.06ld %d is eating\n", time, philo->id);
	sem_post(philo->table->sem_print);
}

static void	ft_simulate_eat(t_table *table, t_philo *philo)
{
	long	time;

	ft_print_status(philo, "is thinking");
	sem_wait(table->sem_eat);
	time = ft_get_current_time(table);
	sem_wait(table->sem[philo->id]);
	philo->last_meal_time = time;
	ft_print_status_eat(philo, time);
	usleep(table->time_to_eat * 1000);
	sem_post(table->sem_eat);
	time = ft_get_current_time(table);
	philo->last_meal_time = time;
	sem_post(table->sem[philo->id]);
}

/*static void	*ft_monitor(void *arg)
{
	t_table	*table;
	t_philo	*philo;
	long	lm;

	table = (t_table *)arg;
	philo = (t_philo *)&table->philos[table->philos->id];
	while (philo->meals_eaten < table->max_meals || table->max_meals == -1)
	{
		lm = ft_get_current_time(table) - philo->last_meal_time;
		if (lm > table->time_to_die)
		{
			printf("%.06ld %d died\n", ft_get_current_time(table), philo->id);
			return (NULL);
		}
	}
	return (table);
}*/

void	ft_simulate_philo(t_table *table, int i)
{
	t_philo	*philo;

	philo = &table->philos[i];
	sem_wait(table->sem_start);
	gettimeofday(&table->start_time, NULL);
	//if (pthread_create(&philo->monitor, NULL, ft_monitor, table) != 0)
	//	sem_post(table->sem_dead);
	philo->last_meal_time = ft_get_current_time(table);
	while (philo->meals_eaten < table->max_meals)
	{
		ft_simulate_eat(table, philo);	
		ft_print_status(philo, "is sleeping");
		usleep(table->time_to_sleep * 1000);
		philo->meals_eaten++;
	}
	while (1)
		usleep(100);
}

void	ft_start_simulation(t_table *table)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i++ < table->num_phi)
	{
		pid = fork();
		if (pid < 0)
			break ;
		else if (pid == 0)
			ft_simulate_philo(table, (i - 1));
	}
	usleep(table->num_phi * 1000);
	while (i-- >= 0)
		sem_post(table->sem_start);
	waitpid(pid, NULL, 0);
	//pthread_create(table->dead, NULL, ft_monitor_dead, table);
	//pthread_create(table->meals_eat, NULL, ft_monitor_meals_eat, table);
}
