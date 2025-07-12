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

void	ft_simulation(t_table *table)
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
			ft_simulate_philo(table);
	}
	ulseep(1000);
	pthread_create(table->dead, NULL, ft_monitor_dead, table);
	pthread_create(table->meals_eat, NULL, ft_monitor_meals_eat, table);
}



while (n < philo)
{
	pid = fork();
	while (1)
	{
		if (!pid)
			ft_check_death();
		else if (pid)
			ft_simulate_philo();
	}
}