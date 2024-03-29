/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:01:35 by aceralin          #+#    #+#             */
/*   Updated: 2023/05/07 15:22:42 by aceralin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	check_death(t_philo *philo)
{
	if ((get_time(philo->start_time) - philo->last_meal_time) >= \
	philo->time_to_die && philo->data->someone_died == 0)
	{
		philo->data->someone_died = 1;
		printf("%ld %d %s\n", get_time(philo->start_time), philo->index, DIE);
	}
	philo->dead = philo->data->someone_died;
}

void	print_routine(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->mutex_philo);
	check_death(philo);
	if (philo->data->someone_died != 1)
		printf("%ld %d %s\n", get_time(philo->start_time), philo->index, action);
	pthread_mutex_unlock(&philo->data->mutex_philo);
}

void	take_a_fork(t_philo *philo)
{
	while (philo->take_forks != 2 && philo->dead != 1)
	{
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
		if (philo->left_fork->free_fork == 0)
		{
			philo->left_fork->free_fork = 1;
			philo->take_forks++;
			print_routine(philo, TAKE_FORK);
		}
		pthread_mutex_unlock(&philo->left_fork->mutex_fork);
		pthread_mutex_lock(&philo->data->mutex_philo);
		check_death(philo);
		pthread_mutex_unlock(&philo->data->mutex_philo);
		pthread_mutex_lock(&philo->right_fork->mutex_fork);
		if (philo->right_fork->free_fork == 0)
		{
			philo->right_fork->free_fork = 1;
			philo->take_forks++;
			print_routine(philo, TAKE_FORK);
		}
		pthread_mutex_unlock(&philo->right_fork->mutex_fork);
	}
}

void	is_eating(t_philo *philo)
{
	long int	end_time;

	print_routine(philo, EAT);
	philo->last_meal_time = get_time(philo->start_time);
	end_time = get_time(philo->start_time) + philo->time_to_eat;
	while (get_time(philo->start_time) < end_time && philo->dead != 1)
	{
		pthread_mutex_lock(&philo->data->mutex_philo);
		check_death(philo);
		pthread_mutex_unlock(&philo->data->mutex_philo);
		if (philo->dead)
			break ;
		usleep(50);
	}
}

void	routine(t_philo *philo)
{
	take_a_fork(philo);
	if (philo->times_must_eat)
		is_eating(philo);
	free_forks(philo);
	philo->times_must_eat--;
	if (philo->times_must_eat)
		is_sleeping(philo);
	else
		print_routine(philo, SLEEP);
}
