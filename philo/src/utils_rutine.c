/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rutine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 09:06:58 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/17 21:02:30 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	taken_fork(t_philo *p)
{
	pthread_mutex_lock(&p->t->table);
	if (p->t->is_dead != 1)
	{
		pthread_mutex_unlock(&p->t->table);
		pthread_mutex_lock(&p->l_fork);
		printf_action(p, "has taken a fork");
		if (p->t->n_philo != 1)
		{
			pthread_mutex_lock(&*p->r_fork);
			printf_action(p, "has taken a fork");
		}
		else
		{
			//pthread_mutex_unlock(&p->l_fork);
			return ;
		}
	}
	else
	{
		pthread_mutex_unlock(&p->t->table);
		return ;
	}
}

void	ft_eat(t_philo *p)
{
	pthread_mutex_lock(&p->t->table);
	if (p->t->is_dead != 1)
	{
		pthread_mutex_unlock(&p->t->table);
		ft_last_eat(p);
		printf_action(p, "is eating");
		ft_meals(p);
		ft_usleep(p->t->eat_to_time, p->t);
		pthread_mutex_unlock(&*p->r_fork);
		pthread_mutex_unlock(&p->l_fork);
	}
	else
	{
		pthread_mutex_unlock(&p->t->table);
		return ;
	}
}

void	ft_sleep(t_philo *p)
{
	pthread_mutex_lock(&p->t->table);
	if (p->t->is_dead != 1)
	{
		pthread_mutex_unlock(&p->t->table);
		printf_action(p, "is sleeping");
		ft_usleep(p->t->sleep_to_time, p->t);
	}
	else
	{
		pthread_mutex_unlock(&p->t->table);
		return ;
	}
}

void	ft_num_meals(t_philo *p)
{
	if (p->meals == p->t->num_meals) // un philo ya ha comido todas las vec
	{
		pthread_mutex_lock(&p->t->table);
		p->t->cont_eat++; // un philo ya ha comido
		printf("cont eat: %d\n", p->t->cont_eat);
		pthread_mutex_unlock(&p->t->table);
	}
}

void	ft_simulator(t_philo *p)
{
	taken_fork(p);
	if (p->t->n_philo == 1)
		return ;
	ft_eat(p);
	ft_num_meals(p); // si ya un philo ha comido todas las veces,
	ft_sleep(p);
	printf_action(p, "is thinking");
}
