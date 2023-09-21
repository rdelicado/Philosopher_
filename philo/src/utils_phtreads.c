/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_phtreads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:54:28 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/21 18:57:14 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	//comer
	//dormir
	//pensar
	sleep(1);
	printf("hilo philosopher creado\n");
	return (NULL);
}

void	*controller(void *args)
{
	t_philo	*p;

	p = (t_philo *)args;
	sleep(1);
	printf("Controlador creado\n");
	return (NULL);
}

void	create_philos(t_philo *p)
{
	pthread_t	control;
	int			i;

	i = 0;
	if (0 != pthread_create(&control, NULL, controller, p))
		ft_error("No se pudo crear el controlador\n");
	if (0 != pthread_join(control, NULL))
		ft_error("Error al esperar al controlador\n");
}

void	set_arr_philos(t_philo *p)
{
	int	i;
	int	j;

	j = p->n_philo;
	p->arr_p = malloc(sizeof(t_data) * p->n_philo);
	if (!p->arr_p)
		ft_error("No se pudo crear el array de philos\n");
	i = 0;
	while (j > 0)
	{
		if (0 != pthread_create(&p->arr_p[i].thread, NULL, philo_routine, p))
			ft_error("No se pudo crear el hilo\n");
		if (0 != pthread_join(p->arr_p[i].thread, NULL))
			ft_error("Error al esperar al controlador\n");
		i++;
		j--;
	}
	i = 0;
	while (i < p->n_philo)
	{
		p->arr_p[i].index = i + 1;
		i++;
	}
}

void	set_arr_forks(t_philo *p)
{
	int	i;
	int	j;

	j = p->n_philo;
	i = 0;
	p->arr_m = malloc(sizeof(pthread_mutex_t) * p->n_philo);
	if (!p->arr_m)
		ft_error("Error al crear los tenedores\n");
	while (j > 0)
	{
		pthread_mutex_init(&p->arr_m[i].mutex, NULL);
		i--;
		j--;
	}
}
