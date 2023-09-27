/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagne <mgagne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:19:31 by mgagne            #+#    #+#             */
/*   Updated: 2023/09/27 14:05:09 by mgagne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define ERROR1 "./philo [nb_of_philo] [time_die] [time_eat] [time_sleep] \
[nb_of_times_philo_must_eat]\n"
# define ERROR2 "parse error: empty parameter.\n"
# define ERROR3 "parse error: parameters must be positive numbers.\n"
# define ERROR4 "parse error: parameters must be between 1 and INT_MAX.\n"
# define ERROR99 "malloc error\n"

// # define EAT	"\x1b[32mis eating\x1b[0m"
# define EAT	"is eating"
# define THINK	"\x1b[34mis thinking\x1b[0m"
# define SLEEP	"\x1b[35mis sleeping\x1b[0m"
# define DEAD	"\x1b[31mdied\x1b[0m"
# define FORK	"\x1b[33mhas taken a fork\x1b[0m"

typedef struct s_info
{
	long long int	nb_philo;
	long long int	t_die;
	long long int	t_eat;
	long long int	t_sleep;
	long long int	nb_eat;
	long long int	create_time;
	int				ac;
	int				alive;
	int				*int_tab;
	int				max_eat;
	pthread_mutex_t	print_m;
	pthread_mutex_t	dead_m;
	pthread_mutex_t	start_end;
	pthread_mutex_t	*fork_m;
}				t_info;

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	long long int	eat_time;
	int				left_fork;
	int				right_fork;
	t_info			*info;

}				t_philo;

//utils.c
size_t			ft_strlen(const char *s);
void			print_error(char *str);
long long		ft_atoll(const char *str);
long			get_time(long create_time);
void			ft_fill_tab(t_info *info);

//init.c
t_info			*init_info(int argc, char **argv);
int				check_input(int argc, char **argv);
pthread_mutex_t	*init_forks(int n);
pthread_t		*init_philo(t_info *info);

//process.c
void			*philosophize(void *data);
int				think(t_philo *p);
int				ft_sleep(t_philo *p);
int				eat(t_philo *p);
int				take_forks(t_philo *p);

//process_utils.c
void			replace_fork(t_philo *p, int fork_id);
int				take_fork(t_philo *p, int fork_id);
int				ft_usleep(t_philo *p, long long t_sleep);
int				check_death(t_philo *p);
void			philosophize_limited(t_philo *p);

//close.c
void			destroy_mutexes(t_info *info);
void			wait_threads(t_info *info, pthread_t *philo_threads);
void			free_all(t_info *info, pthread_t *philo_threads);

#endif
