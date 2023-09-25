/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_phtreads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:54:28 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/25 23:34:31 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_routine(void *args)
{
	t_table	*t;

	t = (t_table *)args;
	//coger tenedor
	//
	printf("tiempo init %ld\n", time_start_prog(t) - t->time_init);
	t->time_curr = time_start_prog(t);
	for (int i = 0; i < 100; i++){
		ft_usleep(200);
		printf("tiempo init %ld\n", time_start_prog(t) - t->time_curr);
	}
	//printf("tiempo %d\n", time_curr_prog(t));
	/* printf("%d %d has taken a fork", t.);
	//comer
	printf("%d %d is eating", );
	//dormir
	printf("%d %d is sleeping", );
	//pensar
	printf("%d %d is thinking", );
	//morir
	printf("%d %d died", );
	usleep(t->arr_p->eat_to_time * 1000); */
/* ◦ timestamp_in_ms X has taken a fork → ha tomado un tenedor
◦ timestamp_in_ms X is eating              → esta comiendo
◦ timestamp_in_ms X is sleeping          → esta durmiendo
◦ timestamp_in_ms X is thinking           → esta pensando
◦ timestamp_in_ms X died                     → murio */
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
	/* int			i;

	i = 0; */
	if (0 != pthread_create(&control, NULL, controller, t))
		ft_error("No se pudo crear el controlador\n");
	if (0 != pthread_join(control, NULL))
		ft_error("Error al esperar al controlador\n");
	/* while (i < t->n_philo)
	{
		if (0 != pthread_join(t->arr_p[i].thread, NULL))
			ft_error("Error al esperar al controlador\n");
		i++;
	} */
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
		pthread_mutex_init(&t->arr_m[i], NULL);
		i--;
		j--;
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