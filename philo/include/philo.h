/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:23:04 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/26 21:51:00 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>

/* structuras */

typedef struct s_philo
{
	pthread_t		thread;
	int				index;
	int				die_to_time;
	int				eat_to_time;
	int				sleep_to_time;
	int				thing_to_time;
	long			time_init;
	long			time_curr;
	int				optional;
}	t_philo;

typedef struct s_table
{
	int				n_philo;
	t_philo			*arr_p;
	pthread_mutex_t	*arr_m;
}	t_table;

/* leaks.c */
void	leaks(void);
void	init_philo_struct(t_table *p);
void	init_data_philos(t_philo *d);

/* philo.c */
void	checker_argv(t_table *p, t_philo *d, char **av);
long	time_start_prog(t_philo *p);
int		main(int ac, char **av);

/* utils_philo.c */
void	ft_error_help(char *str);
void	ft_error(char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
long	ft_usleep(int time);

/* utils_phtreads.c */
void	set_arr_philos(t_table *t, t_philo *p);
void	set_arr_forks(t_table *p);
void	init_threads(t_table *t);
void	*philo_routine(void *args);
void	*controller(void *args);

/* utils_simulator.c */

#endif