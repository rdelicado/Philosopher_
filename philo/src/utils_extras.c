/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:13:38 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/17 21:18:22 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_last_eat(t_philo *p)
{
	pthread_mutex_lock(&p->t->table);
	p->last_eat = time_start_prog();
	pthread_mutex_unlock(&p->t->table);
}

void	ft_meals(t_philo *p)
{
	pthread_mutex_lock(&p->t->table);
	p->meals++;
	//printf("eat: %d\n", p->meals);
	pthread_mutex_unlock(&p->t->table);
}

/* void	ft_cont_eat_global_philos(t_philo *p)
{
	pthread_mutex_lock(&p->t->table);
	p->t->cont_eat++;
	pthread_mutex_unlock(&p->t->table);
} */

/* int	ft_num_meals(t_philo *p)
{
	pthread_mutex_lock(&p->t->table);
	if (p->meals_philo == p->t->num_meals_argv)
	{
		ft_cont_eat_global_philos(p);
		return (1);
	}
	else
		pthread_mutex_unlock(&p->t->table);
	return (0);
} */

int	ft_exit_for_eat(t_table *t)
{

	if (t->num_meals == -1)
		return (0);
	pthread_mutex_lock(&t->table);
	if (t->n_philo == t->cont_eat)
	{
		printf("funcion: %ld\n", t->num_meals);
		//pthread_mutex_unlock(&t->table);
		printf("entra aqui?");
		return (1);
	}
	else
		pthread_mutex_unlock(&t->table);
	return (0);
}


