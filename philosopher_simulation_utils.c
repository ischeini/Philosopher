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

long	ft_calculate(struct timeval *current)
{
	long	difference;

	difference = current->tv_sec * 1000;
	difference += current->tv_usec / 1000;
	return (difference);
}

int	ft_sleep(t_philo *phi, t_time *time)
{
	long	misec;

	gettimeofday(&time->current, NULL);
	misec = ft_calculate(&time->current) - ft_calculate(&time->initial);
	printf("%.010ld %d is sleeping\n", misec, phi->soul->nbr);
	usleep(phi->sleep * 1000);
	return (1);
}

int	ft_can_grab_forks(t_philo *phi, t_time *time)
{
	long	misec;

	if (!pthread_mutex_lock(&phi->left_fork->mutex) &&
	!pthread_mutex_lock(&phi->right_fork->mutex))
	{
		if (ft_philo_alive(phi, time))
		{
			misec = ft_calculate(&time->current) - ft_calculate(&time->initial);
			printf("%.010ld %d has taken a fork\n", misec, phi->soul->nbr);
			misec = ft_calculate(&time->current) - ft_calculate(&time->initial);
			printf("%.010ld %d has taken a fork\n", misec, phi->soul->nbr);
			misec = ft_calculate(&time->current) - ft_calculate(&time->initial);
			printf("%.010ld %d is eating\n", misec, phi->soul->nbr);
			usleep(phi->eat * 1000);
			pthread_mutex_unlock(&phi->right_fork->mutex);
			pthread_mutex_unlock(&phi->left_fork->mutex);
			gettimeofday(&time->last_meal, NULL);
			ft_sleep(phi, time);
		}
		else
		{
			pthread_mutex_unlock(&phi->right_fork->mutex);
			pthread_mutex_unlock(&phi->left_fork->mutex);
			return (0);
		}
	}
	return (1);
}

void	ft_think(t_philo *phi, t_time *time)
{
	long	misec;

	gettimeofday(&time->current, NULL);
	misec = ft_calculate(&time->current) - ft_calculate(&time->initial);
	printf("%.10ld %d is thinking\n", misec, phi->soul->nbr);
}

int	ft_philo_alive(t_philo *phi, t_time *time)
{
	long	misec;

	if (!phi->next->soul->dead || !phi->back->soul->dead)
		return (0);
	gettimeofday(&time->current, NULL);
	misec = ft_calculate(&time->current) - ft_calculate(&time->last_meal);
	if (misec >= (phi->die))
	{
		phi->soul->dead = 0;
		time->dead = misec;
		return (0);
	}
	return (1);
}