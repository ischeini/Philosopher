/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:34:21 by ischeini          #+#    #+#             */
/*   Updated: 2025/05/25 18:15:09 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_lstclear_fork(t_fork **fork)
{
	t_fork	*tmp;

	while (*fork)
	{
		tmp = fork[0]->next;
		free(fork[0]);
		fork[0] = tmp;
	}
	fork[0] = NULL;
	free(fork);
}

void	ft_lstclear_soul(t_philo **philo)
{
	t_philo	*tmp;

	while (*philo)
	{
		tmp = philo[0]->next;
		free(philo[0]->soul);
		free(philo[0]);
		philo[0] = tmp;
	}
	philo[0] = NULL;
	free(philo);
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (0);
}
