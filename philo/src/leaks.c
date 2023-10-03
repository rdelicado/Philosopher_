/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 08:52:33 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/03 17:31:58 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	leaks(void)
{
	system("leaks -q philo");
}

void	init_data_table(t_table *t)
{
	t->die_to_time = -1;
	t->eat_to_time = -1;
	t->sleep_to_time = -1;
	t->thing_to_time = -1;
	t->n_philo = -1;
	t->is_dead = 0;
	t->time_init = -1;
	t->time_curr = -1;
	t->arr_p = NULL;
	t->arr_m = NULL;
}

void	init_data_philos(t_philo *p, t_table *t)
{
	p->t = t;
	p->index = -1;
	p->optional = -1;
}
