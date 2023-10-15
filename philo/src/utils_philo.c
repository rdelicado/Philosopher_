/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@student.42.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 19:34:30 by rdelicad          #+#    #+#             */
/*   Updated: 2023/10/15 23:09:26 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_error_help(char *str)
{
	printf("Error: %s\n\n", str);
	printf("Uso:\n");
	printf("./philo <number_philo> <time_die> <time_eat> <time_sleep> ");
	printf("[optional] <each_time>\n");
	exit(1);
}

void	ft_error(char *str)
{
	printf("Error: %s\n", str);
	exit(1);
}

long	ft_atol(const char *str)
{
	long	num;
	int		sign;

	sign = 1;
	num = 0;
	while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\v'
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

long	ft_usleep(int time, t_table *t)
{
	struct timeval	init;
	long			time_start;
	long			time_finish;

	if (gettimeofday(&init, NULL) < 0)
		ft_error("no time");
	time_start = (init.tv_sec * 1000) + (init.tv_usec / 1000);
	while (1)
	{
		pthread_mutex_lock(&t->table);
		if (t->is_dead)
		{
			pthread_mutex_unlock(&t->table);
			break ;
		}
		else
			pthread_mutex_unlock(&t->table);
		if (gettimeofday(&init, NULL) < 0)
			ft_error("no time");
		time_finish = (init.tv_sec * 1000) + (init.tv_usec / 1000);
		time_finish -= time_start;
		if (time_finish == time)
			return (time_finish);
	}
	return (-1);
}
