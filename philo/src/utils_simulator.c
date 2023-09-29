/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:56:53 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/29 09:51:36 by rdelicad         ###   ########.fr       */
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
	t_philo	*p;

	p = (t_philo *)args;
	p->time_curr = time_start_prog(p);
	if (p->index % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		taken_fork(p);
		printf(BLUE "[%ld] %d is sleeping\n" RESET, time_start_prog(p) - p->time_curr, p->index);
		ft_usleep(p->t->sleep_to_time);
		thinking_philo(p);
	}
	//morir
	//printf("%d %d died", time_start_prog(p) - p->time_curr, p->index);
	return (NULL);
}

void	taken_fork(t_philo *p)
{
	if (p->index % 2 == 0) 
	{
        // Filósofo par toma el tenedor izquierdo primero
		p->flag_l = 1;
        pthread_mutex_lock(&p->t->arr_m[p->l_fork]);
        printf(GREEN "[%ld] %d has taken a fork\n" RESET, time_start_prog(p) - p->time_curr, p->index);
		if (p->t->arr_p[p->index % p->t->n_philo].flag_l == 0)
		{
			pthread_mutex_lock(&p->t->arr_m[p->r_fork]);
			printf(GREEN "[%ld] %d has taken a fork\n" RESET, time_start_prog(p) - p->time_curr, p->index);
		}
		else
			pthread_mutex_unlock(&p->t->arr_m[p->l_fork]);
    } 
	else 
	{
        // Filósofo impar toma el tenedor derecho primero
		p->flag_l = 1;
        pthread_mutex_lock(&p->t->arr_m[p->r_fork]);
        printf(GREEN "[%ld] %d has taken a fork\n" RESET, time_start_prog(p) - p->time_curr, p->index);
		if (p->t->arr_p[p->index % p->t->n_philo].flag_l == 0)
		{
			pthread_mutex_lock(&p->t->arr_m[p->l_fork]);
			printf(GREEN "[%ld] %d has taken a fork\n" RESET, time_start_prog(p) - p->time_curr, p->index);
		}
		else
			pthread_mutex_unlock(&p->t->arr_m[p->r_fork]);
    }
	/* if (p->t->arr_p[(p->index + 1) % p->t->n_philo].flag_l == 0 && p->t->arr_p[p->index % p->t->n_philo].flag_l == 0)
	{
		printf("filosof: %d\n", p->index);
		printf("flag izq: %d\n", p->flag_l);
		if (p->index == p->t->n_philo)
			printf("flag drch: %d\n", p->t->arr_p[0].flag_l);
		else
			printf("flag drch: %d\n", p->t->arr_p[p->index + 1].flag_l);
		p->flag_l = 1;
		printf(GREEN "[%ld] %d has taken a fork\n" RESET, time_start_prog(p) - p->time_curr, p->index);
		printf(GREEN "[%ld] %d has taken a fork\n" RESET, time_start_prog(p) - p->time_curr, p->index);
		printf(RED "[%ld] %d is eating\n" RESET, time_start_prog(p) - p->time_curr, p->index);
	}
	else
		thinking_philo(p); */
	printf(RED "[%ld] %d is eating\n" RESET, time_start_prog(p) - p->time_curr, p->index);
	ft_usleep(p->t->eat_to_time);
	pthread_mutex_unlock(&p->t->arr_m[p->l_fork]);
	pthread_mutex_unlock(&p->t->arr_m[p->r_fork]);
	p->flag_l = 0;
}

void	thinking_philo(t_philo *p)
{
	printf(MAGENTA "[%ld] %d is thinking\n" RESET, time_start_prog(p) - p->time_curr, p->index);
	//ft_usleep(p->t->die_to_time / 3);
	while (1)
	{
		//ft_usleep(1);
		if (p->t->arr_p[p->index % p->t->n_philo].flag_l == 0 && p->t->arr_p[(p->index + 1) % p->t->n_philo].flag_l == 0)
		{
			taken_fork(p);
			break;
		}
	}
}

