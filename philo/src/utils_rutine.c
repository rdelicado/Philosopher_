/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 09:06:58 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/15 22:05:22 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	taken_fork(t_philo *p)
{
	if (!ft_dead(p))
	{
		pthread_mutex_lock(&p->l_fork);
		printf_action(p, "has taken a fork");
		if (p->t->n_philo != 1)
		{
			pthread_mutex_lock(&*p->r_fork);
			printf_action(p, "has taken a fork");
		}
		else
		{
			pthread_mutex_unlock(&p->l_fork);
			return ;
		}
	}
}

void	ft_eat(t_philo *p)
{
	if (!ft_dead(p))
	{
		printf_action(p, "is eating");
		pthread_mutex_lock(&p->t->table);
		p->last_eat = time_start_prog();
		pthread_mutex_unlock(&p->t->table);
		//printf("philo time: %lu\n", p->last_eat);
		ft_usleep(p->t->eat_to_time, p->t);
		pthread_mutex_lock(&p->t->table);
		p->meals++;
		pthread_mutex_unlock(&p->t->table);
		pthread_mutex_unlock(&*p->r_fork);
		pthread_mutex_unlock(&p->l_fork);
	}
	else
		return;
}

void	ft_sleep(t_philo *p)
{
	if (!ft_dead(p))
	{
		printf_action(p, "is sleeping");
		ft_usleep(p->t->sleep_to_time, p->t);
	}
}

int	ft_num_meals(t_philo *p)
{
	if (p->meals == p->t->num_meals)
	{
		pthread_mutex_lock(&p->t->table);
		p->t->cont_eat++;
		pthread_mutex_unlock(&p->t->table);
		return (1);
	}
	return (0);
}
