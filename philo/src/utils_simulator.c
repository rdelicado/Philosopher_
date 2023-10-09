/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:56:53 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/08 15:55:37 by rdelicad         ###   ########.fr       */
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
			if (time_start_prog() - t->arr_p[i].last_eat > t->die_to_time)
			//if (t->arr_p[i].last_eat - t->time_curr > t->die_to_time)
			{
				ft_usleep(1);
				printf_action(&t->arr_p[i], "is_dead");
				pthread_mutex_lock(&t->action);
				t->is_dead = 1;
				pthread_mutex_unlock(&t->action);
				break;
			}
			i++;
		}
	}
	return (NULL);
}

void	printf_action(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->t->action);
	if (p->t->is_dead != 1)
	{
		printf("[%ld] %d %s\n" RESET, time_start_prog() - p->t->time_curr, p->index,
		str);
	}
	pthread_mutex_unlock(&p->t->action);
}

void	*philo_routine(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	if (p->index % 2 == 0)
		ft_usleep(1);
	pthread_mutex_lock(&p->t->action);
	while (p->t->is_dead != 1)
	{
		pthread_mutex_unlock(&p->t->action);
		taken_fork(p);
		if (p->t->n_philo == 1)
			return (NULL);
		ft_eat(p);
		pthread_mutex_unlock(&p->l_fork);
		pthread_mutex_unlock(&*p->r_fork);
		ft_sleep(p);
		ft_thinking(p);
	}
	return (NULL);
}


