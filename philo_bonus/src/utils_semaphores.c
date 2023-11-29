/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_semaphores.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:56:53 by rdelicad          #+#    #+#             */
/*   Updated: 2023/11/29 20:20:34 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_philos(t_table *t, t_philo *p)
{
	int		i;

	t->child_pids = malloc(sizeof(pid_t) * t->n_philo);
	if (!t->child_pids)
		ft_error("No se pudo crear array de pids");
	t->arr_p = malloc(sizeof(t_philo) * t->n_philo);
	if (!t->arr_p)
		ft_error("No se pudo crear array de philos");
	p->t->time_init = time_start_prog();
	p->last_eat = time_start_prog();
	i = 0;
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
			set_arr_philos(t, p, i);
		i++;
	}
	routine_table(t);
}

void	set_arr_philos(t_table *t, t_philo *p, int i)
{
	t->arr_p[i] = *p;
	t->arr_p[i].index = i + 1;
	t->child_pids[i] = t->pid;
	p->pid = t->child_pids[i];
}

void	preclean(t_table *t)
{
	(void)t;
	sem_unlink("/control");
	sem_unlink("/forks");
}

void	clean(t_table *t)
{
	int	i;

	sem_close(t->forks);
	sem_close(t->sem);
	sem_unlink("/control");
	sem_unlink("/forks");
	i = 0;
	while (i < t->n_philo)
	{
		kill(t->arr_p[i].pid, SIGKILL);
		i++;
	}
	free(t->child_pids);
	free(t->arr_p);
}

void	init_semaphores(t_table *t)
{
	t->forks = sem_open("/forks", O_CREAT | O_EXCL | O_RDWR , 0666, t->n_philo);
	if (t->forks == SEM_FAILED)
		ft_error("No se pudo crear el semaforo de forks");
	t->sem = sem_open("/control", O_CREAT | O_EXCL | O_RDWR , 0666, 1);
	if (t->sem == SEM_FAILED)
		ft_error("No se pudo crear el semaforo de control");
}


