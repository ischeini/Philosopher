/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:03:18 by ischeini          #+#    #+#             */
/*   Updated: 2025/05/10 11:03:18 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **args)
{
	t_philo	**philos;
	t_table	*table;

	if (argc <= 4 || argc >= 7)
		return (ft_error("Argv: Amount"));
	if (!ft_check_args(args))
		return (1);
	table = ft_init_table(argc, args);
	if (!table)
		return (1);
	philos = ft_start_philosophers(table);
	if (!philos)
	{
		free(table);
		return (1);
	}
	ft_start_simulation(philos, table);
	ft_lstclear_fork(table->forks);
	ft_lstclear_soul(philos, table->philosophers);
	free(table);
	return (0);
}