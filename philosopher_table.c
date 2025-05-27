/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:19:39 by ischeini          #+#    #+#             */
/*   Updated: 2025/05/27 18:05:39 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_fork	*ft_forknew()
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
			ft_lstclear_fork(forks);
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
}