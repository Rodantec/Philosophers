/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:35:07 by rodantec          #+#    #+#             */
/*   Updated: 2025/08/24 00:00:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table, int ac, char **av)
{
	table->number_of_philosophers = ft_atoi_long(av[1]);
	table->time_to_die = ft_atoi_long(av[2]);
	table->time_to_eat = ft_atoi_long(av[3]);
	table->time_to_sleep = ft_atoi_long(av[4]);
	table->number_tte = -1;
	if (ac == 6)
		table->number_tte = ft_atoi_long(av[5]);
	table->someone_died = 0;
	table->start_time = 0;
	table->forks = NULL;
	table->philo = NULL;
	return (1);
}

static int	init_forks(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(pthread_mutex_t)
			* table->number_of_philosophers);
	if (!table->forks)
		return (0);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_mutexes(t_table *table)
{
	if (!init_forks(table))
		return (0);
	if (pthread_mutex_init(&table->death_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (0);
	return (1);
}

int	init_philosophers(t_table *table)
{
	int	i;

	table->philo = malloc(sizeof(t_philo) * table->number_of_philosophers);
	if (!table->philo)
		return (0);
	i = 0;
	while (i < table->number_of_philosophers)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_eaten = 0;
		table->philo[i].last_meal_time = 0;
		table->philo[i].death_deadline = 0;
		table->philo[i].table = table;
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].right_fork
			= &table->forks[(i + 1) % table->number_of_philosophers];
		if (pthread_mutex_init(&table->philo[i].philo_mutex, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

void	cleanup_table(t_table *table)
{
	int	i;

	if (table->philo)
	{
		i = 0;
		while (i < table->number_of_philosophers)
			pthread_mutex_destroy(&table->philo[i++].philo_mutex);
		free(table->philo);
	}
	if (table->forks)
	{
		i = 0;
		while (i < table->number_of_philosophers)
			pthread_mutex_destroy(&table->forks[i++]);
		free(table->forks);
	}
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->print_mutex);
}
