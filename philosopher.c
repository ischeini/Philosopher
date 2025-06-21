/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:03:18 by ischeini          #+#    #+#             */
/*   Updated: 2025/05/10 11:03:18 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **args)
{
	pthread_t	monitor;
	t_table		table;
	int			i;

	if (argc <= 4 || argc >= 7)
		return (ft_error("Argv: Amount"));
	if (!ft_init_table(&table, argc, args))
		return (1);
	pthread_mutex_lock(&table.start_mutex);
	i = 0;
	while (i < table.num_philos)
	{
		pthread_create(&table.philos[i].thread, NULL, ft_philo_routine, &table);
		i++;
	}
	pthread_create(&monitor, NULL, ft_monitor_routine, &table);
	usleep(1000);
	pthread_mutex_unlock(&table.start_mutex);
	i = 0;
	while (i < table.num_philos)
	{
		pthread_join(table.philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	ft_destroy_mutex(&table);
	free(table.philos);
	free(table.forks);
}

/*int	main(int argc, char **args)
{
	t_philo	**philos;
	t_table	*table;
	int		i;

	i = 0;
	if (argc <= 4 || argc >= 7)
		return (ft_error("Argv: Amount"));
	if (!ft_check_args(args))
		return (1);
	table = ft_init_table(argc, args);
	if (!table)
		return (1);
	philos = ft_start_philosophers(table);
	if (!philos)
	{
		free(table);
		return (1);
	}
	ft_start_simulation(philos, table);
	ft_lstclear_fork(table->forks, table->philosophers);
	ft_lstclear_soul(philos, table->philosophers);
	free(table);
	return (i);
}*/