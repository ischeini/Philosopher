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
	t_table		table;

	if (argc < 5 || argc > 6)
		return (ft_error(PH_AMOUNT));
	if (!ft_init_table(&table, argc, args))
		return (1);
	if (!ft_create_sem(&table, "/dead_sem", table.num_phi, 2) ||
		!ft_create_sem(&table, "/eat_sem", (table.num_phi / 2), 3) ||
		!ft_create_sem(&table, "/fork_sem", (table.num_phi / 2), 4) ||
		!ft_create_sem(&table, "/wait_sem", 1, 5) ||
		!ft_create_meal(&table))
	{
		ft_destroy_sem(table.meals_id->sem, table.meals_id->names, 6);
		ft_destroy_sem(table.sem->sem, table.sem->names, table.num_phi);
		return (1);
	}
	//ft_simulation(table);
	ft_destroy_sem(table.meals_id->sem, table.meals_id->names, 6);
	ft_destroy_sem(table.sem->sem, table.sem->names, table.num_phi);
	return (ft_error(0));
}