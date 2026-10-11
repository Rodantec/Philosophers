/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 14:27:12 by rodantec          #+#    #+#             */
/*   Updated: 2025/08/24 00:00:00 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000LL);
}

long long	get_time_diff(long long start_time)
{
	return (get_current_time() - start_time);
}

int	philo_sleep(t_philo *philo, long long sleep_time)
{
	long long	wake_up_time;

	if (check_death(philo))
		return (0);
	wake_up_time = get_time_diff(philo->table->start_time) + sleep_time;
	while (get_time_diff(philo->table->start_time) < wake_up_time)
	{
		usleep(500);
		if (check_death(philo))
			return (0);
	}
	return (1);
}

void	update_death_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->last_meal_time = get_time_diff(philo->table->start_time);
	pthread_mutex_unlock(&philo->philo_mutex);
}

int	safe_print(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (0);
	}
	printf("%lld %d %s\n",
		get_time_diff(philo->table->start_time), philo->id, message);
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (1);
}
