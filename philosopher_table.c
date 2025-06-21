/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:19:39 by ischeini          #+#    #+#             */
/*   Updated: 2025/06/15 21:57:58 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_philo	*ft_put_philos(t_table *table)
{
	t_philo	*philos;
	int		i;

	philos = malloc(table->num_philos * sizeof(t_philo));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < table->num_philos)
	{
		philos[i].right_fork = &table->forks[(i + 1) % table->num_philos];
		philos[i].left_fork = &table->forks[i];
		philos[i].last_meal_time = 0;
		philos[i].meals_eaten = 0;
		philos[i].table = table;
		philos[i].id = i + 1;
		i++;
	}
	return (philos);
}

static t_fork	*ft_put_forks(t_table *table)
{
	t_fork	*forks;
	int		i;

	forks = malloc(table->num_philos * sizeof(t_fork));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&forks[i].mutex, NULL))
		{
			ft_error("Failed to initialize mutex.");
			free(forks);
			return (NULL);
		}
		forks[i].id = i;
		i++;
	}
	return (forks);
}

static int	ft_check_table(t_table *table, int argc)
{
	if (table->num_philos == -1)
		return (ft_error("Philosphers: Number invalid"));
	if (table->time_to_die == -1)
		return (ft_error("Die: Number invalid"));
	if (table->time_to_eat == -1)
		return (ft_error("Eat: Number invalid"));
	if (table->time_to_sleep == -1)
		return (ft_error("Sleep: Number invalid"));
	if (argc == 6)
	{
		if (table->max_meals == -1)
			return (ft_error("Philosopher: No need to eat"));
	}
	return (1);
}

t_table	*ft_init_table(t_table *table, int argc, char **args)
{
	table->num_philos = ft_atoi(args[1]);
	table->time_to_die = ft_atoi(args[2]);
	table->time_to_eat = ft_atoi(args[3]);
	table->time_to_sleep = ft_atoi(args[4]);
	if (argc == 6)
		table->max_meals = ft_atoi(args[5]);
	if (ft_check_table(table, argc) == -1)
		return (NULL);
	if (argc == 5)
		table->max_meals = -1;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->start_mutex, NULL);
	gettimeofday(&table->start_time, NULL);
	table->forks = ft_put_forks(table);
	if (!table->forks)
		return (NULL);
	table->philos = ft_put_philos(table);
	if (!table->philos)
	{
		ft_destroy_mutex(table);
		free(table->forks);
		return (NULL);
	}
	return (table);
}

/*static t_fork	*ft_forknew()
{
	t_fork	*fork;

	fork = malloc(1 * sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->table = 1;
	fork->next = NULL;
	return (fork);
}

static void	ft_lstadd_fork(t_fork **forks, t_fork *new)
{
	if (!forks[0])
	{
		forks[0] = new;
		return ;
	}
	new->next = forks[0];
	forks[0] = new;
}

static t_fork	**ft_put_forks(int philosophers)
{
	t_fork	**forks;
	t_fork	*next_forks;
	int	i;

	forks = (t_fork **)malloc(1 * sizeof(t_fork *));
	if (!forks)
		return (NULL);
	*forks = NULL;
	i = 0;
	while (i++ < philosophers)
	{
		next_forks = ft_forknew();
		if (!next_forks)
		{
			ft_lstclear_fork(forks, philosophers);
			return (NULL);
		}
		ft_lstadd_fork(forks, next_forks);
	}
	return (forks);
}

static int	ft_check_table(t_table *table, int argc)
{
	if (table->philosophers == 0)
		return (ft_error("Philosphers: Number invalid"));
	if (table->die == 0)
		return (ft_error("Die: Number invalid"));
	if (table->eat == 0)
		return (ft_error("Eat: Number invalid"));
	if (table->sleep == 0)
		return (ft_error("Sleep: Number invalid"));
	if (argc == 6)
	{
		if (table->times_to_eat == 0)
			return (ft_error("Philosopher: No need to eat"));
	}
	return (1);
}

t_table	*ft_init_table(int argc, char **args)
{
	t_table	*table;

	table = malloc(1 * sizeof(t_table));
	if (!table)
		return (NULL);
	table->philosophers = ft_atoi(args[1]);
	table->sleep = ft_atoi(args[4]);
	table->die = ft_atoi(args[2]);
	table->eat = ft_atoi(args[3]);
	if (argc == 6)
		table->times_to_eat = ft_atoi(args[5]);
	if (!ft_check_table(table, argc))
	{
		free(table);
		return (NULL);
	}
	if (argc == 5)
		table->times_to_eat = 0;
	table->forks = ft_put_forks(table->philosophers);
	if (!table->forks)
	{
		free(table);
		return (NULL);
	}
	return (table);
}*/