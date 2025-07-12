/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 11:11:00 by ischeini          #+#    #+#             */
/*   Updated: 2025/06/29 11:11:00 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H
# include <semaphore.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <limits.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef	enum	e_sem_err
{
	PH_SUCCESS = 0,	//Success
	PH_SEM_CLOSE,	//Error closing a semaphore
	PH_SEM_DELET,
	PH_SEM_WAIT,
	PH_INV_PHILO,
	PH_INV_DEATH,
	PH_INV_EAT,
	PH_INV_SLEEP,
	PH_INV_MEALS,
	PH_MEALS_ZERO,
	PH_FORK,
	PH_AMOUNT,
	PH_SEM_OPEN,
	PH_MALLOC,
	PH_NEGATIVE,
}	t_sem_err;

typedef struct s_sem
{
	sem_t	**sem;
	char	**names;
}	t_sem;

typedef struct s_philo
{
	struct timeval	start_time;
	struct s_table	*table;
	pthread_t		monitor;
	long			last_meal_time;
	int				meals_eaten;
	int				id;
}	t_philo;

typedef struct s_table
{
	struct timeval	start_time;
	pthread_t		meals_eat;
	pthread_t		dead;
	t_philo			*philos;
	t_sem			*meals_id;
	t_sem			*sem;
	long			time_to_sleep;
	long			time_to_die;
	long			time_to_eat;
	char			*names;
	int				max_meals;
	int				num_phi;
}	t_table;

t_table	*ft_init_table(t_table *table, int argc, char **args);

t_table	*ft_create_meal(t_table *table);

sem_t	*ft_create_sem(t_table *table, char *str, int num, int pos);

long	ft_get_current_time(t_table *table);

void	*ft_destroy_sem(sem_t **sem, char **names, int nbr);

int	ft_error(t_sem_err error);
int	ft_atoi(const char *str);

#endif
