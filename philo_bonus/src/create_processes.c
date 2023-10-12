/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_processes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:54:28 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/11 09:24:32 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_philos(t_table *t, t_philo *p)
{
	(void)p;
	int		i;
	pid_t	pid;

	i = 0;
	pid = fork();
	while (pid > 0 && i < t->n_philo)
	{
		fork();
		printf("padre con pid %d\n", getpid());
		i++;
	}
	printf("soy el hijo %d hijo de %d \n", getpid(), getppid());
}
