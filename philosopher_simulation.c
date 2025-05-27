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
	struct timeval	tv;
	__useconds_t	milisec;
	int	i;

	i = 0;
	while (ft_philo_alive(soul))
	{
		soul->soul->last_meal = gettimeofday(&tv, NULL);
		if (soul->soul->last_meal >= soul->die)
			ft_philo_die(soul);
		if (ft_can_grab_forks(soul))
			ft_start_eat(soul);
		milisec = soul->eat * 1000;
		if (ft_you_eat(soul))
		{
			soul->times_to_eat++;
			usleep(milisec);
		}
		milisec = soul->sleep * 1000;
		if (ft_you_finish_eat(soul))
			usleep(milisec);
		if (ft_if_you_sleep(soul))
			ft_start_think(soul);
	}
	return (1);
}

static int	ft_eat_until_finish(t_philo *soul)
{
	struct timeval	tv;
	__useconds_t	milisec;
	int	i;

	i = 0;
	while (i < soul->times_to_eat && ft_philo_alive(soul))
	{
		soul->soul->last_meal = gettimeofday(&tv, NULL);
		if (soul->soul->last_meal >= soul->die)
			ft_philo_die(soul);
		if (ft_can_grab_forks(soul))
			ft_start_eat(soul);
		milisec = soul->eat * 1000;
		if (ft_you_eat(soul))
		{
			soul->times_to_eat++;
			usleep(milisec);
		}
		milisec = soul->sleep * 1000;
		if (ft_you_finish_eat(soul))
			usleep(milisec);
		if (ft_if_you_sleep(soul))
			ft_start_think(soul);
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

int	ft_initi_pthread(t_philo **philo, t_table *table)
{
	t_philo	*tmp;
	int		i;	

	tmp = philo[0];
	i = -1;
	while (i++ < table->philosophers)
	{
		pthread_create(tmp->soul->philosophers, NULL, &ft_start, (void *)tmp);
		tmp = tmp->soul;
	}
	
}

int	ft_start_simulation(t_philo **philo, t_table *table)
{
	if (!ft_init_pthread(philo, table))
		return (0);
}