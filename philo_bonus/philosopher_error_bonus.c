/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_error_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 11:31:51 by ischeini          #+#    #+#             */
/*   Updated: 2025/07/13 11:31:51 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	ft_error_int(t_sem_err error)
{
	const char *msg[] = {
		"Success.",
		"Error to close the sem.",
		"Error to eliminate the sem.",
		"Error to wait the sem.",
		"Philosopher: Number invalid.",
		"Die: Number invalid.",
		"Eat: Number invalid.",
		"Sleep: Number invalid.",
		"Max meals: Nummer invalid.",
		"Philosophers: No need to eat.",
		"Error create fork.",
		"Argv: amount.",
		"Error open the sem.",
		"Error malloc.",
		"Negative number."
	};
	printf("%s\n", msg[error]);
	return (error);
}

void	*ft_error_null(t_sem_err error)
{
	const char *msg[] = {
		"Success.",
		"Error to close the sem.",
		"Error to eliminate the sem.",
		"Error to wait the sem.",
		"Philosopher: Number invalid.",
		"Die: Number invalid.",
		"Eat: Number invalid.",
		"Sleep: Number invalid.",
		"Max meals: Nummer invalid.",
		"Philosophers: No need to eat.",
		"Error create fork.",
		"Argv: amount.",
		"Error open the sem.",
		"Error malloc.",
		"Negative number."
	};
	printf("%s\n", msg[error]);
	return (NULL);
}

void	*ft_sem_error(t_sem_err error, t_table *table, int i)
{
	sem_close(table->sem_start);
	sem_close(table->sem_print);
	sem_close(table->sem_dead);
	sem_close(table->sem_wait);
	sem_close(table->sem_forks);
	sem_close(table->sem_eat);
	sem_close(table->sem_meals_eat);
	ft_sem_unlink();
	if (i == 1)
		return (ft_error_null(error));
	return (NULL);
}

void	ft_free(t_table *table)
{
	if (table->philos)
		free(table->philos);
	free(table);
}
