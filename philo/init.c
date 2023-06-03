/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:54:20 by mgagne            #+#    #+#             */
/*   Updated: 2023/06/03 22:30:41 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (!argv[i][0])
			return (print_error(ERROR2), 1);
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (print_error(ERROR3), 1);
			j++;
		}
		i++;
	}
	return (0);
}

t_philo	*init_philo(int argc, char **argv)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (!p)
		return (print_error(ERROR99), NULL);
	p->ac = argc;
	p->nb_philo = ft_atoi(argv[1]);
	printf("%d\n", p->nb_eat);
	p->t_die = ft_atoi(argv[2]);
	p->t_eat = ft_atoi(argv[3]);
	p->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		p->nb_eat = ft_atoi(argv[5]);
	else
		p->nb_eat = -1;
	if (p->nb_philo <= 0 || (argc == 6 && p->nb_eat <= 0))
		return (print_error(ERROR4), NULL);
	if (p->t_die < 60 || p->t_eat < 60 || p->t_sleep < 60)
		return (print_error(ERROR5), NULL);
	return (p);
}
