/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 08:52:33 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/21 18:52:15 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	leaks(void)
{
	system("leaks -q philo");
}

void	init_philo_struct(t_philo *p)
{
	p->n_philo = -1;
	p->time_init = -1;
	p->time_curr = -1;
	p->arr_p = NULL;
	p->arr_m = NULL;
}

void	init_data_philos(t_data *d)
{
	d->index = -1;
	d->die_to_time = -1;
	d->eat_to_time = -1;
	d->sleep_to_time = -1;
	d->thing_to_time = -1;
	d->optional = -1;
}
