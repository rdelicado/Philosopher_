/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:54:28 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/14 14:10:13 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"


void	set_philos(t_table *t, t_philo *p)
{
	int		i;

	t->child_pids = malloc(sizeof(pid_t) * t->n_philo);
	if (!t->child_pids)
		ft_error("No se pudo crear array de philos");
	i = 0;
	p->time_init = time_start_prog();
	p->last_eat = time_start_prog();
	while (i < t->n_philo)
	{
		t->pid = fork();
		if (t->pid == 0)
		{
			p->index = i + 1;
			routine_philos(p);
			exit(0);
		}
		else
		{
			t->child_pids[i] = t->pid;
			p->pid = t->child_pids[i];
		}
		i++;
	}
	routine_table(t);
}

void	routine_table(t_table *t)
{
	(void)t;
	/* sem_wait(&t->control);
	t->is_dead = 1;
	sem_post(&t->control); */
	while (waitpid(-1, NULL, 0) > 0) {}
	
	//waitpid(-1, NULL, 0);	
}

void	routine_philos(t_philo *p)
{
	if (p->index % 2 == 0)
		ft_usleep(1);
	printf("pid %d\n", p->pid);
	while (1)
	{
		//ft_usleep(1000);
		sem_wait(p->t->sem);
		if (p->t->is_dead == 1)
		{
			sem_post(p->t->sem);
			return;
		}
		else
			sem_post(p->t->sem);
		printf_action(p, "is thinking");
		if (time_start_prog() - p->time_init > 100)
		{
			sem_wait(p->t->sem);
			p->t->is_dead = 1;
			sem_post(p->t->sem);
			//printf("valor; %d\n", p->t->is_dead);
			return;
		}
	}
	exit (0);
}

void	printf_action(t_philo *p, char *str)
{
	sem_wait(p->t->sem);
	if (p->t->is_dead != 1)
	{
		if (ft_strcmp(str, "died") == 0)
			printf("%ld" RED " %d %s\n" RESET, time_start_prog()
				- p->time_init, p->index, str);
		else if (ft_strcmp(str, "is eating") == 0)
			printf("%ld" YELLOW " %d %s\n" RESET, time_start_prog()
				- p->time_init, p->index, str);
		else if (ft_strcmp(str, "has taken a fork") == 0)
			printf("%ld" GREEN " %d %s\n" RESET, time_start_prog()
				- p->time_init, p->index, str);
		else if (ft_strcmp(str, "is thinking") == 0)
			printf("%ld" BLUE " %d %s\n" RESET, time_start_prog()
				- p->time_init, p->index, str);
		else if (ft_strcmp(str, "is sleeping") == 0)
			printf("%ld" MAGENTA " %d %s\n" RESET, time_start_prog()
				- p->time_init, p->index, str);
	}
	sem_post(p->t->sem);
}

