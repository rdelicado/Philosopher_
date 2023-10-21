/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:56:53 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/21 17:10:31 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*controller(void *args)
{
	t_table	*t;

	t = (t_table *)args;
	while (1)
	{
		if (ft_exit_for_eat(t))
			break ;
		if (check_is_died(t))
			break ;
	}
	return (NULL);
}

void	*philo_routine(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	if (p->index % 2 == 0)
		ft_usleep(1, p->t);
	ft_simulator(p);
	if (p->t->n_philo == 1)
		return (NULL);
	if (ft_num_meals(p))
		return (NULL);
	if (ft_dead(p))
		return (NULL);
	return (NULL);
}

int	ft_dead(t_philo *p)
{
	pthread_mutex_lock(&p->t->table);
	if (p->t->is_dead == 1)
	{
		pthread_mutex_unlock(&p->t->table);
		return (1);
	}
	else
		pthread_mutex_unlock(&p->t->table);
	return (0);
}

int	check_is_died(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philo)
	{
		pthread_mutex_lock(&t->table);
		if (time_start_prog() - t->arr_p[i].last_eat >= t->die_to_time)
		{
			pthread_mutex_unlock(&t->table);
			pthread_mutex_lock(&t->table);
			t->is_dead = 1;
			pthread_mutex_unlock(&t->table);
			pthread_mutex_lock(&t->table);
			printf("%ld" RED " %d died\n" RESET, time_start_prog()
				- t->time_curr, t->arr_p[i].index);
			pthread_mutex_unlock(&t->table);
			return (1);
		}
		else
			pthread_mutex_unlock(&t->table);
		i++;
	}
	return (0);
}

void	printf_action(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->t->table);
	if (p->t->is_dead != 1)
	{
		if (ft_strcmp(str, "died") == 0)
			printf("%ld" RED " %d %s\n" RESET, time_start_prog()
				- p->t->time_curr, p->index, str);
		else if (ft_strcmp(str, "is eating") == 0)
			printf("%ld" YELLOW " %d %s\n" RESET, time_start_prog()
				- p->t->time_curr, p->index, str);
		else if (ft_strcmp(str, "has taken a fork") == 0)
			printf("%ld" GREEN " %d %s\n" RESET, time_start_prog()
				- p->t->time_curr, p->index, str);
		else if (ft_strcmp(str, "is thinking") == 0)
			printf("%ld" BLUE " %d %s\n" RESET, time_start_prog()
				- p->t->time_curr, p->index, str);
		else if (ft_strcmp(str, "is sleeping") == 0)
			printf("%ld" MAGENTA " %d %s\n" RESET, time_start_prog()
				- p->t->time_curr, p->index, str);
	}
	pthread_mutex_unlock(&p->t->table);
}
