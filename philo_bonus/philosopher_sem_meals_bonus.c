/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_sem_meals_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ischeini <ischeini@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:14:13 by ischeini          #+#    #+#             */
/*   Updated: 2025/07/12 17:53:57 by ischeini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);	
}

static char *ft_itoa(int n)
{
	char	buf[12];
	char	*str;
	int		i;
	int		j;

	i = 0;
	if (n == 0)
		buf[i++] = '0';
	while (n > 0)
	{
		buf[i++] = (n % 10) + '0';
		n /= 10;
	}
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		str[j] = buf[i - j - 1];
		j++;
	}
	str[i] = '\0';
	return (str);
}

static char *ft_make_sem_name(int index)
{
	char	*full_name;
	char	*str;

	str = ft_itoa(index);
	if (!str)
	{
		ft_error(PH_MALLOC);
		return (NULL);
	}
	full_name = malloc(ft_strlen("/meals_id") + ft_strlen(str) + 1);
	if (!full_name)
	{
		ft_error(PH_MALLOC);
		free(str);
		return (NULL);
	}
	memcpy(full_name, "/meals_id", ft_strlen("/meals_id"));
	memcpy(full_name + ft_strlen("/meals_id"), str, ft_strlen(str) + 1);
	free(str);
	return (full_name);
}

t_table	*ft_create_meal(t_table *table)
{
	char	*str;
	int		i;
	
	i = 0;
	while (i < table->num_phi)
	{
		str = ft_make_sem_name(i);
		if (!str)
			return (NULL);
		if (sem_unlink(str))
		{
			ft_error(PH_SEM_DELET);
			return (NULL);
		}
		table->sem->sem[i] = sem_open(str, O_CREAT | O_EXCL, 0644, 0);
		if (table->sem->sem[i] == SEM_FAILED)
		{
			ft_error(PH_SEM_OPEN);
			free(str);
			return (NULL);
		}
		table->sem->names[i] = str;
		i++;
	}
	return (table);
}