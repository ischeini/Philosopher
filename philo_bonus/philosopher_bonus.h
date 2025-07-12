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
}	t_sem_err;

typedef struct s_sem
{
	sem_t	*sem;
	char	names;
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
	t_sem			*sem;
	sem_t			*start_sem;
	sem_t			*print_sem;
	sem_t			*dead_sem;
	sem_t			*wait_sem1;
	sem_t			*wait_sem2;
	sem_t			*eat_sem;
	long			time_to_sleep;
	long			time_to_die;
	long			time_to_eat;
	char			*names;
	int				*sem;
	int				max_meals;
	int				num_phi;
}	t_table;

#endif
