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

long	ft_get_current_time(t_table *table)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - table->start_time.tv_sec) * 1000
	+ (current.tv_usec - table->start_time.tv_usec) / 1000);
}

void	ft_print_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%.06ld %d %s\n", ft_get_current_time(philo->table), philo->id, status);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

/*long	ft_calculate(struct timeval *current)
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
	misec -= (phi->unused * 2);
	printf("%.06ld %d is sleeping\n", misec, phi->soul->nbr);
	usleep(phi->sleep * 1000);
	return (1);
}

int	ft_can_grab_forks(t_philo *phi, t_time *time)
{
	long	misec;

	pthread_mutex_lock(&phi->left_fork->mutex);
	pthread_mutex_lock(&phi->right_fork->mutex);
	if (ft_philo_alive(phi, time))
	{
		gettimeofday(&time->current, NULL);
		misec = ft_calculate(&time->current) - ft_calculate(&time->initial);
		misec -= (phi->unused * 2);
		printf("%.06ld %d has taken a fork\n", misec, phi->soul->nbr);
		printf("%.06ld %d has taken a fork\n", misec, phi->soul->nbr);
		printf("%.06ld %d is eating\n", misec, phi->soul->nbr);
		usleep(phi->eat * 1000);
		pthread_mutex_unlock(&phi->right_fork->mutex);
		pthread_mutex_unlock(&phi->left_fork->mutex);
		gettimeofday(&time->last_meal, NULL);
		ft_sleep(phi, time);
	}
	else
	{
		gettimeofday(&time->current, NULL);
		misec = ft_calculate(&time->current) - ft_calculate(&time->last_meal);
		pthread_mutex_unlock(&phi->right_fork->mutex);
		pthread_mutex_unlock(&phi->left_fork->mutex);
		printf("%.06ld %d die\n", misec, phi->soul->nbr);
		return (0);
	}
	return (1);
}

void	ft_think(t_philo *phi, t_time *time)
{
	long	misec;

	gettimeofday(&time->current, NULL);
	misec = ft_calculate(&time->current) - ft_calculate(&time->initial);
	misec -= (phi->unused * 2);
	if (misec < 0)
		misec = 0; 
	printf("%.6ld %d is thinking\n", misec, phi->soul->nbr);
}

int	ft_philo_alive(t_philo *phi, t_time *time)
{
	long	misec;

	if (!phi->next->soul->dead || !phi->back->soul->dead)
		return (0);
	gettimeofday(&time->current, NULL);
	misec = ft_calculate(&time->current) - ft_calculate(&time->last_meal);
	misec -= (phi->unused * 2);
	if (misec >= (phi->die))
	{
		phi->soul->dead = 0;
		phi->unused = misec;
		return (0);
	}
	return (1);
}*/