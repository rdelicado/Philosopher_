/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:54:28 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/15 14:43:21 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	routine_table(t_table *t)
{
	bool	all_rt;
	bool	death_occurred;
	int		i;

	death_occurred = false;
	all_rt = false;
	i = 0;
	while (!(all_rt || death_occurred))
	{
		i = 0;
		while (i < t->n_philo)
		{
			sem_wait(t->sem);
			if (t->n_philo == t->cont_eat)
			{
				sem_post(t->sem);
				all_rt = true;
				clean(t);
				//break ;
			}
			else
				sem_post(t->sem);
			if (time_to_die(t, i))
			{
				death_occurred = true;
				clean(t);
				//break ;
			}
			i++;
		}
		/* if (all_rt || death_occurred)
		{
			while (waitpid(-1, NULL, 0) > 0)
				; 
			break ;
		} */
	}
	//exit(EXIT_SUCCESS);
	//clean(t);
}

void	routine_philos(t_philo *p)
{
	while (1)
	{
		printf_action(p, "is thinking");
		if (ft_died(p))
			break ;
		taken_fork(p);
		if (p->t->n_philo == 1)
			break ;
		ft_eat(p);
		if (ft_num_meals(p))
			break ;
		ft_sleep(p);
	}
	//exit(EXIT_SUCCESS);
	clean(p->t);
}

int	ft_died(t_philo *p)
{
	sem_wait(p->t->sem);
	if (p->t->is_dead == 1)
	{
		sem_post(p->t->sem);
		return (1);
	}
	else
		sem_post(p->t->sem);
	return (0);
}

int	time_to_die(t_table *t, int i)
{
	sem_wait(t->sem);
	if (time_start_prog() - t->arr_p[i].last_eat > t->die_to_time)
	{
		sem_post(t->sem);
		printf("%ld" RED " %d died\n" RESET, time_start_prog() - t->time_init,
			t->arr_p[i].index);
		printf("%ld %d\n", time_start_prog() - t->arr_p[i].last_eat, t->die_to_time);
		sem_wait(t->sem);
		t->is_dead = 1;
		sem_post(t->sem);
		return (1);
	}
	else
		sem_post(t->sem);
	return (0);
}

void	printf_action(t_philo *p, char *str)
{
	sem_wait(p->t->sem);
	if (p->t->is_dead != 1)
	{
		if (ft_strcmp(str, "died") == 0)
			printf("%ld" RED " %d %s\n" RESET, time_start_prog()
				- p->t->time_init, p->index, str);
		else if (ft_strcmp(str, "is eating") == 0)
			printf("%ld" YELLOW " %d %s\n" RESET, time_start_prog()
				- p->t->time_init, p->index, str);
		else if (ft_strcmp(str, "has taken a fork") == 0)
			printf("%ld" GREEN " %d %s\n" RESET, time_start_prog()
				- p->t->time_init, p->index, str);
		else if (ft_strcmp(str, "is thinking") == 0)
			printf("%ld" BLUE " %d %s\n" RESET, time_start_prog()
				- p->t->time_init, p->index, str);
		else if (ft_strcmp(str, "is sleeping") == 0)
			printf("%ld" MAGENTA " %d %s\n" RESET, time_start_prog()
				- p->t->time_init, p->index, str);
	}
	sem_post(p->t->sem);
}
