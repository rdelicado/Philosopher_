/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:56:34 by rdelicad          #+#    #+#             */
/*   Updated: 2023/11/28 20:19:35 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_last_eat(t_philo *p)
{
	sem_wait(p->t->sem);
	p->last_eat = time_start_prog();
	sem_post(p->t->sem);
}

void	ft_meals(t_philo *p)
{
	sem_wait(p->t->sem);
	p->meals++;
	sem_post(p->t->sem);
}

int	ft_exit_for_eat(t_table *t)
{
	if (t->num_meals == -1)
		return (0);
	sem_wait(t->sem);
	if (t->cont_eat == t->n_philo)
	{
		sem_post(t->sem);
		return (1);
	}
	else
		sem_post(t->sem);
	return (0);
}
