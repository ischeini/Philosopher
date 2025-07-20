/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_uils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:07:10 by ischeini          #+#    #+#             */
/*   Updated: 2025/07/05 12:07:10 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void	ft_sem_unlink(void)
{
	sem_unlink("/start_sem");
	sem_unlink("/print_sem");
	sem_unlink("/dead_sem");
	sem_unlink("/eat_sem");
	sem_unlink("/wait_sem");
	sem_unlink("/fork_sem");
	sem_unlink("/meals_eat_sem");
}

const char	*ft_sem_name(t_sem name)

{
	const char	*sem[] = {
		"/start_sem",
		"/print_sem",
		"/dead_sem",
		"/eat_sem",
		"/wait_sem",
		"/fork_sem",
		"/meals_eat_sem",
	};

	return (sem[name]);
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
		return (ft_error_int(PH_NEGATIVE));
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
	long	time;

	time = ft_get_current_time(philo->table);
	sem_wait(philo->table->sem_print);
	printf("%.06ld %d %s\n", time, philo->id, status);
	sem_post(philo->table->sem_print);
}
