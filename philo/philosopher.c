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

	if (argc < 5 || argc > 6)
		return (ft_error("Argv: Amount"));
	if (!ft_init_table(&table, argc, args))
		return (1);
	i = -1;
	while (++i < table.num_philos)
	{
		if (pthread_create(&table.philos[i].thread, NULL,
				ft_philo_routine, &table.philos[i]) != 0)
			table.simulation_running = 0;
	}
	if (pthread_create(&monitor, NULL, ft_monitor_routine, &table) != 0)
		table.simulation_running = 0;
	i = 0;
	while (i < table.num_philos)
		pthread_join(table.philos[i++].thread, NULL);
	pthread_join(monitor, NULL);
	ft_destroy_mutex(&table);
	free(table.philos);
	free(table.forks);
	return (0);
}
