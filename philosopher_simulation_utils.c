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

void	ft_sleep(t_philo *phi, __useconds_t milisec)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	printf("%d, the philo %d is sleeping\n", tv, phi->soul->nbr);
	usleep(milisec);
}

void	ft_can_grab_forks(t_philo *phi, __useconds_t milisec)
{
	struct timeval	tv;
	
	pthread_mutex_lock(phi->right_fork->mutex->loked);
	gettimeofday(&tv, NULL);
	printf("%d, the philo %d has taken a fork\n", tv, phi->soul->nbr);
	pthread_mutex_lock(phi->left_fork->mutex->loked);
	gettimeofday(&tv, NULL);
	printf("%d, the philo %d has taken a fork\n", tv, phi->soul->nbr);
	if (ft_philo_alive(phi))
	{
		gettimeofday(&tv, NULL);
		printf("%d, the philo %d is eating\n", tv, phi->soul->nbr);
		usleep(milisec);
		phi->times_to_eat++;
	}
	pthread_mutex_unlock(phi->right_fork->mutex->loked);
	pthread_mutex_unlock(phi->left_fork->mutex->loked);
}

void	ft_think(t_philo *phi)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	printf("%d, the philo %d is thinking\n", tv, phi->soul->nbr);
}

int	ft_philo_alive(t_philo *phi)
{
	struct timeval	tv;

	phi->soul->last_meal = gettimeofday(&tv, NULL);
	if (phi->soul->last_meal >= phi->die)
	{
		printf("%d, the philosopher %d died\n", tv, phi->soul->nbr);
		phi->soul->die = 0;
		return (0);
	}
	return (1);
}