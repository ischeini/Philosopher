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
	return (1);
}

void	ft_can_grab_forks(t_philo *phi, __useconds_t milisec)
{
	struct timeval	tv;
	
	if (!pthread_mutex_lock(&phi->left_fork->mutex) &&
	!pthread_mutex_lock(&phi->right_fork->mutex))
	{
		gettimeofday(&tv, NULL);
		printf("%ld.%06ld %d has taken a fork\n",
		tv.tv_sec, tv.tv_usec, phi->soul->nbr);
		gettimeofday(&tv, NULL);
		printf("%ld.%06ld %d has taken a fork\n",
		tv.tv_sec, tv.tv_usec, phi->soul->nbr);
		if (ft_philo_alive(phi, time))
		{
			gettimeofday(&tv, NULL);
			printf("%ld.%06ld %d is eating\n",
			tv.tv_sec, tv.tv_usec, phi->soul->nbr);
			usleep(milisec);
		}
		pthread_mutex_unlock(&phi->right_fork->mutex);
		pthread_mutex_unlock(&phi->left_fork->mutex);
	}
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
	time->last_thing.tv_usec = time->initial.tv_usec - time->current.tv_usec;
	if (time->last_thing.tv_usec >= (phi->die * 1000))
	{
		printf("%ld %d died\n", time->last_thing.tv_usec, phi->soul->nbr);
		phi->soul->dead = 0;
		return (0);
	}
	return (1);
}