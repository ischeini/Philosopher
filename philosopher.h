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
	struct s_fork	*next;
	int				table;
}	t_fork;

typedef struct s_soul
{
	pthread_t		philosophers;
	size_t			last_meal;
	int				has_forks;
	int				meals_eaten;
}	t_soul;

typedef struct s_philo
{
	struct s_philo	*back;
	struct s_philo	*next;
	t_soul			*soul;
	t_fork			*left_fork;
	t_fork			*right_fork;
}	t_philo;

typedef struct s_table
{
	t_philo			*head;
	t_fork			**forks;
	size_t			sleep;
	size_t			eat;
	size_t			die;
	size_t			philosophers;
	size_t			times_to_eat;
}t_table;

unsigned long	ft_atoul(const char *str);

t_philo			**ft_start_philosophers(t_table *table);

t_table			*ft_init_table(int argc, char **args);

void			ft_lstclear_soul(t_philo **philo);

void			ft_lstclear_fork(t_fork **fork);

int				ft_error(char *str);

int				ft_check_args(char **args);

#endif
