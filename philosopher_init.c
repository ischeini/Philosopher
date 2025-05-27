/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:59:51 by ischeini          #+#    #+#             */
/*   Updated: 2025/05/27 18:16:04 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static t_philo	*ft_newphilo(t_fork **fork, t_table *table, int i)
{
	t_philo	*philo;
	t_fork	*tmp_fork;
	int		j;

	j = -1;
	tmp_fork = fork[0];
	while (j++ < i)
		tmp_fork = tmp_fork->next;
	philo = malloc(1 * sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->left_fork = tmp_fork;
	if (i == table->philosophers)
		tmp_fork->next = fork[0];
	philo->right_fork = tmp_fork->next;
	philo->soul = malloc(sizeof(t_soul));
	if (!philo->soul)
	{
		ft_lstclear_fork(table->forks);
		return (NULL);
	}
	philo->soul->last_meal = table->die;
	philo->soul->meals_eaten = 0;
	philo->soul->has_forks = 0;
	return (philo);
}

static void	ft_lstadd_philo(t_philo **philo, t_philo *new, int i)
{
	new->times_to_eat = philo[0]->times_to_eat;
	new->sleep = philo[0]->sleep;
	new->soul->philosophers = i;
	new->die = philo[0]->die;
	new->eat = philo[0]->eat;
	new->soul->dead = 1;
	new->you_eat = 0;
	new->next = NULL;
	new->back = NULL;
	if (!*philo)
	{
		*philo = new;
		return ;
	}
	new->next = *philo;
	(*philo)->back = new;
	*philo = new;
}

static void	ft_sit_philo(t_philo **philo, int philosophers)
{
	t_philo	*current;
	t_philo	*first;
	t_philo	*prev;
	t_philo	*last;
	int		i;

	i = -1;
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
	while (current && i++ < philosophers)
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
			ft_lstclear_soul(philos, i);
			return (NULL);
		}
		ft_lstadd_philo(philos, next_philo, i);
		pthread_mutex_init(next_philo->left_fork->mutex, NULL);
	}
	ft_sit_philo(philos, table->philosophers);
	return (philos);
}