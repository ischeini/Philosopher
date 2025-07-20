/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_sem_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 16:03:17 by ischeini          #+#    #+#             */
/*   Updated: 2025/07/20 18:54:40 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_itos(int n, char *str)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	while (n > 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	str[i] = '\0';
	i--;
	j = 0;
	while (j < i)
	{
		c = str[j];
		str[j] = str[i];
		str[i] = c;
		j++;
		i--;
	}
}

static t_table	*ft_creat(sem_t **sem, t_table *table, char *name, char *num)
{
	int	i;

	i = 0;
	while (i <= table->num_phi)
	{
		ft_strcpy(name, "/sem_philo");
		ft_itos((i + 1), num);
		ft_strcat(name, num);
		sem_unlink(name);
		sem[i] = sem_open(name, O_CREAT, 0644, 1);
		if (sem[i] == SEM_FAILED)
			return (ft_sem_error(PH_SEM_OPEN, table, 1));
		i++;
	}
	return (table);
}

t_table	*ft_create_philo_sem(t_table *table)
{
	table->name = malloc(sizeof(char) * 32);
	if (!table->name)
		return (ft_error_null(PH_MALLOC));
	table->num = malloc(sizeof(char) * 8);
	if (!table->num)
	{
		free(table->name);
		return (ft_error_null(PH_MALLOC));
	}
	table->sem = malloc(sizeof(sem_t *) * (table->num_phi + 1));
	if (!table->sem)
	{
		free(table->num);
		free(table->name);
		return (ft_error_null(PH_MALLOC));
	}
	if (!ft_creat(table->sem, table, table->name, table->num))
		return (NULL);
	return (table);
}
