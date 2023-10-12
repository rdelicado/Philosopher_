/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:56:53 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/12 12:00:03 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*controller(void *args)
{
	t_table	*t;
	int		i;

	t = (t_table *)args;
	i = 0;
	while (t->is_dead != 1)
	{
		i = 0;
		while (i < t->n_philo)
		{
			pthread_mutex_lock(&t->table);
			if (t->n_philo == t->cont_eat)
			{
				pthread_mutex_unlock(&t->table);
				return (0);
			}
			else
				pthread_mutex_unlock(&t->table);
			if (time_to_die(t, i))
				return (NULL);
			i++;
		}
	}
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

int	time_to_die(t_table *t, int i)
{
	pthread_mutex_lock(&t->table);
	if (time_start_prog() - t->arr_p[i].last_eat > t->die_to_time)
	{
		pthread_mutex_unlock(&t->table);
		printf("%ld" RED " %d died\n" RESET, time_start_prog()
				- t->time_curr, t->arr_p->index);
		pthread_mutex_lock(&t->table);
		t->is_dead = 1;
		pthread_mutex_unlock(&t->table);
		return (1);
	}
	else
		pthread_mutex_unlock(&t->table);
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

void	*philo_routine(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	/* if (p->index % 2 == 0)
		ft_usleep(1, p->t); */
	while (1)
	{
		printf_action(p, "is thinking");
		if (ft_dead(p))
			break ;
		taken_fork(p);
		if (p->t->n_philo == 1)
			return (NULL);
		ft_eat(p);
		if (ft_num_meals(p))
			return (NULL);
		ft_sleep(p);
	}
	return (NULL);
}
