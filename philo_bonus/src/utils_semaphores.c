/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_semaphores.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:56:53 by rdelicad          #+#    #+#             */
/*   Updated: 2023/12/01 14:22:42 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_philos(t_table *t, t_philo *p)
{
	t->child_pids = malloc(sizeof(pid_t) * t->n_philo);
	if (!t->child_pids)
		ft_error("No se pudo crear array de pids");
	t->arr_p = malloc(sizeof(t_philo) * t->n_philo);
	if (!t->arr_p)
		ft_error("No se pudo crear array de philos");
	p->t->time_init = time_start_prog();
	p->last_eat = time_start_prog();
	create_fork(t, p);
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
	sem_unlink("/sem_meals_eaten");
	sem_unlink("/death");
}

void	clean(t_table *t)
{
	int	i;

	sem_close(t->forks);
	sem_close(t->sem);
	sem_unlink("/control");
	sem_unlink("/forks");
	sem_unlink("/sem_meals_eaten");
	sem_unlink("/death");
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
	t->sem_meals_eaten = sem_open("/meals_eaten", O_CREAT, 0644, 0);
	if (t->sem_meals_eaten == SEM_FAILED)
		ft_error("No se pudo crear el semaforo de comidas");
	t->sem_death = sem_open("/died", O_CREAT, 0644, 0);
	if (t->sem_meals_eaten == SEM_FAILED)
		ft_error("No se pudo crear el semaforo de muerte");
}


