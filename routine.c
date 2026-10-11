/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:35:07 by rodantec          #+#    #+#             */
/*   Updated: 2025/08/24 13:30:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken a fork");
		update_death_time(philo);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, "has taken a fork");
		update_death_time(philo);
	}
	return (1);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->philo_mutex);
	if (philo->table->number_tte != -1
		&& philo->meals_eaten >= philo->table->number_tte)
	{
		pthread_mutex_unlock(&philo->philo_mutex);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->philo_mutex);
	safe_print(philo, "is eating");
	philo_sleep(philo, philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_and_think(t_philo *philo)
{
	safe_print(philo, "is sleeping");
	philo_sleep(philo, philo->table->time_to_sleep);
	safe_print(philo, "is thinking");
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	update_death_time(philo);
	if (philo->table->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, "has taken a fork");
		philo_sleep(philo, philo->table->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(2000);
	while (!check_death(philo))
	{
		eat(philo);
		if (check_death(philo))
			break ;
		sleep_and_think(philo);
	}
	return (NULL);
}
