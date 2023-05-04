/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 19:32:37 by aceralin          #+#    #+#             */
/*   Updated: 2023/05/04 18:14:36 by aceralin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex_fork);
	philo->left_fork->free_fork = 0;
	pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	pthread_mutex_lock(&philo->right_fork->mutex_fork);
	philo->right_fork->free_fork = 0;
	pthread_mutex_unlock(&philo->right_fork->mutex_fork);
	philo->take_forks = 0;
}

void	is_sleeping(t_philo *philo)
{
	long int	end_time;

	print_routine(philo, SLEEP);
	end_time = get_time(philo->start_time) + philo->time_to_sleep;
	while (get_time(philo->start_time) < end_time && philo->dead != 1)
	{
		pthread_mutex_lock(&philo->data->mutex_philo);
		check_death(philo);
		pthread_mutex_unlock(&philo->data->mutex_philo);
		if (philo->dead)
			break ;
		usleep(50);
	}
	print_routine(philo, THINK);
}
