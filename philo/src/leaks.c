/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 08:52:33 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/02 18:31:22 by rdelicad         ###   ########.fr       */
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
	t->arr_p = NULL;
	t->arr_m = NULL;
}

void	init_data_philos(t_philo *p, t_table *t)
{
	p->t = t;
	p->index = -1;
	p->time_init = -1;
	p->time_curr = -1;
	p->optional = -1;
}
