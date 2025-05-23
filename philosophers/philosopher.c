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

static t_philisopher	*ft_init_philosopher(int argc)
{
	t_philosopher	*philosopher;

	philosopher->philosophers = ft_atoul(args[1]);
	philosopher->die = ft_atoul(args[2]);
	philosopher->eat = ft_atoul(args[3]);
	philosopher->slepp = ft_atoul(args[4]);
	if (argc == 6)
		philosopher->times_to_eat = ft_atoul(args[5]);
	if (ft_check_atoul(philosopher, argc))
		return (NULL);
	return (philosopher);
}

int	main(int argc, char **args)
{
	t_philosopher	*philosopher;

	if (argc != 5 || argc != 6)
		return (ft_error("Argv: Amount"));
	if (ft_check_args(args))
		return (1);
	philosopher = ft_init_philospher(argc);
	if (!philosopher)
		return (1);
	ft_start_eat(philosopher);
}