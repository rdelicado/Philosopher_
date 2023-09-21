/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 08:52:33 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/21 21:35:29 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	leaks(void)
{
	system("leaks -q philo");
}

void	init_philo_struct(t_table *t)
{
	t->n_philo = -1;
	t->time_init = -1;
	t->time_curr = -1;
	t->arr_p = NULL;
	t->arr_m = NULL;
}

void	init_data_philos(t_philo *p)
{
	p->index = -1;
	p->die_to_time = -1;
	p->eat_to_time = -1;
	p->sleep_to_time = -1;
	p->thing_to_time = -1;
	p->optional = -1;
}
