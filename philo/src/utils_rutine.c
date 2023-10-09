/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 09:06:58 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/08 15:54:18 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	taken_fork(t_philo *p)
{
	pthread_mutex_lock(&p->l_fork);
	printf_action(p, "has taken a fork");
	if (p->t->n_philo != 1)
	{
		pthread_mutex_lock(&*p->r_fork);
		printf_action(p, "has taken a fork");
	}
	else
		return ;
}

void	ft_eat(t_philo *p)
{
	//printf("incio last time comida %d %lu\n",p->meals, p->last_eat);
	printf_action(p, "is eating");
	ft_usleep(p->t->eat_to_time);
	pthread_mutex_lock(&p->t->time);
	p->last_eat = time_start_prog();
	p->meals++;
	pthread_mutex_unlock(&p->t->time);
	if (p->meals == p->t->num_meals)
		{
			printf("num. comidas; %d\n", p->meals);
			return ;
		}
}

void	ft_sleep(t_philo *p)
{
	printf_action(p, "is sleeping");
	ft_usleep(p->t->sleep_to_time);
}

void	ft_thinking(t_philo *p)
{
	printf_action(p, "is thinking");
}