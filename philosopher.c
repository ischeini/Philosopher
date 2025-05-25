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

void	print_list(t_fork *head)
{
	while (head)
	{
		printf("Valor: %d\n", head->table);
		head = head->next;
	}
}

/*void	print_soul_list(t_soul *head)
{
	int i = 1;
	while (head)
	{
		printf("Philosopher #%d:\n", i);
		printf("  Last meal time: %zu\n", head->last_meal);
		printf("  Has forks: %s\n", head->has_forks ? "Yes" : "No");
		printf("  Meals eaten: %d\n", head->meals_eaten);
		i++;
	}
}*/

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
	printf("times_to_eat : %zu \n", table->times_to_eat);
	printf("philosopher : %zu \n", table->philosophers);
	printf("sleep : %zu \n", table->sleep);
	printf("die : %zu \n", table->die);
	printf("eat : %zu \n", table->eat);
	print_list(table->forks[0]);
	philos = ft_start_philosophers(table);
	if (!philos)
	{
		free(table);
		return (1);
	}
	ft_lstclear_fork(table->forks);
	ft_lstclear_soul(philos);
	free(philos);
	free(table);
}