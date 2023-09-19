/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:22:38 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/19 16:27:57 by rdelicad         ###   ########.fr       */
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

int	main(int ac, char **av)
{
	t_philo	p;

	if (ac < 5 || ac > 6)
		ft_error("You must enter at least 4 arguments!");
	//atexit(leaks);
	init_philo_struct(&p);
	checker_argv(&p, av);
	create_philos(&p);
	return (0);
}
