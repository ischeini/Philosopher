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

static int	ft_create_table(void)
{

}

static t_philo	*ft_start_simulation(philosophers)
{
	t_philo	**table;

	table = malloc(1 * sizeof(t_table));
	if (!table)
		return (NULL);
	table[0] = 
	table->forks = 0;
	table->philosophers	
	
}

static t_philosopher	*ft_init_table(int argc, char **args)
{
	t_table	*table;

	table = malloc(1 * sizeof(t_philosopher));
	if (!table)
		return (NULL);
	table->philosophers = ft_atoul(args[1]);
	table->die = ft_atoul(args[2]);
	table->eat = ft_atoul(args[3]);
	table->sleep = ft_atoul(args[4]);
	if (argc == 6)
		table->times_to_eat = ft_atoul(args[5]);
	if (!ft_check_atoul(table, argc))
	{
		free(table);
		return (NULL);
	}
	return (table);
}

int	main(int argc, char **args)
{
	t_philosopher	*philosopher;
	t_table			*table;

	if (argc <= 4 || argc >= 7)
		return (ft_error("Argv: Amount"));
	if (!ft_check_args(args))
		return (1);
	philosopher = ft_init_table(argc, args);
	if (!philosopher)
		return (1);
	//printf("times_to_eat : %d \n", philosopher->times_to_eat);
	//printf("philosopher : %d \n", philosopher->philosophers);
	//printf("sleep : %zu \n", philosopher->sleep);
	//printf("die : %zu \n", philosopher->die);
	//printf("eat : %zu \n", philosopher->eat);
	table = ft_start_simulation(philosopher);
	if (!table)
		return (1);
	free(philosopher);
	free(table);
}