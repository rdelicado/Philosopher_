/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_simulator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 20:56:53 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/14 13:34:45 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	preclean()
{
	sem_unlink("/control");
}

void	clean(t_table *t)
{
	sem_close(t->sem);
	sem_unlink("/control");
	free(t->child_pids);
}

void	init_semaphores(t_table *t)
{
	t->sem = sem_open("/control", O_CREAT | O_EXCL | O_RDWR , 0666, 1);
	if (t->sem == SEM_FAILED)
		ft_error("No se pudo crear el semaforo");
}