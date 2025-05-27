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

#include "philosophers.h"

int	ft_initi_pthread(t_philo **philo)
{
	size_t	i;

	i = -1;
	while (i++ < philo->philosophers)
	{
		pthread_create()
	}
	
}

int	ft_start_simulation(t_philo **philo, t_table *table)
{
	if (!ft_init_pthread(philo))
		return (0);
}