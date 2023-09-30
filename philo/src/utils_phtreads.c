/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_phtreads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:54:28 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/30 08:39:39 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_arr_philos(t_table *t, t_philo *p)
{
	int	i;
	int	j;

	j = t->n_philo;
	t->arr_p = malloc(sizeof(t_philo) * t->n_philo);
	if (!t->arr_p)
		ft_error("No se pudo crear el array de philos\n");
	i = 0;
	while (j > 0)
	{
		t->arr_p[i] = *p;
        t->arr_p[i].index = i + 1;
		i++;
		j--;
	}
}

void	set_arr_forks(t_table *t)
{
	int	i;
	int	j;

	j = t->n_philo - 1;
	i = 0;
	t->arr_m = malloc(sizeof(pthread_mutex_t) * t->n_philo);
	if (!t->arr_m)
		ft_error("Error al crear los tenedores\n");
	while (i <= j)
	{
		pthread_mutex_init(&t->arr_p[i].l_fork, NULL);
		if (i == j)
			t->arr_p[i].r_fork = &t->arr_p[0].l_fork;
		else
			t->arr_p[i].r_fork = &t->arr_p[i + 1].l_fork;
		i++;
	}
}

void	init_threads(t_table *t)
{
    int i;

	if (0 != pthread_create(&t->control, NULL, controller, t))
            ft_error("No se pudo crear el hilo\n");
	ft_usleep(10);
	i = 0;
    while (i < t->n_philo)
    {
        if (0 != pthread_create(&t->arr_p[i].thread, NULL, philo_routine, &t->arr_p[i]))
            ft_error("No se pudo crear el hilo\n");
        i++;
    }
	init_joins(t);
}

void	init_joins(t_table *t)
{
	int	i;

	if (0 != pthread_join(t->control, NULL))
            ft_error("Error al esperar al filósofo\n");
	i = 0;
	while (i < t->n_philo)
    {
		if (0 != pthread_join(t->arr_p[i].thread, NULL))
            ft_error("Error al esperar al filósofo\n");
        i++;
    }
	
}
