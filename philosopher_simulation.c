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

#include "philosopher.h"

static int	ft_infinite(t_philo *soul)
{
	__useconds_t	milisec;

	while (ft_philo_alive(soul))
	{
		ft_think(soul);
		milisec = soul->eat * 1000;
		ft_can_grab_forks(soul, milisec);
		if (soul->soul->dead == 0)
			return (1);
		milisec = soul->sleep * 1000;
		usleep(milisec);
	}
	return (1);
}

static int	ft_eat_until_finish(t_philo *soul)
{
	__useconds_t	milisec;
	int	i;

	i = 0;
	while (i < soul->times_to_eat && ft_philo_alive(soul))
	{
		ft_think(soul);
		milisec = soul->eat * 1000;
		ft_can_grab_forks(soul, milisec);
		if (soul->soul->dead == 0)
			return (1);
		milisec = soul->sleep * 1000;
		usleep(milisec);
	}
	return (1);
}

static void	*ft_start(void *soul)
{
	t_philo			*tmp;

	tmp = (t_philo *)soul;
	if (tmp->times_to_eat)
		ft_eat_until_finish(tmp);
	else
		ft_infinite(tmp);
}

void	ft_start_simulation(t_philo **philo, t_table *table)
{
	t_philo	*tmp;
	int		i;	

	tmp = philo[0];
	i = 0;
	while (i++ < table->philosophers)
	{
		pthread_create(tmp->soul->philosophers, NULL, &ft_start, (void *)tmp);
		tmp = tmp->next;
	}
	tmp = philo[0];
	while (tmp)
	{
		if (!tmp->soul->dead)
			break ;
		tmp = tmp->next;
	}
}