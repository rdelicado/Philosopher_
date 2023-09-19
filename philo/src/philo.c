/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:22:38 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/19 11:14:44 by rdelicad         ###   ########.fr       */
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
	if (p->n_philo < 2 || p->die_time < 1 || p->eat_time < 1 || \
		p->sleep_time < 1)
		ft_error("The argument must be greater than 1");
}

int	main(int ac, char **av)
{
	t_philo	p;

	if (ac != 5)
		ft_error("You must enter 4 arguments!");
	//atexit(leaks);
	init_philo_struct(&p);
	checker_argv(&p, av);
}