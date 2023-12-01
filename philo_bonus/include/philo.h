/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:23:04 by rdelicad          #+#    #+#             */
/*   Updated: 2023/12/01 15:55:08 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>

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
	sem_t				*sem;
	sem_t				*forks;
	sem_t				*sem_meals_eaten;
	sem_t				*sem_death;
	pid_t				*child_pids;
	pid_t				pid;
	t_philo				*arr_p;
	long				n_philo;
	long				time_init;
	long				die_to_time;
	long				eat_to_time;
	long				thing_to_time;
	long				sleep_to_time;
	long				num_meals;
	int					is_dead;
}						t_table;

typedef struct s_philo
{
	t_table				*t;
	pid_t				pid;
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

/* utils_philo.c */
void					ft_error_help(char *str);
void					ft_error(char *str);
long					ft_atol(const char *str);
int						ft_isdigit(int c);
long					ft_usleep(int time, t_table *t);

/* utils_semaphores.c */
void					set_philos(t_table *t, t_philo *p);
void					set_arr_philos(t_table *t, t_philo *p, int i);
void					init_semaphores(t_table *t);
void					preclean(t_table *t);
void					clean(t_table *t);

/* simulator.c */
void					routine_table(t_table *t);
void					routine_philos(t_philo *p);
int						time_to_die(t_table *t);
int						ft_died(t_philo *p);
void					printf_action(t_philo *p, char *str);

/* utils_rutine */
void					taken_fork(t_philo *p);
void					ft_eat(t_philo *p);
void					ft_sleep(t_philo *p);
int						ft_num_meals(t_philo *p);
void					ft_simulator(t_philo *p);

/* utils_extras.c */
void					ft_last_eat(t_philo *p);
void					ft_meals(t_philo *p);
int						ft_exit_for_eat(t_table *t);
void					create_fork(t_table *t, t_philo *p);

#endif