/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:57:20 by aceralin          #+#    #+#             */
/*   Updated: 2023/03/21 22:49:24 by aceralin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_philo(t_philo	*philo, char **argv, t_data *data, \
long int start_time)
{
	int				i;

	i = 0;
	while (i < data->nb_philo)
	{
		philo[i].index = i + 1;
		philo[i].take_forks = 0;
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].times_must_eat = -1;
		if (argv[5])
			philo[i].times_must_eat = ft_atoi(argv[5]);
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		philo[i].data = data;
		philo[i].start_time = start_time;
		philo[i].dead = 0;
		i++;
	}
}

int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i].mutex_fork, NULL) == -1)
		{
			printf("Error: Mutex init fail");
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i].mutex_fork);
			return (1);
		}
		data->forks[i].free_fork = 0;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	if (pthread_mutex_init(&data->mutex_philo, NULL) == -1)
		return (printf("Error: Mutex init fail"), 1);
	data->someone_died = 0;
	return (0);
}

int	init_all(t_philo *philo, char **argv, t_data *data)
{
	struct timeval	current_time;
	long int		start_time;
	int				i;

	i = 0;
	if (init_data(data, argv))
		return (1);
	if (init_fork(data))
		return (pthread_mutex_destroy(&data->mutex_philo), 1);
	if (gettimeofday(&current_time, NULL) == -1)
	{
		while (i < data->nb_philo)
			pthread_mutex_destroy(&data->forks[i++].mutex_fork);
		return (pthread_mutex_destroy(&data->mutex_philo), \
		printf("Failed to get current time\n"), 1);
	}
	start_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	init_philo(philo, argv, data, start_time);
	return (0);
}

void	init_thread(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philo[i].id, NULL, &ft_thread, &philo[i]) != 0)
		{
			pthread_mutex_lock(&data->mutex_philo);
			printf("Error thread %d\n", i);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->mutex_philo);
			break ;
		}
		i++;
	}
	while (i--)
		pthread_join(philo[i].id, NULL);
}
