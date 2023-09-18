/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:34:30 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/18 20:10:47 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_error(char *str)
{
	printf("Error: %s", str);
}

void	init_philo_struct(t_philo *p)
{
	p->n_philo = 0;
	p->die_time = 0;
}


