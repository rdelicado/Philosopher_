/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:23:04 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/08 15:50:22 by rdelicad         ###   ########.fr       */
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

// Definiciones de colores
#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

/* structuras */

typedef struct s_philo t_philo;

typedef struct s_table
{
	pthread_mutex_t	time;
	pthread_mutex_t action;
	pthread_mutex_t	*arr_m;
	pthread_t		control;
	t_philo			*arr_p;
	long			time_init;
	long			time_curr;
	int				is_dead;
	int				die_to_time;
	int				eat_to_time;
	int				sleep_to_time;
	int				thing_to_time;
	int				num_meals;
	int				n_philo;
}	t_table;

typedef struct s_philo
{
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		thread;
	t_table			*t;
	long			last_eat;
	int				index;
	int				meals;
}	t_philo;

/* leaks.c */
void	leaks(void);
void	init_data_table(t_table *t);
void	init_data_philos(t_philo *p, t_table *t);

/* philo.c */
void	checker_argv(t_table *t, char **av);
long	time_start_prog(void);
int		main(int ac, char **av);
void	free_threads(t_table *t);

/* utils_philo.c */
void	ft_error_help(char *str);
void	ft_error(char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
long	ft_usleep(int time);

/* utils_phtreads.c */
void	set_arr_philos(t_table *t, t_philo *p);
void	set_arr_forks(t_table *t);
void	init_threads(t_table *t);
void	init_joins(t_table *t);

/* utils_simulator.c */
void	*philo_routine(void *args);
void	*controller(void *args);
void	printf_action(t_philo *p, char *str);

/* utils_rutine */
void	taken_fork(t_philo *p);
void	ft_eat(t_philo *p);
void	ft_sleep(t_philo *p);
void	ft_thinking(t_philo *p);

#endif