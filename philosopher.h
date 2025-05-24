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

typedef struct s_philosopher
{
	pthread_t		philosophers;//soul
	size_t			last_meal;//if > == die | FAIL
	int				has_forks;//false if (has_fork){ ft_eat(philo)}
	int				meals_eaten;
}	t_philosopher;

typedef	struct s_fork
{
	int	table;//if 0 (no table) else (on table)
}	t_fork;

typedef struct s_philo//t_list -- Function 1st priority;
{
	t_philosopher	philosopher;//void *content //philosopher
	t_fork			*left_fork; //forks[0]
	t_fork			*right_fork; //forks[1]//grab_forks(philo) phil
	struct s_philo	*next;//struct s_list *next; struct s_list *prev;
	struct s_philo	*back;
}	t_philo;

typedef struct s_table
{
	t_fork			**forks;// == philosophers 0 - 1
	size_t			sleep;
	size_t			eat;
	size_t			die;
	int				philosophers;//b
	int				times_to_eat;//b
	t_philo		*first;//t_list **head;
}t_table;



unsigned long	ft_atoul(const char *str);

int			ft_check_atoul(t_philosopher *philosopher, int argc);

int			ft_check_args(char **args);

int			ft_error(char *str);

#endif
