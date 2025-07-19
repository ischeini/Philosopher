/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:10:13 by ischeini          #+#    #+#             */
/*   Updated: 2025/06/29 11:10:13 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	main(int argc, char **args)
{
	t_table		*table;

	if (argc < 5 || argc > 6)
		return (ft_error_int(PH_AMOUNT));
	table = NULL;
	table = ft_init_table(argc, args);
	if (!table)
		return (1);
	debug_table(table);
	debug_philo(table->philos);
	ft_sem_error(0, table, 0);
	ft_free(table);
	return (ft_error_int(PH_SUCCESS));
}
