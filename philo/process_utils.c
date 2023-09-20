/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:30:55 by mgagne            #+#    #+#             */
/*   Updated: 2023/09/20 14:40:32 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	replace_fork(t_philo *p, int fork_id)
{
	pthread_mutex_lock(&p->info->fork_m[fork_id]);
	p->info->int_tab[fork_id] = 0;
	pthread_mutex_unlock(&p->info->fork_m[fork_id]);
	return ;
}

int	take_fork(t_philo *p, int fork_id)
{
	while (1)
	{
		if (check_death(p))
			return (1);
		pthread_mutex_lock(&p->info->fork_m[fork_id]);
		if (p->info->int_tab[fork_id] == 0)
			break ;
		pthread_mutex_unlock(&p->info->fork_m[fork_id]);
		usleep(p->info->nb_philo * 10);
	}
	p->info->int_tab[fork_id] = 1;
	pthread_mutex_unlock(&p->info->fork_m[fork_id]);
	return (0);
}

int	ft_usleep(t_philo *p, long long t_sleep)
{
	long	t;

	t = get_time(p->info->create_time);
	while ((get_time(p->info->create_time) - t) < t_sleep)
	{
		usleep(t_sleep);
		if (check_death(p))
			return (1);
	}
	return (0);
}

int	check_death(t_philo *p)
{
	pthread_mutex_lock(&p->info->dead_m);
	if (p->info->alive
		&& (get_time(p->info->create_time) - p->eat_time) > p->info->t_die)
	{
		p->info->alive = 0;
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, DEAD);
		pthread_mutex_unlock(&p->info->dead_m);
		return (1);
	}
	if (p->info->alive == 0)
	{
		pthread_mutex_unlock(&p->info->dead_m);
		return (1);
	}
	pthread_mutex_unlock(&p->info->dead_m);
	return (0);
}
