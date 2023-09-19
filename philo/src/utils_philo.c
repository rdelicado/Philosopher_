/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:34:30 by rdelicad          #+#    #+#             */
/*   Updated: 2023/09/19 14:08:23 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_philo_struct(t_philo *p)
{
	p->n_philo = -1;
	p->die_time = -1;
	p->eat_time = -1;
	p->sleep_time = -1;
	p->each_time = -1;
}

void	ft_error(char *str)
{
	printf("Error: %s\n\n", str);
	printf("Uso:\n");
	printf("./philo <number_philo> <time_die> <time_eat> <time_sleep> ");
	printf("[optional] <each_time>\n");
	exit(1);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	sign;

	sign = 1;
	num = 0;
	while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\v' \
	|| *str == '\n' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (*str >= '0' && *str <= '9')
			num = num * 10 + (*str - '0');
		str++;
	}
	return (num * sign);
}

int	ft_isdigit(int c)
{
	if ((unsigned char)(c >= '0' && c <= '9'))
		return (1);
	return (0);
}

