/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:50:52 by mgagne            #+#    #+#             */
/*   Updated: 2023/06/03 13:04:06 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	print_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (1);
}

static int	ft_overflow(int negative)
{
	if (negative == -1)
		return (0);
	else
		return (-1);
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				negative;
	long int		result;

	i = 0;
	negative = 1;
	result = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			negative = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		if (result != (result * 10 + (str[i] - '0')) / 10)
			return (ft_overflow(negative));
		result *= 10;
		result += (int)str[i] - '0';
		i++;
	}
	return ((int) result * negative);
}
