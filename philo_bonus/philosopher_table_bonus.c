/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_table_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 13:11:52 by ischeini          #+#    #+#             */
/*   Updated: 2025/06/29 13:11:52 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static t_table	*ft_create_sem(t_table *table)
{
	table->sem_start = sem_open(ft_sem_name(PH_SEM_START), O_CREAT, 0660, 1);
	if (table->sem_start == SEM_FAILED)
		return (ft_sem_error(PH_SEM_OPEN, table, 1));
	table->sem_print = sem_open(ft_sem_name(PH_SEM_PRINT), O_CREAT, 0660, 1);
	if (table->sem_print == SEM_FAILED)
		return (ft_sem_error(PH_SEM_OPEN, table, 1));
	table->sem_forks = sem_open(ft_sem_name(PH_SEM_FORKS), O_CREAT, 0660,
			(table->num_phi / 2));
	if (table->sem_forks == SEM_FAILED)
		return (ft_sem_error(PH_SEM_OPEN, table, 1));
	table->sem_dead = sem_open(ft_sem_name(PH_SEM_DEAD), O_CREAT, 0660, table->num_phi);
	if (table->sem_dead == SEM_FAILED)
		return (ft_sem_error(PH_SEM_OPEN, table, 1));
	table->sem_wait = sem_open(ft_sem_name(PH_SEM_WAI), O_CREAT, 0660, 1);
	if (table->sem_wait == SEM_FAILED)
		return (ft_sem_error(PH_SEM_OPEN, table, 1));
	table->sem_eat = sem_open(ft_sem_name(PH_SEM_EAT), O_CREAT, 0660,
			(table->num_phi / 2));
	if (table->sem_eat == SEM_FAILED)
		return (ft_sem_error(PH_SEM_OPEN, table, 1));
	table->sem_meals_eat = sem_open(ft_sem_name(PH_SEM_MEALS), O_CREAT,
			0660, table->num_phi);
	if (table->sem_meals_eat == SEM_FAILED)
		return (ft_sem_error(PH_SEM_OPEN, table, 1));
	return (table);
}

static int	ft_check_table(t_table *table, int argc)
{
	if (table->num_phi == -1)
		return (ft_error_int(PH_INV_PHILO));
	if (table->time_to_die == -1)
		return (ft_error_int(PH_INV_DEATH));
	if (table->time_to_eat == -1)
		return (ft_error_int(PH_INV_EAT));
	if (table->time_to_sleep == -1)
		return (ft_error_int(PH_INV_SLEEP));
	if (argc == 6)
	{
		if (table->max_meals == -1)
			return (ft_error_int(PH_INV_MEALS));
		if (table->max_meals == 0)
			return (ft_error_int(PH_MEALS_ZERO));
	}
	return (1);
}

static t_philo	*ft_create_phi(t_table *table)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * table->num_phi);
	if (!philos)
	{
		ft_sem_error(PH_SEM_OPEN, table, 0);
		ft_free(table);	
		return (ft_error_null(PH_MALLOC));
	}
	while (i < table->num_phi)
	{
		philos[i].table = table;
		philos[i].last_meal_time = 0;
		philos[i].meals_eaten = 0;
		philos[i].id = i + 1;
		i++;
	}
	return (philos);
}

t_table	*ft_init_table(int argc, char **args)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (ft_error_null(PH_MALLOC));
	table->num_phi = ft_atoi(args[1]);
	table->time_to_die = ft_atoi(args[2]);
	table->time_to_eat = ft_atoi(args[3]);
	table->time_to_sleep = ft_atoi(args[4]);
	if (argc == 6)
		table->max_meals = ft_atoi(args[5]);
	if (ft_check_table(table, argc) == -1)
		return (NULL);
	if (argc == 5)
		table->max_meals = -1;
	ft_sem_unlink();
	if (!ft_create_sem(table))
	{
		ft_free(table);	
		return (NULL);
	}
	table->philos = ft_create_phi(table);
	if (!table->philos)
		return (NULL);
	return (table);
}
