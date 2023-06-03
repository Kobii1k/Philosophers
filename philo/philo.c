/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:20:29 by mgagne            #+#    #+#             */
/*   Updated: 2023/06/03 13:36:57 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;

	if (argc != 5 && argc != 6)
		return (print_error(ERROR1));
	if (check_input(argc, argv))
		return (print_error("parse error"));
	philo = init_philo(argc, argv);
	if (!philo)
		return (1);


	// if (start_philo(philo))
	// 	return (1);
	return (0);
}
