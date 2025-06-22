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

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id;
} t_fork;

typedef struct s_philo
{
	pthread_t	thread;
	struct		s_table *table;
	t_fork		*right_fork;
	t_fork		*left_fork;
	long		last_meal_time;
	int 		meals_eaten;
	int			is_eating;
	int			priority;
	int 		id;
} t_philo;

typedef struct s_table
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	start_mutex;
	t_philo			*philos;
	struct			timeval start_time;
	long			time_to_sleep;
	long			time_to_die;
	long			time_to_eat;
	int				simulation_running;
	int				num_philos;
	int				max_meals;
	t_fork			*forks;
} t_table;

int		ft_error(char *str);

int		ft_atoi(const char *str);

void	ft_destroy_mutex(t_table *table);

t_table	*ft_init_table(t_table *table, int argc, char **args);

void	*ft_monitor_routine(void *arg);

void	*ft_philo_routine(void *arg);

long	ft_get_current_time(t_table *table);

void	ft_print_status(t_philo *philos, const char *status);

/*typedef struct s_time
{
	struct timeval	last_thing;
	struct timeval	last_meal;
	struct timeval	current;
	struct timeval	initial;
	long			dead;
}	t_time;


typedef	struct s_fork
{
	pthread_mutex_t	mutex;
	struct s_fork	*next;
	int				table;
}	t_fork;

typedef struct s_soul
{
	pthread_t		*philosophers;
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
	t_fork			*right_fork;
	t_fork			*left_fork;
	t_soul			*soul;
	t_time			*time;
	long			unused;
	int				times_to_eat;
	int				you_eat;
	int				sleep;
	int				die;
	int				eat;
}	t_philo;

typedef struct s_table
{
	t_philo			*head;
	t_philo			**philo;
	t_fork			**forks;
	int				sleep;
	int				eat;
	int				die;
	int				philosophers;
	int				times_to_eat;
}t_table;

void	ft_time_unused(t_philo *philo);

long	ft_calculate(struct timeval *current);

int	ft_can_grab_forks(t_philo *phi, t_time *time);

int	ft_sleep(t_philo *phi, t_time *time);

void	ft_think(t_philo *phi, t_time *time);

int		ft_philo_alive(t_philo *phi, t_time *time);

t_philo	**ft_start_philosophers(t_table *table);

t_table	*ft_init_table(int argc, char **args);

void	ft_lstclear_soul(t_philo **philo, int philosophers);

void	ft_lstclear_fork(t_fork **fork, int philosophers);

void	ft_start_simulation(t_philo **philo, t_table *table);

int		ft_check_args(char **args);

int		ft_atoi(const char *str);

int		ft_error(char *str);*/

#endif
