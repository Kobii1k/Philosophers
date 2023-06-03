/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:19:31 by mgagne            #+#    #+#             */
/*   Updated: 2023/06/03 13:05:45 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define ERROR1 "./philo [nb_of_philo] [time_die] [time_eat] [time_sleep] \
[nb_of_times_philo_must_eat]\n"

typedef struct s_philo
{
	int	nb_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	nb_eat;
}				t_philo;

//utils.c
size_t	ft_strlen(const char *s);
int		print_error(char *str);
int		ft_atoi(const char *str);

//init.c
t_philo	*init_philo(int argc, char **argv);
int		check_input(int argc, char **argv);

#endif
