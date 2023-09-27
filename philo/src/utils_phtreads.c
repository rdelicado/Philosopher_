/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_phtreads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:54:28 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/27 20:03:02 by rdelicad         ###   ########.fr       */
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

void	set_arr_forks(t_table *t, t_philo *p)
{
	int	i;
	int	j;

	j = t->n_philo;
	i = 0;
	t->arr_m = malloc(sizeof(pthread_mutex_t) * t->n_philo);
	if (!t->arr_m)
		ft_error("Error al crear los tenedores\n");
	while (j > 0)
	{
		pthread_mutex_init(&t->arr_m[i], NULL);
		p->l_fork = t->arr_m[i];
		if (j != 0)
			p->r_fork = t->arr_m[i + 1];
		p->r_fork = t->arr_m[0];
		i++;
		j--;
	}
}

void	init_threads(t_table *t)
{
	pthread_t control;
    int i = 0;

    if (0 != pthread_create(&control, NULL, controller, t))
        ft_error("No se pudo crear el controlador\n");
    if (0 != pthread_join(control, NULL))
        ft_error("Error al esperar al controlador\n");
    while (i % 2 == 0 && i < t->n_philo)
    {
        if (0 != pthread_create(&t->arr_p[i].thread, NULL, philo_routine, &t->arr_p[i]))
            ft_error("No se pudo crear el hilo\n");
        i += 2;
    }
	i = 1;
	while (i % 2 != 0 && i < t->n_philo)
    {
        if (0 != pthread_create(&t->arr_p[i].thread, NULL, philo_routine, &t->arr_p[i]))
            ft_error("No se pudo crear el hilo\n");
        i += 2;
    }
	init_joins(t);
}

void	init_joins(t_table *t)
{
	int	i;

	i = 0;
	while (i % 2 == 0 && i < t->n_philo)
    {
		if (0 != pthread_join(t->arr_p[i].thread, NULL))
            ft_error("Error al esperar al filósofo\n");
        i += 2;
    }
	i = 1;
	while (i % 2 != 0 && i < t->n_philo)
    {
		if (0 != pthread_join(t->arr_p[i].thread, NULL))
            ft_error("Error al esperar al filósofo\n");
        i += 2;
    }
}


/* 
void* filosofo(void* arg) {
    t_philo* philosopher = (t_philo*)arg;
    int left_fork = philosopher->id;
    int right_fork = (philosopher->id + 1) % NUM_FILOSOFOS;

    // Acceder a los tenedores
    pthread_mutex_lock(&table->forks[left_fork]);
    pthread_mutex_lock(&table->forks[right_fork]);

    // Realizar acciones de comer

    // Liberar los tenedores
    pthread_mutex_unlock(&table->forks[left_fork]);
    pthread_mutex_unlock(&table->forks[right_fork]);

    pthread_exit(NULL);
}
 */