/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:04:45 by mgagne            #+#    #+#             */
/*   Updated: 2023/09/18 16:52:25 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	replace_forks(t_philo *p);
int		check_death(t_philo *p);

int	ft_usleep(t_philo *p, long long t_sleep)
{
	long	t;

	t = get_time(p->info->create_time);
	while ((get_time(p->info->create_time) - t) < t_sleep)
	{
		usleep(p->info->nb_philo);
		if (check_death(p))
			return (1);
	}
	return (0);
}

int	check_death(t_philo *p)
{
	pthread_mutex_lock(&p->info->dead_m);
	if (p->info->alive && (get_time(p->info->create_time) - p->eat_time) > p->info->t_die)
	{
		p->info->alive = 0;
		// pthread_mutex_lock(&p->info->print_m);
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, DEAD);
		// pthread_mutex_unlock(&p->info->print_m);
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

int	take_forks(t_philo *p)
{

	pthread_mutex_lock(&p->info->fork_m[p->left_fork - 1]);
	pthread_mutex_lock(&p->info->fork_m[p->right_fork - 1]);
	pthread_mutex_lock(&p->info->print_m);
	if (!check_death(p))
	{
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, FORK);
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, FORK);
		pthread_mutex_unlock(&p->info->print_m);
		return (0);
	}
	pthread_mutex_unlock(&p->info->print_m);
	replace_forks(p);
	return (1);
}

int	eat(t_philo *p)
{
	pthread_mutex_lock(&p->info->print_m);
	if (!check_death(p))
	{
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, EAT);
		pthread_mutex_unlock(&p->info->print_m);
		p->eat_time = get_time(p->info->create_time);
		p->nb_eat += 1;
		if (ft_usleep(p, p->info->t_eat))
		{
			replace_forks(p);
			return (1);
		}
		return (0);
	}
	pthread_mutex_unlock(&p->info->print_m);
	replace_forks(p);
	return (1);
}

void	replace_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->info->fork_m[p->left_fork - 1]);
	pthread_mutex_unlock(&p->info->fork_m[p->right_fork - 1]);
	return ;
}

int	ft_sleep(t_philo *p)
{
	pthread_mutex_lock(&p->info->print_m);
	if (!check_death(p))
	{
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, SLEEP);
		pthread_mutex_unlock(&p->info->print_m);
		return (ft_usleep(p, p->info->t_sleep));
	}
	pthread_mutex_unlock(&p->info->print_m);
	return (1);
}

int	think(t_philo *p)
{
	pthread_mutex_lock(&p->info->print_m);
	if (!check_death(p))
	{
		printf("%ld %d %s\n", get_time(p->info->create_time), p->id, THINK);
		pthread_mutex_unlock(&p->info->print_m);
		return (0);
	}
	pthread_mutex_unlock(&p->info->print_m);
	return (1);
}

void	*philosophize(void *data)
{
	t_philo	*p;

	p = (t_philo *)data;
	// printf("%d\n", p->id);
	// printf("%ld\n", get_time(p->info->create_time));
	if (p->id % 2)
		usleep(15000);
	while (p->nb_eat != p->info->nb_eat)
	{
		if (take_forks(p))
			return (NULL);
		if (eat(p))
			return (NULL);
		replace_forks(p);
		if (ft_sleep(p))
			return (NULL);
		if (think(p))
			return (NULL);
	}
	return (NULL);
}
