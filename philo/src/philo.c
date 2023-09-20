/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:22:38 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/20 19:16:03 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	checker_argv(t_philo *p, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				ft_error("The argument must contain only numeric digits.");
			j++;
		}
		i++;
	}
	p->n_philo = ft_atoi(av[1]);
	p->die_time = ft_atoi(av[2]);
	p->eat_time = ft_atoi(av[3]);
	p->sleep_time = ft_atoi(av[4]);
	if (av[5] != NULL)
		p->each_time = ft_atoi(av[5]);
	if (p->n_philo < 1 || p->die_time < 1 || p->eat_time < 1 || \
		p->sleep_time < 1)
		ft_error("The argument must be greater than 1");
}

void	set_arr_philos(t_philo *p)
{
	int	i;
	p->arr_philos = malloc(sizeof(t_data) * p->n_philo);
	if (!p->arr_philos)
		ft_error("No se pudo crear el array de philos\n");
	i = 0;
	while (p->n_philo > 0)
	{
		if (0 != pthread_create(&p->arr_philos[i].thread, NULL, controller, NULL))
		ft_error("No se pudo crear el hilo\n");
		i++;
		p->n_philo--;
	}
}

void	set_arr_forks(t_philo *p)
{
	int	i;

	i = 0;
	p->arr_forks = malloc(sizeof(pthread_mutex_t) * p->n_philo);
	if (!p->arr_forks)
		ft_error("Error al crear los tenedores\n");
	while (p->n_philo > 0)
	{
		pthread_mutex_init(&p->arr_forks[i], NULL);
		i--;
		p->arr_forks--;
	}
}

void	time_start_prog(t_philo *p)
{
	struct timeval	init;

	gettimeofday(&init, NULL);
	p->time_init = (init.tv_sec * 1000) + (init.tv_usec / 1000);
	printf("Tiempo desde que inicio prog: %ld\n", p->time_init);
	
}

int	main(int ac, char **av)
{
	t_philo			p;

	if (ac < 5 || ac > 6)
		ft_error("You must enter at least 4 arguments!");
	//atexit(leaks);
	time_start_prog(&p);
	init_data_philos(&p);
	init_philo_struct(&p);
	checker_argv(&p, av);
	set_arr_philos(&p);
	set_arr_forks(&p);
	create_philos(&p);
	free(p.arr_philos);
	return (0);
}
