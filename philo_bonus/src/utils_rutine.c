/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 09:06:58 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/15 14:21:10 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	taken_fork(t_philo *p)
{
	if (p->t->n_philo != 1)
	{
		sem_wait(p->t->forks);
		printf_action(p, "has taken a fork");
		printf_action(p, "has taken a fork");
		sem_post(p->t->forks);
	}
	else
	{
		return ;
	}
}

void	ft_eat(t_philo *p)
{
	printf_action(p, "is eating");
	sem_wait(p->t->sem);
	p->last_eat = time_start_prog();
	sem_post(p->t->sem);
	ft_usleep(p->t->eat_to_time, p->t);
	sem_wait(p->t->sem);
	p->meals++;
	sem_post(p->t->sem);
	sem_post(p->t->forks);
	sem_post(p->t->forks);
}

void	ft_sleep(t_philo *p)
{
	printf_action(p, "is sleeping");
	ft_usleep(p->t->sleep_to_time, p->t);
}

int	ft_num_meals(t_philo *p)
{
	if (p->meals == p->t->num_meals)
	{
		sem_wait(p->t->sem);
		p->t->cont_eat++;
		sem_post(p->t->sem);
		return (1);
	}
	return (0);
}