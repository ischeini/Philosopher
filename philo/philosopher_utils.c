/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:43:00 by ischeini          #+#    #+#             */
/*   Updated: 2025/05/10 11:43:00 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (-1);
}

void	ft_destroy_mutex(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->start_mutex);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_destroy(&table->forks[i].mutex);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	if (str[0] == '\0')
		return (-1);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (ft_error("Negative number"));
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > (INT_MAX - (str[i] - '0')) / 10)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (result);
}

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
	if (philo->table->simulation_running)
		printf("%.06ld %d %s\n",
			ft_get_current_time(philo->table), philo->id, status);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
