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

static int	ft_infinite(t_philo *soul, t_time *time)
{
	while (ft_philo_alive(soul, time))
	{
		ft_can_grab_forks(soul, time);
		ft_sleep(soul, time);
		ft_think(soul, time);
	}
	free(time);
	return (1);
}

static int	ft_eat_until_finish(t_philo *soul, t_time *time)
{
	int	j;

	j = 0;
	while (j < soul->times_to_eat && ft_philo_alive(soul, time))
	{
		ft_can_grab_forks(soul, time);
		j++;
		ft_sleep(soul, time);
		ft_think(soul, time);
	}
	return (1);
}

static void	*ft_start(void *soul)
{
	t_philo	*tmp;
	t_time	*time;

	tmp = (t_philo *)soul;
	time = malloc((sizeof(t_time)));
	if (!time)
		return (0);
	gettimeofday(&time->initial, NULL);
	ft_think(soul, time);
	if (tmp->times_to_eat)
	{
		if (!ft_eat_until_finish(tmp, time))
			return (NULL);
	}
	else
		if (!ft_infinite(tmp, time))
			return (NULL);
	return (soul);
}

void	ft_start_simulation(t_philo **philo, t_table *table)
{
	t_philo	*tmp;
	int		i;	

	tmp = philo[0];
	tmp->soul->philosophers = malloc(sizeof(pthread_t) * table->philosophers);
	if (!tmp->soul->philosophers)
		return ;
	i = 0;
	while (i < table->philosophers)
	{
		if (pthread_create(&philo[0]->soul->philosophers[i++], NULL, &ft_start, (void *)tmp))
		{
			free(tmp->soul->philosophers);
			return ;
		}
		tmp = tmp->next;
	}
	i = 0;
	while (i < table->philosophers)
		pthread_join(tmp->soul->philosophers[i++], NULL);
	free(tmp->soul->philosophers);
}