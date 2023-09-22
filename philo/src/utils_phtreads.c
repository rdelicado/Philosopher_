/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_phtreads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:54:28 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/22 09:18:42 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *args)
{
	t_table	*t;

	t = (t_table *)args;
	(void)t;
	//comer
	//dormir
	//pensar
	sleep(1);
	printf("hilo philosopher creado\n");
	return (NULL);
}

void	*controller(void *args)
{
	t_table	*t;

	t = (t_table *)args;
	(void)t;
	sleep(1);
	printf("Controlador creado\n");
	return (NULL);
}

void	create_philos(t_table *t)
{
	pthread_t	control;

	if (0 != pthread_create(&control, NULL, controller, t))
		ft_error("No se pudo crear el controlador\n");
	if (0 != pthread_join(control, NULL))
		ft_error("Error al esperar al controlador\n");
}

void	set_arr_philos(t_table *t)
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
		if (0 != pthread_create(&t->arr_p[i].thread, NULL, philo_routine, t))
			ft_error("No se pudo crear el hilo\n");
		if (0 != pthread_join(t->arr_p[i].thread, NULL))
			ft_error("Error al esperar al controlador\n");
		i++;
		j--;
	}
	i = 0;
	while (i < t->n_philo)
	{
		t->arr_p[i].index = i + 1;
		i++;
	}
}

void	set_arr_forks(t_table *t)
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
		pthread_mutex_init(&t->arr_m[i].mutex, NULL);
		i--;
		j--;
	}
}

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
