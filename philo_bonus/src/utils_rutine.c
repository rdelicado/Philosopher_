/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 09:06:58 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/16 10:40:41 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	taken_fork(t_philo *p)
{
	sem_wait(p->t->forks);
	printf_action(p, "has taken a fork");
	if (p->t->n_philo != 1)
	{
		sem_wait(p->t->forks);
		printf_action(p, "has taken a fork");
	}
	else
	{
		sem_post(p->t->forks);
		return ;
	}
}

void	ft_eat(t_philo *p)
{
	sem_wait(p->t->sem);
	p->last_eat = time_start_prog();
	printf("(funcion eat) time philo %d: %ld\n", p->index, p->last_eat);
	sem_post(p->t->sem);
	printf_action(p, "is eating");
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

void	ft_simulator(t_philo *p)
{
	printf_action(p, "is thinking");
	taken_fork(p);
	if (p->t->n_philo == 1)
		return ;
	ft_eat(p);
	if (ft_num_meals(p))
		return ;
	ft_sleep(p);
}