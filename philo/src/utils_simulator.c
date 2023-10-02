/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:56:53 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/02 19:35:00 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*controller(void *args)
{
	t_table	*t;
	int		i;

	t = (t_table *)args;
	//printf("Controlador creado\n");
	i = 0;
	/* while (++i < t->n_philo)
	{
		if (time_start_prog(t) - t->arr_p[i].last_eat)
		{
			ft_usleep(t->die_to_time - t->eat_to_time);
			printf("%ld %d died\n", time_start_prog(p) - p->time_curr,
				p->index);
			exit (0);
		}
		else
			ft_usleep(p->t->sleep_to_time);
	} */
	return (NULL);
}

void	ft_printf(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->t->dead_mutex);
	if (p->t->is_dead != 1)
	{
		printf("[%ld] %d %s\n" RESET, time_start_prog(p->t) - p->t->time_curr, p->index,
		str);
	}
	pthread_mutex_unlock(&p->t->dead_mutex);
}

void	*philo_routine(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	p->t->time_curr = time_start_prog(p->t);
	if (p->index % 2 == 0)
		ft_usleep(1);
	while (1)
	{
		ft_printf(p, "is thinking");
		taken_fork(p);
		ft_printf(p, "is sleeping");
		ft_usleep(p->t->sleep_to_time);
	}
	return (NULL);
}

void	taken_fork(t_philo *p)
{
	if (pthread_mutex_lock(&p->l_fork) == 0)
		ft_printf(p, "has taken a fork");
	if (pthread_mutex_lock(&*p->r_fork) == 0)
		ft_printf(p, "has taken a fork");
	ft_printf(p, "is eating");
	p->last_eat = time_start_prog(p->t);
	printf("ultima vez que comio %ld\n", p->last_eat);
	ft_usleep(p->t->eat_to_time);
	pthread_mutex_unlock(&p->l_fork);
	pthread_mutex_unlock(&*p->r_fork);
}
