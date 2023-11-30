/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:54:28 by rdelicad          #+#    #+#             */
/*   Updated: 2023/11/30 20:44:17 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	routine_table(t_table *t)
{
	ft_exit_for_eat(t);
	while (1)
	{
		/* if (ft_exit_for_eat(t))
		{
			printf("salida2\n");
			break ;
		} */
		if (time_to_die(t))
			break ;	
	}
}

void	routine_philos(t_philo *p)
{
	if (p->index % 2 == 0)
		ft_usleep(1, p->t);
	ft_simulator(p);
	if (p->t->n_philo == 1)
		return ;
	/* else if (ft_num_meals(p))
	{
		printf("1 entra aqui\n");
		exit (0);
	}
	else if (ft_died(p))
		return ; */
	printf("salida\n");
	return ;
}

int	ft_died(t_philo *p)
{
	/* int sval;
	sem_getvalue(p->t->sem, &sval);
	sem_wait(p->t->sem);
	printf("wait: %d\n", sval);
	if (p->t->is_dead == 1)
	{
		printf("entra aqui\n");
		
		sem_getvalue(p->t->sem, &sval);
		sem_post(p->t->sem);
		printf("post: %d\n", sval);
		return (1);
	}
	sem_getvalue(p->t->sem, &sval);
	sem_post(p->t->sem);
	printf("else: %d\n", sval); */
	//int sval;
	int is_dead_local;

	sem_wait(p->t->sem);
	is_dead_local = p->t->is_dead;
	sem_post(p->t->sem);

	if (is_dead_local == 1)
	{
		printf("entra aqui\n");
		return (1);
	}
	//printf("else: %d\n", sval);
	return (0);
}

int	time_to_die(t_table *t)
{
	int	i;

	i = 0;
	while (i < t->n_philo)
	{
		sem_wait(t->sem);
		if (time_start_prog() - t->arr_p[i].last_eat >= t->die_to_time
			&& t->has_eaten == 0)
		{
			sem_post(t->sem);
			sem_wait(t->sem);
			t->is_dead = 1;
			sem_post(t->sem);
			sem_wait(t->sem);
			printf("%ld" RED " %d died\n" RESET, time_start_prog() - t->time_init,
				t->arr_p[i].index);
			sem_post(t->sem);
			return (1);
		}
		else
			sem_post(t->sem);
		i++;
	}
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
