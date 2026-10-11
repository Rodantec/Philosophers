/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:42:23 by rodantec          #+#    #+#             */
/*   Updated: 2025/08/24 12:25:36 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	int	dead;

	pthread_mutex_lock(&philo->table->death_mutex);
	dead = philo->table->someone_died;
	pthread_mutex_unlock(&philo->table->death_mutex);
	return (dead);
}

int	check_all_fed(t_table *table)
{
	int	i;
	int	all_fed;

	if (table->number_tte == -1)
		return (0);
	all_fed = 1;
	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->philo[i].philo_mutex);
		if (table->philo[i].meals_eaten < table->number_tte)
			all_fed = 0;
		pthread_mutex_unlock(&table->philo[i].philo_mutex);
		if (!all_fed)
			break ;
		i++;
	}
	return (all_fed);
}

int	is_philosopher_dead(t_philo *philo)
{
	long long	current_time;
	long long	time_since_last_meal;
	int			dead;

	pthread_mutex_lock(&philo->philo_mutex);
	current_time = get_time_diff(philo->table->start_time);
	time_since_last_meal = current_time - philo->last_meal_time;
	dead = (time_since_last_meal > philo->table->time_to_die);
	pthread_mutex_unlock(&philo->philo_mutex);
	return (dead);
}
