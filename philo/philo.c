/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:20:29 by mgagne            #+#    #+#             */
/*   Updated: 2023/06/03 22:06:51 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	start_philo(t_philo *p)
// {
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc != 5 && argc != 6)
		return (print_error(ERROR1), 1);
	if (check_input(argc, argv))
		return (1);
	philo = init_philo(argc, argv);
	if (!philo)
		return (1);
	// if (start_philo(philo))
	// 	return (1);
	return (0);
}
