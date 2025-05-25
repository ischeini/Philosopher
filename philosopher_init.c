/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:59:51 by ischeini          #+#    #+#             */
/*   Updated: 2025/05/25 18:14:55 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_philo	*ft_newphilo(t_fork **fork, t_table *table, size_t i)
{
	t_philo	*philo;

	philo = malloc(1 * sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->left_fork = fork[i - 1];
	philo->right_fork = fork[i];
	philo->soul = malloc(1 * sizeof(t_soul));
	if (!philo->soul)
	{
		ft_lstclear_fork(table->forks);
		free(table);
		return (NULL);
	}
	philo->soul->last_meal = table->die;
	philo->soul->meals_eaten = 0;
	philo->soul->has_forks = 0;
	philo->next = NULL;
	philo->back = NULL;
	return (philo);
}

static void	ft_lstadd_philo(t_philo **philo, t_philo *new)
{
	if (!*philo)
	{
		*philo = new;
		return ;
	}
	new->next = *philo;
	(*philo)->back = new;
	*philo = new;
}

static void	ft_sit_philo(t_philo **philo)
{
	t_philo	*current;
	t_philo	*first;
	t_philo	*prev;
	t_philo	*last;

	first = *philo;
	last = first;
	while (last && last->next)
		last = last->next;
	if (last && first)
	{
		last->next = first;
		first->back = last;
	}
	current = first;
	prev = last;
	while (current)
	{
		current->back = prev;
		prev = current;
		current = current->next;
	}
}

t_philo	**ft_start_philosophers(t_table *table)
{
	t_philo	**philos;
	t_philo	*next_philo;
	size_t	i;

	philos = (t_philo **)malloc(sizeof(t_philo *));
	if (!philos)
	{
		ft_lstclear_fork(table->forks);
		return (NULL);
	}
	*philos = NULL;
	i = 0;
	while (i++ < table->philosophers)
	{
		next_philo = ft_newphilo(table->forks, table, i);
		if (!next_philo)
		{
			ft_lstclear_soul(philos);
			return (NULL);
		}
		ft_lstadd_philo(philos, next_philo);
	}
	ft_sit_philo(philos);
	return (philos);
}