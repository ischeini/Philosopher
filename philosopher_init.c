/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:59:51 by ischeini          #+#    #+#             */
/*   Updated: 2025/06/20 14:29:49 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*static t_philo	*ft_newphilo(t_fork **fork, t_table *table, int i)
{
	t_philo	*philo;
	t_fork	*tmp_fork;
	int		j;

	j = 0;
	tmp_fork = fork[0];
	while (++j < i)
		tmp_fork = tmp_fork->next;
	philo = malloc(1 * sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->left_fork = tmp_fork;
	philo->soul = malloc(sizeof(t_soul));
	if (!philo->soul)
	{
		ft_lstclear_fork(table->forks, table->philosophers);
		return (NULL);
	}
	philo->soul->last_meal = table->die;
	philo->soul->meals_eaten = 0;
	philo->soul->has_forks = 0;
	return (philo);
}

static void	ft_lstad_philo(t_table *table, t_philo **phil, t_philo *new, int i)
{
	new->times_to_eat = table->times_to_eat;
	new->sleep = table->sleep;
	new->die = table->die;
	new->eat = table->eat;
	new->soul->dead = 1;
	new->soul->nbr = i;
	new->you_eat = 0;
	new->next = NULL;
	new->back = NULL;
	ft_time_unused(new);
	if (!phil[0])
	{
		phil[0] = new;
		return ;
	}
	new->next = phil[0];
	phil[0]->back = new;
	phil[0] = new;
}

static void	ft_sit_philo(t_philo **philo, int philosophers)
{
	t_philo	*current;
	t_philo	*first;
	t_philo	*prev;
	t_philo	*last;
	int		i;

	i = 0;
	first = *philo;
	last = first;
	while (last && last->next)
	{
		last->right_fork = last->next->left_fork;
		last = last->next;
	}
	last->right_fork = first->left_fork;
	if (last && first && philosophers != 1)
	{
		last->next = first;
		first->back = last;
	}
	current = first;
	prev = last;
	while (current && i++ < philosophers && philosophers != 1)
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
	int		i;

	philos = (t_philo **)malloc(sizeof(t_philo *));
	if (!philos)
	{
		ft_lstclear_fork(table->forks, table->philosophers);
		return (NULL);
	}
	*philos = NULL;
	i = 0;
	while (i++ < table->philosophers)
	{
		next_philo = ft_newphilo(table->forks, table, i);
		if (!next_philo)
		{
			ft_lstclear_soul(philos, i);
			return (NULL);
		}
		pthread_mutex_init(&next_philo->left_fork->mutex, NULL);
		ft_lstad_philo(table, philos, next_philo, i);

	}
	ft_sit_philo(philos, table->philosophers);
	return (philos);
}*/