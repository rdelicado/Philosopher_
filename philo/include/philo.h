/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:23:04 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/21 18:56:10 by rdelicad         ###   ########.fr       */
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

typedef struct s_data
{
	pthread_t		thread;
	pthread_mutex_t	mutex;
	int				index;
	int				die_to_time;
	int				eat_to_time;
	int				sleep_to_time;
	int				thing_to_time;
	int				optional;
}	t_data;

typedef struct s_philo
{
	int				n_philo;
	long			time_init;
	long			time_curr;
	t_data			*arr_p;
	t_data			*arr_m;
}	t_philo;

/* leaks.c */
void	leaks(void);
void	init_philo_struct(t_philo *p);
void	init_data_philos(t_data *d);

/* philo.c */
void	checker_argv(t_philo *p, t_data *d, char **av);
int		time_start_prog(t_philo *p);
int		time_curr_prog(t_philo *p);
int		main(int ac, char **av);

/* utils_philo.c */
void	ft_error_help(char *str);
void	ft_error(char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

/* utils_phtreads.c */
void	*philo_routine(void *args);
void	*controller(void *args);
void	create_philos(t_philo *p);
void	set_arr_philos(t_philo *p);
void	set_arr_forks(t_philo *p);

#endif