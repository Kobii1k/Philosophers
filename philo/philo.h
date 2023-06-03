/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:19:31 by mgagne            #+#    #+#             */
/*   Updated: 2023/06/03 22:28:22 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define ERROR1 "./philo [nb_of_philo] [time_die] [time_eat] [time_sleep] \
[nb_of_times_philo_must_eat]\n"
# define ERROR2 "parse error: empty parameter.\n"
# define ERROR3 "parse error: parameters must be digits.\n"
# define ERROR4 "parse error: parameters must be between 1 and INT_MAX.\n"
# define ERROR5 "parse error: time variables must be >= 60ms.\n"
# define ERROR99 "malloc error\n"

typedef struct s_philo
{
	int	nb_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	nb_eat;
	int ac;
}				t_philo;

//utils.c
size_t	ft_strlen(const char *s);
void	print_error(char *str);
int		ft_atoi(const char *str);

//init.c
t_philo	*init_philo(int argc, char **argv);
int		check_input(int argc, char **argv);

#endif
