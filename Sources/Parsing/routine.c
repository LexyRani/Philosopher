/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:01:35 by aceralin          #+#    #+#             */
/*   Updated: 2023/03/16 18:57:15 by aceralin         ###   ########.fr       */
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
	while (philo->take_forks != 2)
	{
		pthread_mutex_lock(&philo->left_fork->mutex_fork);
		if (philo->left_fork->free_fork == 0)
		{
			philo->left_fork->free_fork = 1;
			philo->take_forks++;
			print_routine(philo, TAKE_FORK);
		}
		pthread_mutex_unlock(&philo->left_fork->mutex_fork);
		pthread_mutex_lock(&philo->right_fork->mutex_fork);
		if (philo->right_fork->free_fork == 0)
		{
			philo->right_fork->free_fork = 1;
			philo->take_forks++;
			print_routine(philo, TAKE_FORK);
		}
		pthread_mutex_unlock(&philo->left_fork->mutex_fork);
	}
}

void	eating(t_philo *philo)
{
	print_routine(philo, EAT);
	//usleep()
}

void	routine(t_philo *philo)
{
	take_a_fork(philo);//il doit prendre deux fourchettes pour manger
	//puis il mange
	//il libere les fourchettes
	//il dort
	//il pense au reveil
	// print_routine(philo, EAT);
	// print_routine(philo, EAT);
	// print_routine(philo, EAT);
	// print_routine(philo, EAT);
}
