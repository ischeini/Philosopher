/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:03:45 by ischeini          #+#    #+#             */
/*   Updated: 2025/05/10 11:03:45 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef	struct s_fork
{
	pthread_mutex_t	mutex;
	struct s_fork	*next;
	int				table;
}	t_fork;

typedef struct s_soul
{
	pthread_t		philosophers;
	int				last_meal;
	int				has_forks;
	int				meals_eaten;
	int				dead;
	int				nbr;
}	t_soul;

typedef struct s_philo
{
	struct s_philo	*back;
	struct s_philo	*next;
	t_soul			*soul;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				die;
	int				sleep;
	int				times_to_eat;
	int				you_eat;
	int				eat;
}	t_philo;

typedef struct s_table
{
	t_philo			*head;
	t_fork			**forks;
	int				sleep;
	int				eat;
	int				die;
	int				philosophers;
	int				times_to_eat;
}t_table;

void	ft_can_grab_forks(t_philo *phi, __useconds_t milisec);

void	ft_sleep(t_philo *phi, __useconds_t milisec);

void	ft_think(t_philo *phi);

int		ft_philo_alive(t_philo *phi);

t_philo	**ft_start_philosophers(t_table *table);

t_table	*ft_init_table(int argc, char **args);

void	ft_lstclear_soul(t_philo **philo, int philosophers);

void	ft_lstclear_fork(t_fork **fork, int philosophers);

void	ft_start_simulation(t_philo **philo, t_table *table);

int		ft_check_args(char **args);

int		ft_atoi(const char *str);

int		ft_error(char *str);

#endif
