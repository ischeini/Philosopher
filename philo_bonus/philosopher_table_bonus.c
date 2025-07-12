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

static sem_t	ft_create_sem(t_table *table, char *str, int num, int pos)
{
	table->sem[pos] = sem_open(str, O_CREATE, 0644, num);
	if (table->sem[pos] == SEM_FAILED)
		return (NULL);
	table->str[pos] = str;
	return (table->sem[pos]); 
}

static int	ft_check_table(t_table *table, int argc)
{
	if (table->num_philos == -1)
		return (ft_error(PH_INV_PHILO));
	if (table->time_to_die == -1)
		return (ft_error(PH_INV_DEATH));
	if (table->time_to_eat == -1)
		return (ft_error(PH_INV_EAT));
	if (table->time_to_sleep == -1)
		return (ft_error(PH_INV_SLEEP));
	if (argc == 6)
	{
		if (table->max_meals == -1)
			return (ft_error(PH_INV_MEALS));
		if (table->max_meals == 0)
			return (ft_error(PH_MEALS_ZERO));
	}
	table->str = malloc(sizeof(char *) * 5);
	if (!table->str)
		return (-1);
	table->simulation_running = 1;
	return (1);
}

static t_philo	ft_create_phi(t_table *table)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * table->num_phi);
	if (!philos)
		return (NULL);
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

t_table	*ft_init_table(t_table *table, int argc, char **args)
{
	t_sem	*sem;

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
	table->sem = malloc(sizeof(sem_t) * 6);
	if (!sem)
		return (NULL);
	if (!ft_create_sem(table, "/start_sem", 0, 0) ||
		!ft_create_sem(table, "/print_sem", 1, 1) == NULL)
        return (ft_destroy_sem(table->sem, table-sem->names));
	table->philos = ft_create_phi(table);
	if (!table->philos)
		return (ft_destroy_sem(table->sem, table-sem->names));
	return (table);
}