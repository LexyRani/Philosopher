/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:01:35 by aceralin          #+#    #+#             */
/*   Updated: 2023/03/14 20:13:39 by aceralin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    routine(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data->mutex_philo);
	// printf("time_for %d = %ld\n", philo->index, get_time(philo->start_time));
	// pthread_mutex_unlock(&philo->data->mutex_philo);
	philo->times_must_eat--;
	usleep(10000);
}