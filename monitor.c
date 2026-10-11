/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:40:04 by rodantec          #+#    #+#             */
/*   Updated: 2025/08/24 13:05:21 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_philo_death(t_table *table, int i)
{
	pthread_mutex_lock(&table->death_mutex);
	table->someone_died = 1;
	pthread_mutex_unlock(&table->death_mutex);
	pthread_mutex_lock(&table->print_mutex);
	printf("%lld %d died\n",
		get_time_diff(table->start_time), table->philo[i].id);
	pthread_mutex_unlock(&table->print_mutex);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		if (check_all_fed(table))
		{
			pthread_mutex_lock(&table->death_mutex);
			table->someone_died = 1;
			pthread_mutex_unlock(&table->death_mutex);
			return (NULL);
		}
		i = 0;
		while (i < table->number_of_philosophers)
		{
			if (is_philosopher_dead(&table->philo[i]))
				return (handle_philo_death(table, i), NULL);
			i++;
		}
		usleep(500);
	}
	return (NULL);
}
