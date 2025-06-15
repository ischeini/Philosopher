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

void	ft_sleep(t_philo *phi, t_time *time)
{
	gettimeofday(&time->current, NULL);
	time->last_thing.tv_usec = time->initial.tv_usec - time->current.tv_usec;
	printf("%ld %d died\n", time->last_thing.tv_usec, phi->soul->nbr);
	usleep((phi->sleep * 1000));
	gettimeofday(&time->current, NULL);
	time->initial.tv_usec = time->current.tv_usec - time->current.tv_usec;
}

int	ft_can_grab_forks(t_philo *phi, t_time *time)
{
	if (!pthread_mutex_lock(&phi->left_fork->mutex) &&
	!pthread_mutex_lock(&phi->right_fork->mutex))
	{
		if (ft_philo_alive(phi, time))
		{
			gettimeofday(&time->current, NULL);
			time->last_thing.tv_usec = time->current.tv_usec - time->initial.tv_usec;
			printf("%.06ld %d has taken a fork\n", time->last_thing.tv_usec, phi->soul->nbr);
			gettimeofday(&time->current, NULL);
			time->last_thing.tv_usec = time->current.tv_usec - time->initial.tv_usec;
			printf("%.06ld %d has taken a fork\n", time->last_thing.tv_usec, phi->soul->nbr);
			gettimeofday(&time->current, NULL);
			time->last_thing.tv_usec = time->current.tv_usec - time->initial.tv_usec;
			printf("%.06ld %d is eating\n", time->last_thing.tv_usec, phi->soul->nbr);
			usleep(phi->eat * 1000);
		}
		else
			return (0);
		pthread_mutex_unlock(&phi->right_fork->mutex);
		pthread_mutex_unlock(&phi->left_fork->mutex);
		gettimeofday(&time->last_meal, NULL);
	}
	return (1);
}

void	ft_think(t_philo *phi, t_time *time)
{
	gettimeofday(&time->current, NULL);
	time->last_thing.tv_usec = time->current.tv_usec - time->initial.tv_usec;
	printf("%ld, %d is thinking\n", time->last_thing.tv_usec, phi->soul->nbr);
}

int	ft_philo_alive(t_philo *phi, t_time *time)
{
	gettimeofday(&time->current, NULL);
	time->last_thing.tv_usec = time->current.tv_usec - time->last_meal.tv_usec;
	if (time->last_thing.tv_usec >= (phi->die * 1000))
	{
		time->last_thing.tv_usec = time->current.tv_usec - time->initial.tv_usec;
		printf("%ld %d died\n", time->last_thing.tv_usec, phi->soul->nbr);
		phi->soul->dead = 0;
		return (0);
	}
	return (1);
}