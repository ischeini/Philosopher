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

int	ft_error(t_sem_err error)
{
	const char *msg[] = {
		"Success."
		"Error to close the sem.",
		"Error to eliminate the sem.",
		"Error to wait the sem.",
		"Philosopher: Number invalid.",
		"Die: Number invalid.",
		"Eat: Number invalid.",
		"Sleep: Number invalid.".
		"Max meals: Nummer invalid.",
		"Philosophers: No need to eat.",
		"Error create fork"
	};
	printf("%s\n", msg[error]);
	return (error);
}

void	*ft_destroy_sem(sem_t *sem, char *names)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (sem[i] && sem_close(semaphores[i] == -1))
		{
			ft_error(PH_SEM_CLOSE);
			if (sem_unlink(names[i] == -1))
				ft_error(PH_SEM_DELET);
		}
		i++;
	}
	return (NULL);
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