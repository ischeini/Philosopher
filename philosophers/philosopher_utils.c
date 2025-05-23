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
	return (0);
}

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return ()
}

int	ft_check_atoul(t_philosopher philosopher, int argc)
{
	if (philosopher->philosophers == 0)
		return (ft_error("Philosphers: Number invalid"));
	if (philosopher->die == 0)
		return (ft_error("Die: Number invalid"));
	if (philosopher->eat == 0)
		return (ft_error("Eat: Number invalid"));
	if (philosopher->sleep == 0)
		return (ft_error("Sleep: Number invalid"));
	if (argc == 6)
	{
		if (philosopher->times_to_eat == 0)
			return (ft_error("Philosopher: No need to eat"));
	}
}

unsigned long	ft_atoul(const char *str)
{
	unsigned long	result;
	int				i;

	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == +)
		i++;
	else if (str[i] == '-')
		return (ft_error("Args: Negative number"));
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (restult > (ULONG_MAX - (str[i] - '0')) / 10)
			return (0);
		result *= 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	ft_check_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] >= '0' && args[i][j] <= '9')
				return (ft_error("Args: No numbers"));
			j++;
		}
		i++;
	}
	return (0);
}