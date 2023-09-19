/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:23:04 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/19 16:21:26 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

typedef struct s_philo
{
	int	n_philo;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	each_time;
}	t_philo;

/* leaks.c */
void	leaks(void);

/* philo.c */
int		main(int ac, char **av);
void	checker_argv(t_philo *p, char **av);
void	create_philos(t_philo *p);

/* utils_philo.c */
void	init_philo_struct(t_philo *p);
void	ft_error(char *str);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);

/* utils_phtreads.c */
void	*controller(void *args);

#endif