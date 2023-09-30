/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:56:53 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/30 09:01:08 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*controller(void *args)
{
	t_table	*t;
	int		i;
	
	(void)t;
	t = (t_table *)args;
	printf("Controlador creado\n");
	i = 0;
	/* while (1)
	{
		if (t->die_to_time < t->arr_p[i].last_eat)
		{
			ft_usleep(t->die_to_time - t->eat_to_time);
			printf("%ld %d died\n", time_start_prog(p) - p->time_curr, p->index);
			exit (0);
		}
		else
			ft_usleep(p->t->sleep_to_time);
	} */
	return (NULL);
}

void	*philo_routine(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	p->time_curr = time_start_prog(p);
	if (p->index % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		printf(MAGENTA "[%ld] %d is thinking\n" RESET, time_start_prog(p) - p->time_curr, p->index);
		taken_fork(p);
		printf(BLUE "[%ld] %d is sleeping\n" RESET, time_start_prog(p) - p->time_curr, p->index);
		if (p->t->eat_to_time + p->t->sleep_to_time > p->t->die_to_time)
		{
			ft_usleep(p->t->die_to_time - p->t->eat_to_time);
			printf("%ld %d died\n", time_start_prog(p) - p->time_curr, p->index);
			exit (0);
		}
		else
			ft_usleep(p->t->sleep_to_time);
	}
	return (NULL);
}

void	taken_fork(t_philo *p)
{
	p->last_eat = time_start_prog;
	if (pthread_mutex_lock(&p->l_fork) == 0)
		printf(GREEN "[%ld] %d has taken a fork\n" RESET, time_start_prog(p) - p->time_curr, p->index);
	if	(pthread_mutex_lock(&*p->r_fork) == 0)
		printf(GREEN "[%ld] %d has taken a fork\n" RESET, time_start_prog(p) - p->time_curr, p->index);
	printf(RED "[%ld] %d is eating\n" RESET, time_start_prog(p) - p->time_curr, p->index);
	ft_usleep(p->t->eat_to_time);
	pthread_mutex_unlock(&p->l_fork);
	pthread_mutex_unlock(&*p->r_fork);
}
