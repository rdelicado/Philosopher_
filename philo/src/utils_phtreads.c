/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_phtreads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:54:28 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/20 15:32:11 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*controller(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	(void)p;
	int i = 3;
	while (i > 0)
	{
		sleep(1);
		// pthread_create(p->n_philo, NULL, )
		printf("Controlador creado\n");
		i--;
	}
	return NULL;
}

void	create_philos(t_philo *p)
{
	pthread_t	control;
	int	i;

	i = 0;
	if (0 != pthread_create(&control, NULL, controller, p))
		ft_error("No se pudo crear el controlador\n");
	if (0 != pthread_join(control, NULL))
		ft_error("Error al esperar al controlador\n");
}


