/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:20:29 by mgagne            #+#    #+#             */
/*   Updated: 2023/09/27 13:53:43 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo(t_info *info, int id)
{
	t_philo			*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (print_error(ERROR99), NULL);
	philo->id = id;
	philo->info = info;
	philo->nb_eat = 0;
	philo->eat_time = info->create_time;
	philo->right_fork = id;
	if (id == 1)
		philo->left_fork = info->nb_philo;
	else
		philo->left_fork = id - 1;
	return (philo);
}

pthread_t	*start_process(t_info *info, pthread_t	*philo_threads)
{
	int				i;
	t_philo			*philo;
	struct timeval	time;

	i = 0;
	pthread_mutex_lock(&info->start_end);
	info->create_time = 0;
	while (i < info->nb_philo)
	{
		philo = new_philo(info, i + 1);
		if (!philo)
			return (free(info->fork_m), free(info->int_tab), free(info),
				free(philo_threads), NULL);
		pthread_create(&philo_threads[i], NULL, philosophize, philo);
		i++;
	}
	gettimeofday(&time, NULL);
	info->create_time = (long)(time.tv_usec / 1000 + time.tv_sec * 1000);
	pthread_mutex_unlock(&info->start_end);
	return (philo_threads);
}

int	main(int argc, char **argv)
{
	t_info		*info;
	pthread_t	*philo_threads;

	if (argc != 5 && argc != 6)
		return (print_error(ERROR1), 1);
	if (check_input(argc, argv))
		return (1);
	info = init_info(argc, argv);
	if (!info)
		return (1);
	philo_threads = init_philo(info);
	if (!philo_threads)
		return (1);
	philo_threads = start_process(info, philo_threads);
	if (!philo_threads)
		return (1);
	wait_threads(info, philo_threads);
	destroy_mutexes(info);
	free_all(info, philo_threads);
	return (0);
}
