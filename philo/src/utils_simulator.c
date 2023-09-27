/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:56:53 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/27 20:28:24 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*controller(void *args)
{
	t_table	*t;

	t = (t_table *)args;
	(void)t;
	sleep(1);
	printf("Controlador creado\n");
	return (NULL);
}

void	*philo_routine(void *args)
{
	/* printf("tiempo init %ld\n", time_start_prog(t) - t->time_init);
	t->time_curr = time_start_prog(t);
	for (int i = 0; i < 100; i++){
		ft_usleep(200);
		printf("tiempo init %ld\n", time_start_prog(t) - t->time_curr);
	} */
	t_philo	*p;

	p = (t_philo *)args;
	p->time_curr = time_start_prog(p);
	while (1)
	{
		//coger tenedor
		taken_fork(p);
		// comer
		printf("%ld %d is eating\n", time_start_prog(p) - p->time_curr, p->index);
		ft_usleep(p->eat_to_time);
		//dormir
		printf("%ld %d is sleeping\n", time_start_prog(p) - p->time_curr, p->index);
		ft_usleep(p->sleep_to_time);
		//pensar
		printf("%ld %d is thinking\n", time_start_prog(p) - p->time_curr, p->index);
		ft_usleep(p->thing_to_time);
	}
	//morir
	//printf("%d %d died", time_start_prog(p) - p->time_curr, p->index);
/* ◦ timestamp_in_ms X has taken a fork → ha tomado un tenedor
◦ timestamp_in_ms X is eating              → esta comiendo
◦ timestamp_in_ms X is sleeping          → esta durmiendo
◦ timestamp_in_ms X is thinking           → esta pensando
◦ timestamp_in_ms X died                     → murio */
	return (NULL);
}

void	taken_fork(t_philo *p)
{
	pthread_mutex_lock(p->l_fork[p->index]);
	printf("%ld %d has taken a fork\n", time_start_prog(p) - p->time_curr, p->index);
	pthread_mutex_unlock(p->l_fork[p->index]);
}