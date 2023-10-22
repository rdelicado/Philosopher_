/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:13:38 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/22 12:05:47 by rdelicad         ###   ########.fr       */
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
	pthread_mutex_unlock(&p->t->table);
}

int	ft_exit_for_eat(t_table *t)
{
	if (t->argv_meals == -1)
		return (0);
	pthread_mutex_lock(&t->table);
	if (t->cont_eat == t->n_philo)
	{
		pthread_mutex_unlock(&t->table);
		return (1);
	}
	else
		pthread_mutex_unlock(&t->table);
	return (0);
}
