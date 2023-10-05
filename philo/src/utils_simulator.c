/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:56:53 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/04 16:03:37 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*controller(void *args)
{
	t_table	*t;
	int		i;

	t = (t_table *)args;
	while (t->is_dead != 1)
	{
		i = 0;
		while (i < t->n_philo)
		{
			if (time_start_prog(t) - t->arr_p[i].last_eat > t->die_to_time)
			{
				printf_action(&t->arr_p[i], "is_dead");
				//pthread_mutex_lock(&t->action);
				t->is_dead = 1;
				//pthread_mutex_unlock(&t->action);
				break;
			}
			i++;
		}
	}
	return (NULL);
}

void	printf_action(t_philo *p, char *str)
{
	//pthread_mutex_lock(&p->t->action);
	if (p->t->is_dead != 1)
	{
		printf("[%ld] %d %s\n" RESET, time_start_prog(p->t) - p->t->time_curr, p->index,
		str);
	}
	//pthread_mutex_unlock(&p->t->action);
}

void	*philo_routine(void *args)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)args;
	p->t->time_curr = time_start_prog(p->t);
	if (p->index % 2 == 0)
		ft_usleep(0.01);
	while (p->t->is_dead != 1)
	{
		printf_action(p, "is thinking");
		taken_fork(p);
		if (p->t->n_philo != 1)
		{
			printf_action(p, "is sleeping");
			ft_usleep(p->t->sleep_to_time);
		}
		else
			break;
	}
	i = 0;
	while (i++ < p->t->n_philo)
	{
		pthread_mutex_destroy(&p->l_fork);
		pthread_mutex_destroy(p->r_fork);
	}
	return (NULL);
}

void	taken_fork(t_philo *p)
{
	pthread_mutex_lock(&p->l_fork);
	printf_action(p, "has taken a fork");
	if (p->t->n_philo != 1)
	{
		pthread_mutex_lock(&*p->r_fork);
		printf_action(p, "has taken a fork");
		printf_action(p, "is eating");
		p->last_eat = time_start_prog(p->t);
		ft_usleep(p->t->eat_to_time);
		p->optional++;
		pthread_mutex_unlock(&p->l_fork);
		pthread_mutex_unlock(&*p->r_fork);
	}
	else
		pthread_mutex_unlock(&p->l_fork);
}
