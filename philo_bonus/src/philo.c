/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:22:38 by rdelicad          #+#    #+#             */
/*   Updated: 2023/12/01 15:52:18 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	checker_argv(t_table *t, char **av, int ac)
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
	init_args(t, av, ac);
}

void	init_args(t_table *t, char **av, int ac)
{
	t->n_philo = ft_atol(av[1]);
	t->die_to_time = ft_atol(av[2]);
	t->eat_to_time = ft_atol(av[3]);
	t->sleep_to_time = ft_atol(av[4]);
	if (ac == 5)
		t->num_meals = -1;
	else if (ac == 6)
	{
		t->num_meals = ft_atol(av[5]);
		if (t->num_meals > INT_MAX)
			ft_error_help("numero excedido del INT_MAX");
		else if (t->num_meals < 1)
			ft_error_help("The argument must be greater than 1");
	}
	if (t->n_philo < 1 || t->die_to_time < 1 || t->eat_to_time < 1
		|| t->sleep_to_time < 1)
		ft_error_help("The argument must be greater than 1");
	if (t->n_philo > INT_MAX || t->die_to_time > INT_MAX
		|| t->eat_to_time > INT_MAX || t->sleep_to_time > INT_MAX)
		ft_error_help("numero excedido del INT_MAX");
}

long	time_start_prog(void)
{
	unsigned long	nbr;
	struct timeval	init;

	if (gettimeofday(&init, NULL) < 0)
		ft_error("no time");
	nbr = (init.tv_sec * 1000) + (init.tv_usec / 1000);
	return (nbr);
}

int	main(int ac, char **av)
{
	t_table	t;
	t_philo	p;

	if (ac < 5 || ac > 6)
		ft_error("You must enter at least 4 arguments!");
	// atexit(leaks);
	preclean(&t);
	init_data_table(&t);
	init_data_philos(&p, &t);
	checker_argv(&t, av, ac);
	init_semaphores(&t);
	set_philos(&t, &p);
	clean(&t);
	return (0);
}
