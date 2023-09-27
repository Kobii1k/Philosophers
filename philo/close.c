/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:14:31 by mgagne            #+#    #+#             */
/*   Updated: 2023/09/27 11:46:04 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_info *info, pthread_t *philo_threads)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
		pthread_join(philo_threads[i], NULL);
	return ;
}

void	destroy_mutexes(t_info *info)
{
	int	i;

	pthread_mutex_destroy(&info->dead_m);
	pthread_mutex_destroy(&info->start_end);
	pthread_mutex_destroy(&info->print_m);
	i = -1;
	while (++i < info->nb_philo)
		pthread_mutex_destroy(&info->fork_m[i]);
	return ;
}

void	free_all(t_info *info, pthread_t *philo_threads)
{
	free(philo_threads);
	free(info->fork_m);
	free(info->int_tab);
	free(info);
	return ;
}
