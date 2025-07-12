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

static void	ft_simulation(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	if (table->simulation_running)
	{
		philo->is_eating = 1;
		ft_print_status(philo, "has taken a fork");
		ft_print_status(philo, "has taken a fork");
		ft_print_status(philo, "is eating");
		philo->last_meal_time = ft_get_current_time(table);
		usleep(table->time_to_eat * 1000);
		philo->last_meal_time = ft_get_current_time(table);
		philo->is_eating = 0;
	}
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	if (table->simulation_running)
	{
		ft_print_status(philo, "is sleeping");
		usleep(table->time_to_sleep * 1000);
		ft_print_status(philo, "is thinking");
		philo->meals_eaten++;
	}
}

void	*ft_philo_routine(t_table *table)
{
	if (sem_wait(table->sem[0]))
		return (ft_error(PH_SEM_WAIT));
	philo->last_meal_time = ft_get_current_time(table);
	if (philo->id % 2 == 0)
		usleep(table->time_to_eat * 900);
	if (table->simulation_running && (table->max_meals != 0)
		&& (table->time_to_die) != 0)
		ft_print_status(philo, "is thinking");
	while ((table->simulation_running && (table->max_meals != 0)
			&& (table->time_to_die) != 0 && table->num_philos != 1))
		ft_simulation(table, philo);
	return (NULL);
}

static void	*ft_simulation(t_table *table)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i++ < table->num_phi)
	{
		pid = fork();
		if (pid < 0)
			return (ft_error(PH_FORK));
		else if (pid == 0)
			ft_philo_routine(table);
		pthread_create(table->dead, NULL, ft_monitor_dead, table);
		table->philos->id++;
	}
	ulseep(1000);
	
}


void philo_routine(t_philo *philo) {
    while () {
        sem_wait(philo->sems->active_group);
        sem_wait(philo->sems->delay_gate);
        sem_post(philo->sems->active_group);
        usleep(philo->times.eat * 400); // Demora proporcional al tiempo de comer
        sem_wait(philo->sems->entry_gate);
        sem_post(philo->sems->delay_gate);
        print_action(philo, "take fork");
        print_action(philo, "take fork");
        print_action(philo, "is eating");
        philo->last_meal = get_time();
        usleep(philo->times.eat);
        sem_post(philo->sems->entry_gate);
        print_action(philo, "is sleeping");
        usleep(philo->times.sleep);
        print_action(philo, "is thinking");
    }
}

int	main(int argc, char **args)
{
	t_table		table;
	int			i;

	if (argc < 5 || argc > 6)
		return (ft_error("Argv: Amount"));
	if (!ft_init_table(&table, argc, args))
		return (1);
	if (!ft_create_sem(table, "/dead_sem", table->num_phi, 2) ||
		!ft_create_sem(table, "/wait_sem", (table->num_phi / 2), 3) ||
		!ft_create_sem(table, "/wait_sem", (table->num_phi / 2), 4) ||
		!ft_create_sem(table, "/eat_sem", 1, 5))
	{
		ft_destroy_sem(table->sem, table-sem->names)
		return (1);
	}
	ft_simulation(table);
	ft_destroy_sem(table->sem, table->sem->names);
	return (ft_error(0));
}