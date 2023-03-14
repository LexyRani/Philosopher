/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceralin <aceralin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:57:20 by aceralin          #+#    #+#             */
/*   Updated: 2023/03/14 19:59:38 by aceralin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_philo(t_philo	*philo, char **argv, t_data *data)
{
	struct timeval	current_time;
	long int		start_time;
	int				i;

	i = 0;
	gettimeofday(&current_time, NULL); //proteger
	start_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	data->nb_philo = ft_atoi(argv[1]); //nombre de philo
	while(i < data->nb_philo)
	{
		philo[i].index = i + 1;
		philo[i].time_to_die = ft_atoi(argv[2]); //
		philo[i].time_to_eat = ft_atoi(argv[3]); // temps que le philo passe à manger
		philo[i].time_to_sleep = ft_atoi(argv[4]);// temps que le philo passe à dormir
		philo[i].times_must_eat = -1;
		if(argv[5])
			philo[i].times_must_eat = ft_atoi(argv[5]);//nombre de fois que chaque philo doit manger
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		philo[i].data = data;
		philo[i].start_time = start_time;
		// printf("left: %d, right: %d\n", i, (i + 1) % data->nb_philo);
		i++;
	}
}

void	init_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i].mutex_fork, NULL); //proteger
		data->forks[i].free_fork = 0;
		i++;
	}
}

void	init_data(t_data *data)
{

	pthread_mutex_init(&data->mutex_philo, NULL); //proteger
	data->someone_died = 0;
}

void	init_all(t_philo *philo, char **argv, t_data *data)
{
	init_data(data);
	init_fork(data);
	init_philo(philo, argv, data);
}
