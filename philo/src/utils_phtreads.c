/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_phtreads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:54:28 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/21 17:10:04 by rdelicad         ###   ########.fr       */
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
	while (i <= j)
	{
		pthread_mutex_init(&t->arr_p[i].l_fork, NULL);
		if (i == j)
			t->arr_p[i].r_fork = &t->arr_p[0].l_fork;
		else
			t->arr_p[i].r_fork = &t->arr_p[i + 1].l_fork;
		i++;
	}
	pthread_mutex_init(&t->table, NULL);
}

void	init_threads(t_table *t)
{
	int	i;

	t->time_curr = time_start_prog();
	i = 0;
	while (i < t->n_philo)
	{
		if (0 != pthread_create(&t->arr_p[i].thread, NULL, philo_routine,
				&t->arr_p[i]))
			ft_error("No se pudo crear el hilo\n");
		pthread_mutex_lock(&t->table);
		t->arr_p[i].last_eat = t->time_curr;
		pthread_mutex_unlock(&t->table);
		i++;
	}
	if (0 != pthread_create(&t->control, NULL, controller, t))
		ft_error("No se pudo crear el hilo\n");
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
