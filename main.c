/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:35:07 by rodantec          #+#    #+#             */
/*   Updated: 2025/08/24 00:00:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				philosopher_routine, &table->philo[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&table->monitor_thread, NULL,
			monitor_routine, table) != 0)
		return (0);
	return (1);
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
	pthread_join(table->monitor_thread, NULL);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (validate_args(ac, av) == 0)
		return (1);
	if (init_table(&table, ac, av) == 0)
		return (1);
	if (init_mutexes(&table) == 0)
	{
		cleanup_table(&table);
		return (1);
	}
	if (init_philosophers(&table) == 0)
	{
		cleanup_table(&table);
		return (1);
	}
	table.start_time = get_current_time();
	if (create_threads(&table) == 0)
	{
		cleanup_table(&table);
		return (1);
	}
	join_threads(&table);
	cleanup_table(&table);
	return (0);
}
