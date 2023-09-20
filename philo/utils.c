/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:50:52 by mgagne            #+#    #+#             */
/*   Updated: 2023/09/20 10:01:40 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_fill_tab(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		info->int_tab[i] = 0;
		i++;
	}
	return ;
}

long	get_time(long create_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_usec / 1000 + time.tv_sec * 1000) - create_time);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	print_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return ;
}

long long	ft_atoll(const char *str)
{
	long long	result;
	long long	tmp;
	char		is_negative;

	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
		|| *str == '\r' || *str == ' ')
		str++;
	is_negative = *str == '-';
	if (*str == '+' || *str == '-')
		str++;
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		tmp = result * 10 + *str++ - '0';
		if (tmp < result)
		{
			if (is_negative)
				return (LLONG_MIN);
			return (LLONG_MAX);
		}
		result = tmp;
	}
	if (is_negative)
		return (-result);
	return (result);
}
