/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:22:38 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/21 21:36:41 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	checker_argv(t_table *t, t_philo *p, char **av)
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
	t->n_philo = ft_atoi(av[1]);
	p->die_to_time = ft_atoi(av[2]);
	p->eat_to_time = ft_atoi(av[3]);
	p->sleep_to_time = ft_atoi(av[4]);
	if (av[5] != NULL)
		p->thing_to_time = ft_atoi(av[5]);
	if (t->n_philo < 1 || t->n_philo > 200 || p->die_to_time < 1 || \
		p->eat_to_time < 1 || p->sleep_to_time < 1)
		ft_error_help("The argument must be greater than 1");
}

int	time_start_prog(t_table *t)
{
	struct timeval	init;

	if (gettimeofday(&init, NULL) < 0)
		ft_error("no time");
	t->time_init = (init.tv_sec * 1000) + (init.tv_usec / 1000);
	printf("Tiempo desde que inicio prog: %ld\n", t->time_init);
	return (t->time_init);
}

int	time_curr_prog(t_table *t)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	t->time_curr = (curr.tv_sec * 1000) + (curr.tv_usec / 1000);
	return (t->time_curr);
}

int	main(int ac, char **av)
{
	t_table			t;
	t_philo			p;

	if (ac < 5 || ac > 6)
		ft_error("You must enter at least 4 arguments!");
	//atexit(leaks);
	init_data_philos(&p);
	init_philo_struct(&t);
	checker_argv(&t, &p, av);
	time_start_prog(&t);
	set_arr_philos(&t);
	set_arr_forks(&t);
	create_philos(&t);
	free(t.arr_p);
	free(t.arr_m);
	return (0);
}
