/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:54:28 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/13 14:32:52 by rdelicad         ###   ########.fr       */
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
		if (t->pid == 0) //proceso hijo
		{
			p->index = i + 1;
			//printf("philo %d, inicio %ld\n", p->index, time_start_prog());
			//ft_usleep(1000);
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

void	init_semaphores(t_table *t)
{
	sem_init(&t->control, 0, 0);
}

void	routine_table(t_table *t)
{
	/* sem_wait(&t->control);
	t->is_dead = 1;
	sem_post(&t->control); */
	while (waitpid(-1, NULL, 0) > 0) {}
	sem_destroy(&t->control);
	//waitpid(-1, NULL, 0);	
}

void	routine_philos(t_philo *p)
{
	int y;
	printf("pid %d\n", p->pid);
	scanf("%d", &y);
	//while (1)
	//{
		//sem_wait(&p->t->control);
		if (p->t->is_dead == 1)
		{
			//sem_post(&p->t->control);
			return;
		}
		
		printf_action(p, "is thinking");
		if (p->index == 3)
		{
			p->t->is_dead = 1;
			//sem_post(&p->t->control);
			//printf("valor; %d\n", p->t->is_dead);
			return;
		}
		//sem_post(&p->t->control);
	//}
	exit (0);
}

void	printf_action(t_philo *p, char *str)
{
	//pthread_mutex_lock(&p->t->table);
	//sem_wait(&p->t->control);
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
	//sem_post(&p->t->control);
	//pthread_mutex_unlock(&p->t->table);
}
