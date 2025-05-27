/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:51:26 by ischeini          #+#    #+#             */
/*   Updated: 2025/05/26 15:51:26 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_philo_alive(t_philo *philo)
{
	t_philo	*tmp;
	int		i;

	tmp = philo;
	i = tmp->soul->philosophers;
	if (!tmp->soul->dead)
		return (0);
	else
		tmp = tmp->next;
	while (i != tmp->soul->philosophers)
	{
		if (!tmp->soul->dead)
			return (0);
		else
			tmp = tmp->next;
	}
	return (1);
}