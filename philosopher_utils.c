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

/*void	ft_time_unused(t_philo *philo)
{
	struct timeval	unused;
	struct timeval	tv;
	struct timeval	a;

	gettimeofday(&a, NULL);
	gettimeofday(&tv, NULL);
	ft_calculate(&a);
	gettimeofday(&unused, NULL);
	philo->unused = ft_calculate(&unused) - ft_calculate(&tv);
}*/

int	ft_atoi(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
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

/*int	ft_check_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] < '0' && args[i][j] > '9')
				return (ft_error("Args: No numbers"));
			j++;
		}
		i++;
	}
	return (1);
}*/