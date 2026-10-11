/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodantec <rodantec@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:35:07 by rodantec          #+#    #+#             */
/*   Updated: 2025/06/11 12:26:52 by rodantec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	philo_mutex;
	long long		last_meal_time;
	int				meals_eaten;
	t_table			*table;
	long long		death_deadline;
}	t_philo;

typedef struct s_table
{
	long long		number_of_philosophers;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		number_tte;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	int				someone_died;
	t_philo			*philo;
	pthread_t		monitor_thread;
}	t_table;

long long	ft_atoi_long( char *str);
int			validate_args(int ac, char **av);
int			init_table(t_table *table, int ac, char **av);
int			init_philosophers(t_table *table);
int			init_mutexes(t_table *table);
void		cleanup_table(t_table *table);
long long	get_current_time(void);
long long	get_time_diff(long long start_time);
int			philo_sleep(t_philo *philo, long long sleep_time);
void		update_death_time(t_philo *philo);
void		*philosopher_routine(void *arg);
void		*monitor_routine(void *arg);
int			take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		sleep_and_think(t_philo *philo);
int			safe_print(t_philo *philo, char *message);
int			check_death(t_philo *philo);
int			check_all_fed(t_table *table);
int			is_philosopher_dead(t_philo *philo);
void		*monitor_routine(void *arg);

#endif
