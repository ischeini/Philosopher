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

typedef enum e_sem
{
	PH_SEM_START = 0,
	PH_SEM_PRINT,
	PH_SEM_DEAD,
	PH_SEM_EAT,
	PH_SEM_WAI,
	PH_SEM_FORKS,
	PH_SEM_MEALS,
}	t_sem;

typedef enum e_sem_err
{
	PH_SUCCESS = 0,
	PH_SEM_CLOSE,
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
	sem_t			**sem;
	sem_t			*sem_start;
	sem_t			*sem_meals_eat;
	sem_t			*sem_print;
	sem_t			*sem_dead;
	sem_t			*sem_wait;
	sem_t			*sem_forks;
	sem_t			*sem_eat;
	char			*name;
	char			*num;
	long			time_to_sleep;
	long			time_to_die;
	long			time_to_eat;
	int				max_meals;
	int				num_phi;
}	t_table;

t_table		*ft_init_table(int argc, char **args);
t_table		*ft_create_philo_sem(t_table *table);

char		*ft_strcat(char *dest, char *src);
char		*ft_strcpy(char *dest, char *src);

long		ft_get_current_time(t_table *table);


const char	*ft_sem_name(t_sem name);

void		*ft_error_null(t_sem_err error);
void		*ft_sem_error(t_sem_err error, t_table *table, int i);
void		ft_print_status(t_philo *philo, const char *status);
void		ft_start_simulation(t_table *table);
void		ft_itos(int n, char *str);
void		ft_free(t_table *table);
void		ft_sem_unlink(void);

int			ft_error_int(t_sem_err error);
int			ft_atoi(const char *str);

#endif
