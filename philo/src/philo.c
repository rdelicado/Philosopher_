/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:22:38 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/21 18:57:28 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	checker_argv(t_philo *p, t_data *d, char **av)
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
				ft_error_help("The argument must contain only numeric digits.");
			j++;
		}
		i++;
	}
	p->n_philo = ft_atoi(av[1]);
	d->die_to_time = ft_atoi(av[2]);
	d->eat_to_time = ft_atoi(av[3]);
	d->sleep_to_time = ft_atoi(av[4]);
	if (av[5] != NULL)
		d->thing_to_time = ft_atoi(av[5]);
	if (p->n_philo < 1 || p->n_philo > 200 || d->die_to_time < 1 || \
		d->eat_to_time < 1 || d->sleep_to_time < 1)
		ft_error_help("The argument must be greater than 1");
}

int	time_start_prog(t_philo *p)
{
	struct timeval	init;

	if (gettimeofday(&init, NULL) < 0)
		ft_error("no time");
	p->time_init = (init.tv_sec * 1000) + (init.tv_usec / 1000);
	printf("Tiempo desde que inicio prog: %ld\n", p->time_init);
	return (p->time_init);
}

int	time_curr_prog(t_philo *p)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	p->time_curr = (curr.tv_sec * 1000) + (curr.tv_usec / 1000);
	return (p->time_curr);
}

int	main(int ac, char **av)
{
	t_philo			p;
	t_data			d;

	if (ac < 5 || ac > 6)
		ft_error("You must enter at least 4 arguments!");
	atexit(leaks);
	init_data_philos(&d);
	init_philo_struct(&p);
	checker_argv(&p, &d, av);
	time_start_prog(&p);
	set_arr_philos(&p);
	set_arr_forks(&p);
	create_philos(&p);
	free(p.arr_p);
	free(p.arr_m);
	return (0);
}
