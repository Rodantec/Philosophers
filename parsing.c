/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:35:07 by rodantec          #+#    #+#             */
/*   Updated: 2025/06/11 12:26:52 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atoi_long( char *str)
{
	long long	result;
	int			i;

	result = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	validate_args(int ac, char **av)
{
	int			i;
	long long	value;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat\n",
			av[0]);
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
			return (printf("Error: Invalid argument '%s'\n", av[i]), 0);
		value = ft_atoi_long(av[i]);
		if (value <= 0 || value > INT_MAX)
			return (printf("Error: Argument '%s' out of range\n", av[i]), 0);
		i++;
	}
	if (ft_atoi_long(av[1]) > 200)
		return (printf("Error: Too many philosophers (max 200)\n"), 0);
	return (1);
}
