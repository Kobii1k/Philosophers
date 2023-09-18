/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:54:20 by mgagne            #+#    #+#             */
/*   Updated: 2023/09/07 18:13:19 by mgagne           ###   ########.fr       */
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

static int	check_overflow(t_info *p, int argc)
{
	if (p->nb_philo > INT_MAX || p->t_die > INT_MAX || p->t_eat > INT_MAX || \
	p->t_sleep > INT_MAX || p->nb_philo <= 0 || p->t_die <= 0 || \
	p->t_eat <= 0 || p->t_sleep <= 0 || \
	(argc == 6 && (p->nb_eat <= 0 || p->nb_eat > INT_MAX)))
		return (print_error(ERROR4), 1);
	if (p->t_die < 60 || p->t_eat < 60 || p->t_sleep < 60)
		return (print_error(ERROR5), 1);
	return (0);
}

t_info	*init_info(int argc, char **argv)
{
	t_info			*info;
	struct timeval	time;

	info = malloc(sizeof(t_info));
	if (!info)
		return (print_error(ERROR99), NULL);
	info->ac = argc;
	info->nb_philo = ft_atoll(argv[1]);
	info->t_die = ft_atoll(argv[2]);
	info->t_eat = ft_atoll(argv[3]);
	info->t_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		info->nb_eat = ft_atoll(argv[5]);
	else
		info->nb_eat = -1;
	if (check_overflow(info, argc))
		return(free(info), NULL);
	gettimeofday(&time, NULL);
	info->create_time = (long)(time.tv_usec / 1000 + time.tv_sec * 1000);
	pthread_mutex_init(&(info->print_m), NULL);
	pthread_mutex_init(&(info->dead_m), NULL);
	return (info);
}

pthread_t	*init_philo(t_info *info)
{
	pthread_t	*philo_threads;

	philo_threads = malloc(sizeof(pthread_t) * info->nb_philo);
	if (!philo_threads)
		return (free(info), NULL);
	info->alive = 1;
	info->fork_m = init_forks(info->nb_philo);
	if (!info->fork_m)
		return (free(info), free(philo_threads), NULL);
	return (philo_threads);
}

pthread_mutex_t	*init_forks(int	n)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!forks)
		return (print_error(ERROR99), NULL);
	i = -1;
	while (++i < n)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}
