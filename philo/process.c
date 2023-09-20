/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:04:45 by mgagne            #+#    #+#             */
/*   Updated: 2023/09/20 14:34:37 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *p)
{
	if (take_fork(p, p->left_fork - 1))
		return (1);
	if (!check_death(p))
	{
		pthread_mutex_lock(&p->info->print_m);
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, FORK);
		pthread_mutex_unlock(&p->info->print_m);
	}
	else
		return (1);
	if (p->info->nb_philo == 1)
	{
		usleep(p->info->t_die * 1000);
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, DEAD);
		return (1);
	}
	if (take_fork(p, p->right_fork - 1))
		return (1);
	if (!check_death(p))
	{
		pthread_mutex_lock(&p->info->print_m);
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, FORK);
		return (pthread_mutex_unlock(&p->info->print_m), 0);
	}
	return (1);
}

int	eat(t_philo *p)
{
	if (!check_death(p))
	{
		pthread_mutex_lock(&p->info->print_m);
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, EAT);
		pthread_mutex_unlock(&p->info->print_m);
		if (ft_usleep(p, p->info->t_eat))
			return (1);
		p->eat_time = get_time(p->info->create_time);
		p->nb_eat += 1;
		replace_fork(p, p->left_fork - 1);
		replace_fork(p, p->right_fork - 1);
		return (0);
	}
	return (1);
}

int	ft_sleep(t_philo *p)
{
	if (!check_death(p))
	{
		pthread_mutex_lock(&p->info->print_m);
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, SLEEP);
		pthread_mutex_unlock(&p->info->print_m);
		return (ft_usleep(p, p->info->t_sleep));
	}
	return (1);
}

int	think(t_philo *p)
{
	if (!check_death(p))
	{
		pthread_mutex_lock(&p->info->print_m);
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, THINK);
		pthread_mutex_unlock(&p->info->print_m);
		return (0);
	}
	return (1);
}

void	*philosophize(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	pthread_mutex_lock(&p->info->jon);
	pthread_mutex_unlock(&p->info->jon);
	if (p->id % 2 != 0)
		usleep(40000);
	// printf("%ld %d\n", get_time(p->info->create_time), p->id);
	while (p->nb_eat != p->info->nb_eat)
	{
		if (take_forks(p))
			break ;
		if (eat(p))
			break ;
		if (ft_sleep(p))
			break ;
		if (think(p))
			break ;
	}
	free(data);
	return (NULL);
}
