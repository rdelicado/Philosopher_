/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:23:04 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/22 12:08:34 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// Definiciones de colores
# define RESET "\x1B[0m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"

/* structuras */

typedef struct s_philo	t_philo;

typedef struct s_table
{
	pthread_mutex_t		table;
	pthread_t			control;
	t_philo				*arr_p;
	long				n_philo;
	long				time_init;
	long				time_curr;
	long				die_to_time;
	long				eat_to_time;
	long				sleep_to_time;
	long				argv_meals;
	int					cont_eat;
	int					is_dead;
	int					has_eaten;
}						t_table;

typedef struct s_philo
{
	pthread_mutex_t		l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			thread;
	t_table				*t;
	long				last_eat;
	int					index;
	int					meals;
}						t_philo;

/* leaks.c */
void					leaks(void);
void					init_data_table(t_table *t);
void					init_data_philos(t_philo *p, t_table *t);
int						ft_strcmp(const char *s1, const char *s2);

/* philo.c */
void					checker_argv(t_table *t, char **av, int ac);
void					init_args(t_table *t, char **av, int ac);
long					time_start_prog(void);
int						main(int ac, char **av);
void					free_threads(t_table *t);

/* utils_philo.c */
void					ft_error_help(char *str);
void					ft_error(char *str);
long					ft_atol(const char *str);
int						ft_isdigit(int c);
long					ft_usleep(int time, t_table *t);

/* utils_phtreads.c */
void					set_arr_philos(t_table *t, t_philo *p);
void					set_arr_forks(t_table *t);
void					init_threads(t_table *t);
void					init_joins(t_table *t);

/* utils_simulator.c */
void					*philo_routine(void *args);
void					*controller(void *args);
void					printf_action(t_philo *p, char *str);
int						ft_dead(t_philo *p);
int						check_is_died(t_table *t);

/* utils_rutine */
void					taken_fork(t_philo *p);
void					ft_eat(t_philo *p);
void					ft_sleep(t_philo *p);
int						ft_num_meals(t_philo *p);
void					ft_simulator(t_philo *p);

/* utils_extras.c */
int						ft_exit_for_eat(t_table *t);
void					ft_meals(t_philo *p);
void					ft_last_eat(t_philo *p);

#endif