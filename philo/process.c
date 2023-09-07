/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:04:45 by mgagne            #+#    #+#             */
/*   Updated: 2023/09/07 18:05:48 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *p)
{
	pthread_mutex_lock(&p->info->fork_m[p->left_fork - 1]);
	pthread_mutex_lock(&p->info->fork_m[p->right_fork - 1]);
	pthread_mutex_lock(&p->info->print_m);
	printf("%ld %d %s\n", get_time(p->info->create_time), p->id, FORK);
	printf("%ld %d %s\n", get_time(p->info->create_time), p->id, FORK);
	pthread_mutex_unlock(&p->info->print_m);
	return ;
}

void	eat(t_philo *p)
{
	pthread_mutex_lock(&p->info->print_m);
	printf("%ld %d %s\n", get_time(p->info->create_time), p->id, EAT);
	pthread_mutex_unlock(&p->info->print_m);
	p->eat_time = get_time(p->info->create_time);
	p->nb_eat += 1;
	usleep(p->info->t_eat * 1000);
	return ;
}

void	replace_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->info->fork_m[p->left_fork - 1]);
	pthread_mutex_unlock(&p->info->fork_m[p->right_fork - 1]);
	return ;
}

void	sleep_think(t_philo *p)
{
	pthread_mutex_lock(&p->info->print_m);
	printf("%ld %d %s\n", get_time(p->info->create_time), p->id, SLEEP);
	pthread_mutex_unlock(&p->info->print_m);
	usleep(p->info->t_sleep * 1000);
	pthread_mutex_lock(&p->info->print_m);
	printf("%ld %d %s\n", get_time(p->info->create_time), p->id, THINK);
	pthread_mutex_unlock(&p->info->print_m);
	return ;
}

void	*philosophize(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	// printf("%d\n", p->id);
	// printf("%ld\n", get_time(p->info->create_time));
	while (p->nb_eat != p->info->nb_eat)
	{
		//check die
		take_forks(p);
		//check die
		eat(p);
		replace_forks(p);
		//check die
		sleep_think(p);
	}
	return (NULL);
}
